#include "simd_floatarray.h"

VALUE SIMD_FloatArray = Qnil;

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

static VALUE allocate(VALUE klass)
{
	d2v_container *vector = malloc(sizeof(d2v_container));
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}
	vector->data = NULL;

	return(Data_Wrap_Struct(klass, NULL, deallocate, vector));
}

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

static VALUE method_initialize(VALUE self, VALUE rb_array)
{
	d2v_container *vector;
	unsigned long n,m,i;

	Check_Type(rb_array, T_ARRAY);

	Data_Get_Struct(self, d2v_container, vector);
	vector->len = n = RARRAY_LEN(rb_array);
	vector->data = internal_allocate_vector_array(vector->len);

	m = n + (n % 2);
	for(i = 0; i < n; i++)
		vector->data[i/2].f[i%2] = NUM2DBL(rb_ary_entry(rb_array, i));

	if(n < m)
		vector->data[m/2].f[1] = 1.0;

	return(self);
}

static VALUE method_multiply(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_multiply));
}

static VALUE method_divide(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_divide));
}

static VALUE method_add(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_add));
}

static VALUE method_subtract(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, func_subtract));
}

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

	size = v1->len + (v1->len % 2);
	r->data = internal_allocate_vector_array(size);
	r->len = v1->len;

	switch(align)
	{
		case 0:
			for(i = 0; i < size / 2; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[i].v);
			}
			break;
		case 1:
			for(i = 0; i < size / 2; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[0].v);
			}
			break;
		default:
			for(i = 0; i < size / 2; i++)
			{
				r->data[i].v = func(v1->data[i].v, v2->data[i % v2->len].v);
			}
	}

	return(result_obj);
}

static VALUE method_length(VALUE self)
{
	d2v_container *vector;
	Data_Get_Struct(self, d2v_container, vector);

	return(INT2NUM(vector->len));
}

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

static d2v_t *internal_allocate_vector_array(unsigned long size)
{
	d2v_t *vector = malloc(((size + (size % 2)) / 2) * sizeof(d2v_t));
	if(vector == NULL)
	{
		rb_raise(rb_eNoMemError, "Unable to allocate memory");
	}

	return(vector);
}

static int internal_align_vectors(unsigned long v1, unsigned long v2)
{
	if(v1 == v2)
		return(0);
	if(v2 == 2)
		return(1);
	if(v1 % v2 == 0)
		return(2);

	rb_raise(rb_eArgError, "Vector length must be evenly divisible by operand.");
	/* Never reached */
	return(-1);
}

static d2v func_multiply(d2v v1, d2v v2)
{
	return(v1 * v2);
}

static d2v func_divide(d2v v1, d2v v2)
{
	return(v1 / v2);
}

static d2v func_add(d2v v1, d2v v2)
{
	return(v1 + v2);
}

static d2v func_subtract(d2v v1, d2v v2)
{
	return(v1 - v2);
}
