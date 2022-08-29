#include "simd_intarray.h"

VALUE SIMD_IntArray = Qnil;

/* Internal: Create the SIMD::FloatArray class. */
void Init_SIMD_IntArray(VALUE parent)
{
	SIMD_IntArray = rb_define_class_under(parent, "IntArray", rb_cObject);
	rb_define_alloc_func(SIMD_IntArray, allocate);
	rb_define_method(SIMD_IntArray, "initialize", method_initialize, 1);
	rb_define_method(SIMD_IntArray, "*", method_multiply, 1);
	rb_define_method(SIMD_IntArray, "/", method_divide, 1);
	rb_define_method(SIMD_IntArray, "+", method_add, 1);
	rb_define_method(SIMD_IntArray, "-", method_subtract, 1);
	rb_define_method(SIMD_IntArray, "&", method_and, 1);
	rb_define_method(SIMD_IntArray, "|", method_or, 1);
	rb_define_method(SIMD_IntArray, "^", method_xor, 1);
	rb_define_method(SIMD_IntArray, "gt", method_gt, 1);
	rb_define_method(SIMD_IntArray, "lt", method_lt, 1);
	rb_define_method(SIMD_IntArray, ">", method_gt, 1);
	rb_define_method(SIMD_IntArray, "<", method_lt, 1);
	rb_define_method(SIMD_IntArray, "length", method_length, 0);
	rb_define_method(SIMD_IntArray, "to_a", method_to_a, 0);
}

/* Public: Initialize the FloatArray object given a Ruby Array of values
 * which can be cast to a double. */
static VALUE method_initialize(VALUE self, VALUE rb_array)
{
	vector_t *vector;
	i4v_t *data;
	unsigned long long int n,i;

	Check_Type(rb_array, T_ARRAY);
	Data_Get_Struct(self, vector_t, vector);

	vector->len = n = RARRAY_LEN(rb_array);

	if(vector->len < 4)
	{
		rb_raise(rb_eArgError, "Vectors must be at least 4 long");
	}

	vector->data = internal_allocate_vector_array(vector->len);

	data = (i4v_t *)vector->data;
	for(i = 0; i < vector->len; i++)
	{
		data[i/4].f[i%4] = NUM2INT(rb_ary_entry(rb_array, i));
	}

	internal_sanitize_unaligned_final_vector(vector, sizeof(int));

	return(self);
}

/* Public: Multiply values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_multiply(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_multiply));
}

/* Public: Divide values contained in the data array by those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_divide(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_divide));
}

/* Public: add values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_add(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_add));
}

/* Public: and values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_and(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_and));
}

/* Public: or values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_or(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_or));
}

/* Public: xor values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_xor(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_xor));
}

/* Public: Compare values contained in the data array with those contained in
 * another IntArray object, return a new IntArray with each element being -1
 * if the data array's value is greater, and 0 otherwise. */
static VALUE method_gt(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_gt));
}

/* Public: Compare values contained in the data array with those contained in
 * another IntArray object, return a new IntArray with each element being -1 if
 * the data array's value is less, and 0 otherwise. */
static VALUE method_lt(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_lt));
}

/* Public: Subtract values contained in another FloatArray object from those
 * contained in the current data array object, returning a new FloatArray. */
static VALUE method_subtract(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(int), SIMD_IntArray, func_subtract));
}

/* Public: Return a Ruby Array containing the doubles within the data array. */
static VALUE method_to_a(VALUE self)
{
	unsigned long long int i;
	vector_t *vector;
	i4v_t *data;
	VALUE rb_array = rb_ary_new();

	Data_Get_Struct(self, vector_t, vector);
	data = (i4v_t *)vector->data;
	for(i = 0; i < vector->len; i++)
	{
		rb_ary_store(rb_array, i, INT2NUM(data[i/4].f[i%4]));
	}

	return(rb_array);
}

/* Function: Multiply two vectors. */
static void func_multiply(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 * *(i4v *)v2;
}

/* Function: Divide two vectors. */
static void func_divide(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 / *(i4v *)v2;
}

/* Function: Add two vectors. */
static void func_add(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 + *(i4v *)v2;
}

/* Function: Subtract two vectors. */
static void func_subtract(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 - *(i4v *)v2;
}

/* Function: Perform a binary AND on two vectors. */
static void func_and(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 & *(i4v *)v2;
}

/* Function: Perform a binary OR on two vectors. */
static void func_or(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 | *(i4v *)v2;
}

/* Function: Perform a binary XOR on two vectors. */
static void func_xor(void *v1, void *v2, void *r)
{
	*(i4v *)r = *(i4v *)v1 ^ *(i4v *)v2;
}

/* Function: Compare vectors, return -1 if v1 is greater than v2, 0 otherwise */
static void func_gt(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(i4v *)v1 > *(i4v *)v2);
}

/* Function: Compare vectors, return -1 if v1 is less than v2, 0 otherwise */
static void func_lt(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(i4v *)v1 < *(i4v *)v2);
}
