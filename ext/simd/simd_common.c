#include "simd_common.h"

#define XMM_BYTES 16 /* Width of the xmm1,2... registers */

/* Internal: Allocate memory for the vector container. */
VALUE allocate(VALUE klass)
{
	vector_t *vector = malloc(sizeof(vector_t));
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}

	vector->data = NULL; /* Avoid potentially freeing unitialized memory. */
	return(Data_Wrap_Struct(klass, NULL, deallocate, vector));
}

/* Internal: Free memory from the vector container and the data array. */
void deallocate(vector_t *vector)
{
	if(vector)
	{
		if(vector->data)
		{
			free(vector->data);
		}
		free(vector);
	}
}

/* Public: Return the number of elements in the Array. */
VALUE method_length(VALUE self)
{
	vector_t *vector;
	Data_Get_Struct(self, vector_t, vector);

	return(INT2NUM(vector->len));
}

/* Internal: Allocate memory for the data array. */
void *internal_allocate_vector_array(unsigned long count)
{
	void *vector = malloc((count + 1) * XMM_BYTES);
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}

	return(vector);
}

/* Internal: Determine if two arrays can be acted upon, by being of equal
 * lengths or with the operand's length being a multiple of the data array's. */
int internal_align_vectors(unsigned long v1, unsigned long v2, unsigned int modulo)
{
	if((v1 % modulo) != (v2 % modulo))
	{
		rb_raise(rb_eArgError, "Both Vectors must be of even or odd length.");
	}

	if(v1 == v2)
	{
		return(0);
	}
	if(v2 == modulo)
	{
		return(1);
	}
	if(v1 % v2 == 0 && v2 % modulo == 0)
	{
		return(2);
	}

	rb_raise(rb_eArgError, "Vector lengths misaligned.");
	/* Never reached */
	return(-1);
}

/* Internal: Given another object, perform an action specified via a function
 * pointer against both.
 *
 * Since arithmetic is purposefully performed against a void pointers, disable
 * warnings regarding this for the current function. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
VALUE internal_apply_operation(VALUE self, VALUE obj, size_t size, VALUE klass, b_operation func)
{
	unsigned long length, i, j;
	int align;
	vector_t *v1, *v2, *rv;
	void *data;
	VALUE result_obj = allocate(klass);

	Data_Get_Struct(self, vector_t, v1);
	Data_Get_Struct(obj, vector_t, v2);
	Data_Get_Struct(result_obj, vector_t, rv);
	rv->data = internal_allocate_vector_array(v1->len);

	align = internal_align_vectors(v1->len, v2->len, (XMM_BYTES / size));

	length = ((v1->len + (XMM_BYTES / size - 1)) / (XMM_BYTES / size));
	rv->len = v1->len;

	switch(align)
	{
		case 0: /* Same size arrays */
			for(i = 0; i < length; i++)
			{
				func((v1->data + XMM_BYTES * i), (v2->data + XMM_BYTES * i), (rv->data + XMM_BYTES * i));
			}
			break;
		case 1: /* Operand is exactly 4 long (size of 1 sse register) */
			for(i = 0; i < length; i++)
			{
				func((v1->data + XMM_BYTES * i), v2->data, (rv->data + XMM_BYTES * i));
			}
			break;
		default: /* Self is a multiple of operand's length long */
			for(j = 0; j < v2->len; j++)
			{
				data = v2->data + XMM_BYTES * j;
				for(i = j; i < length; i+=v2->len)
				{
					func((v1->data + XMM_BYTES * i), data, (rv->data + XMM_BYTES * i));
				}
			}
	}
	internal_sanitize_unaligned_final_vector(rv, size);

	return(result_obj);
}
#pragma GCC diagnostic pop

/* Internal: Make sure that no null bytes exist beyond the boundary of
 * unaligned vectors.  This function should be called after any operation that
 * results in the mutation or creation of a vector array.
 *
 * Since arithmetic is purposefully performed against a void pointers, disable
 * warnings regarding this for the current function. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
void internal_sanitize_unaligned_final_vector(vector_t *rv, size_t size)
{
	unsigned long i;

	if((rv->len * size) % XMM_BYTES)
	{
		for(i = 1; i <= XMM_BYTES - ((rv->len * size) % XMM_BYTES); i+=size)
		{
			*(unsigned char *)(rv->data + (rv->len * size + i)) = 1;
		}
	}
}
#pragma GCC diagnostic pop
