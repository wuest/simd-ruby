#include "simd_common.h"

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
void *internal_allocate_vector_array(unsigned long count, size_t size)
{
	unsigned int modulo = 16 / size;
	void *vector = malloc(((count + (count % modulo)) / modulo + 1) * size);
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
