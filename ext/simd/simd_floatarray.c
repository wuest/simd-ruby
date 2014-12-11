#include "simd_floatarray.h"

VALUE SIMD_FloatArray = Qnil;

/* Internal: Create the SIMD::FloatArray class. */
void Init_SIMD_FloatArray(VALUE parent)
{
	SIMD_FloatArray = rb_define_class_under(parent, "FloatArray", rb_cObject);
	rb_define_alloc_func(SIMD_FloatArray, allocate);
	rb_define_method(SIMD_FloatArray, "initialize", method_initialize, 1);
	rb_define_method(SIMD_FloatArray, "*", method_multiply, 1);
	rb_define_method(SIMD_FloatArray, "/", method_divide, 1);
	rb_define_method(SIMD_FloatArray, "+", method_add, 1);
	rb_define_method(SIMD_FloatArray, "-", method_subtract, 1);
	rb_define_method(SIMD_FloatArray, "length", method_length, 0);
	rb_define_method(SIMD_FloatArray, "to_a", method_to_a, 0);
}

/* Internal: Allocate memory for the vector container. */
static VALUE allocate(VALUE klass)
{
	d2v_container *vector = malloc(sizeof(d2v_container));
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}

	vector->data = NULL; /* Avoid potentially freeing unitialized memory. */
	return(Data_Wrap_Struct(klass, NULL, deallocate, vector));
}

/* Internal: Free memory from the vector container and the data array. */
static void deallocate(d2v_container *vector)
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

/* Public: Initialize the FloatArray object given a Ruby Array of values
 * which can be cast to a double. */
static VALUE method_initialize(VALUE self, VALUE rb_array)
{
	d2v_container *vector;
	unsigned long n,m,i;

	Check_Type(rb_array, T_ARRAY);
	Data_Get_Struct(self, d2v_container, vector);

	vector->len = n = RARRAY_LEN(rb_array);

	if(vector->len < 2)
	{
		rb_raise(rb_eArgError, "Vectors must be at least 2 long");
	}

	vector->data = internal_allocate_vector_array(vector->len);

	for(i = 0; i < n; i++)
		vector->data[i/2].f[i%2] = NUM2DBL(rb_ary_entry(rb_array, i));

	/* If the array is an odd number of elements, set the final element to 1 */
	m = n + (n % 2);
	if(n < m)
	{
		vector->data[m/2].f[1] = 1.0;
	}

	return(self);
}

/* Public: Multiply values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_multiply(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_multiply));
}

/* Public: Divide values contained in the data array by those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_divide(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_divide));
}

/* Public: add values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_add(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_add));
}

/* Public: Subtract values contained in another FloatArray object from those
 * contained in the current data array object, returning a new FloatArray. */
static VALUE method_subtract(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_subtract));
}

/* Public: Return the number of elements in the Array. */
static VALUE method_length(VALUE self)
{
	d2v_container *vector;
	Data_Get_Struct(self, d2v_container, vector);

	return(INT2NUM(vector->len));
}

/* Public: Return a Ruby Array containing the doubles within the data array. */
static VALUE method_to_a(VALUE self)
{
	unsigned long i;
	d2v_container *vector;
	VALUE rb_array = rb_ary_new();

	Data_Get_Struct(self, d2v_container, vector);
	for(i = 0; i < vector->len; i++)
	{
		rb_ary_store(rb_array, i, DBL2NUM(vector->data[i/2].f[i%2]));
	}

	return(rb_array);
}

/* Internal: Given another FloatArray object, perform an action specified via a
 * function pointer against both. */
static VALUE internal_apply_operation(VALUE self, VALUE obj, b_operation func)
{
	unsigned long size, i;
	int align;
	d2v_container *v1, *v2, *r;
	VALUE result_obj = allocate(SIMD_FloatArray);

	Data_Get_Struct(self, d2v_container, v1);
	Data_Get_Struct(obj, d2v_container, v2);
	Data_Get_Struct(result_obj, d2v_container, r);

	align = internal_align_vectors(v1->len, v2->len);

	/* Ensure that size will be the result of ceil(len / 2.0) */
	size = (v1->len + 1) / 2;
	r->data = internal_allocate_vector_array(v1->len);
	r->len = v1->len;

	switch(align)
	{
		case 0: /* Same size arrays */
			for(i = 0; i < size; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[i].v);
			}
			break;
		case 1: /* Operand is exactly 2 long (size of 1 sse register) */
			for(i = 0; i < size; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[0].v);
			}
			break;
		default: /* Self is a multiple of operand's length long */
			for(i = 0; i < size; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[i % v2->len].v);
			}
	}

	return(result_obj);
}

/* Internal: Allocate memory for the data array. */
static d2v_t *internal_allocate_vector_array(unsigned long size)
{
	d2v_t *vector = malloc(((size + (size % 2)) / 2 + 1) * sizeof(d2v_t));
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}

	return(vector);
}

/* Internal: Determine if two arrays can be acted upon, by being of equal
 * lengths or with the operand's length being a multiple of the data array's. */
static int internal_align_vectors(unsigned long v1, unsigned long v2)
{
	if((v1 % 2) != (v2 % 2))
	{
		rb_raise(rb_eArgError, "Both Vectors must be of even or odd length.");
	}

	if(v1 == v2)
	{
		return(0);
	}
	if(v2 == 2)
	{
		return(1);
	}
	if(v1 % v2 == 0)
	{
		return(2);
	}

	rb_raise(rb_eArgError, "Vector length must be evenly divisible by operand.");
	/* Never reached */
	return(-1);
}

/* Function: Multiply two vectors. */
static d2v func_multiply(d2v v1, d2v v2)
{
	return(v1 * v2);
}

/* Function: Divide two vectors. */
static d2v func_divide(d2v v1, d2v v2)
{
	return(v1 / v2);
}

/* Function: Add two vectors. */
static d2v func_add(d2v v1, d2v v2)
{
	return(v1 + v2);
}

/* Function: Subtract two vectors. */
static d2v func_subtract(d2v v1, d2v v2)
{
	return(v1 - v2);
}
