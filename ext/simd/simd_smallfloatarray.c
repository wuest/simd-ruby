#include "simd_smallfloatarray.h"
#include "simd_intarray.h"

VALUE SIMD_SmallFloatArray = Qnil;

/* Internal: Create the SIMD::FloatArray class. */
void Init_SIMD_SmallFloatArray(VALUE parent)
{
	SIMD_SmallFloatArray = rb_define_class_under(parent, "SmallFloatArray", rb_cObject);
	rb_define_alloc_func(SIMD_SmallFloatArray, allocate);
	rb_define_method(SIMD_SmallFloatArray, "initialize", method_initialize, 1);
	rb_define_method(SIMD_SmallFloatArray, "*", method_multiply, 1);
	rb_define_method(SIMD_SmallFloatArray, "/", method_divide, 1);
	rb_define_method(SIMD_SmallFloatArray, "+", method_add, 1);
	rb_define_method(SIMD_SmallFloatArray, "-", method_subtract, 1);
	rb_define_method(SIMD_SmallFloatArray, "sqrt", method_sqrt, 0);
	rb_define_method(SIMD_SmallFloatArray, "&", method_and, 1);
	rb_define_method(SIMD_SmallFloatArray, "|", method_or, 1);
	rb_define_method(SIMD_SmallFloatArray, "^", method_xor, 1);
	rb_define_method(SIMD_SmallFloatArray, "gt", method_gt, 1);
	rb_define_method(SIMD_SmallFloatArray, "lt", method_lt, 1);
	rb_define_method(SIMD_SmallFloatArray, "gte", method_gte, 1);
	rb_define_method(SIMD_SmallFloatArray, "lte", method_lte, 1);
	rb_define_method(SIMD_SmallFloatArray, "eq", method_eq, 1);
	rb_define_method(SIMD_SmallFloatArray, "neq", method_neq, 1);
	rb_define_method(SIMD_SmallFloatArray, ">", method_gt, 1);
	rb_define_method(SIMD_SmallFloatArray, "<", method_lt, 1);
	rb_define_method(SIMD_SmallFloatArray, ">=", method_gte, 1);
	rb_define_method(SIMD_SmallFloatArray, "<=", method_lte, 1);
	rb_define_method(SIMD_SmallFloatArray, "length", method_length, 0);
	rb_define_method(SIMD_SmallFloatArray, "to_a", method_to_a, 0);
}

/* Public: Initialize the FloatArray object given a Ruby Array of values
 * which can be cast to a double. */
static VALUE method_initialize(VALUE self, VALUE rb_array)
{
	vector_t *vector;
	f4v_t *data;
	unsigned long long int n,i;

	Check_Type(rb_array, T_ARRAY);
	Data_Get_Struct(self, vector_t, vector);

	vector->len = n = RARRAY_LEN(rb_array);

	if(vector->len < 4)
	{
		rb_raise(rb_eArgError, "Vectors must be at least 4 long");
	}

	vector->data = internal_allocate_vector_array(vector->len);

	data = (f4v_t *)vector->data;
	for(i = 0; i < vector->len; i++)
	{
		data[i/4].f[i%4] = (float)NUM2DBL(rb_ary_entry(rb_array, i));
	}

	internal_sanitize_unaligned_final_vector(vector, sizeof(float));

	return(self);
}

/* Public: Multiply values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_multiply(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_multiply));
}

/* Public: Divide values contained in the data array by those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_divide(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_divide));
}

/* Public: add values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_add(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_add));
}

/* Public: Subtract values contained in another FloatArray object from those
 * contained in the current data array object, returning a new FloatArray. */
static VALUE method_subtract(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_subtract));
}

/* Public: Compute the square root of values contained in a SmallFloatArray
 * object, returning a new SmallFloatArray. */
static VALUE method_sqrt(VALUE self)
{
	return(internal_apply_unary_operation(self, sizeof(float), SIMD_SmallFloatArray, func_sqrt));
}

/* Public: and values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_and(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_and));
}

/* Public: or values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_or(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_or));
}

/* Public: xor values contained in the data array with those contained in
 * another FloatArray object, returning a new FloatArray. */
static VALUE method_xor(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_SmallFloatArray, func_xor));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * -1 if the data array's value is greater, and 0 otherwise. */
static VALUE method_gt(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_gt));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * -1 if the data array's value is less, and 0 otherwise. */
static VALUE method_lt(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_lt));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * -1 if the data array's value is greater or equal, and 0 otherwise. */
static VALUE method_gte(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_gte));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * -1 if the data array's value is less or equal, and 0 otherwise. */
static VALUE method_lte(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_lte));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * -1 if the data array's value is equal, and 0 otherwise. */
static VALUE method_eq(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_eq));
}

/* Public: Compare values contained in the data array with those contained in
 * another SmallFloatArray object, return a new IntArray with each element being
 * 0 if the data array's value is equal, and -1 otherwise. */
static VALUE method_neq(VALUE self, VALUE obj)
{
	return(internal_apply_operation(self, obj, sizeof(float), SIMD_IntArray, func_neq));
}

/* Public: Return a Ruby Array containing the doubles within the data array. */
static VALUE method_to_a(VALUE self)
{
	unsigned long long int i;
	vector_t *vector;
	f4v_t *data;
	VALUE rb_array = rb_ary_new();

	Data_Get_Struct(self, vector_t, vector);
	data = (f4v_t *)vector->data;
	for(i = 0; i < vector->len; i++)
	{
		rb_ary_store(rb_array, i, DBL2NUM(data[i/4].f[i%4]));
	}

	return(rb_array);
}

/* Function: Multiply two vectors. */
static void func_multiply(void *v1, void *v2, void *r)
{
	*(f4v *)r = *(f4v *)v1 * *(f4v *)v2;
}

/* Function: Divide two vectors. */
static void func_divide(void *v1, void *v2, void *r)
{
	*(f4v *)r = *(f4v *)v1 / *(f4v *)v2;
}

/* Function: Add two vectors. */
static void func_add(void *v1, void *v2, void *r)
{
	*(f4v *)r = *(f4v *)v1 + *(f4v *)v2;
}

/* Function: Subtract two vectors. */
static void func_subtract(void *v1, void *v2, void *r)
{
	*(f4v *)r = *(f4v *)v1 - *(f4v *)v2;
}

/* Function: Compute square root for a vector. */
static void func_sqrt(void *v1, void *r)
{
	(*(f4v *)r)[0] = sqrt((*(f4v *)v1)[0]);
	(*(f4v *)r)[1] = sqrt((*(f4v *)v1)[1]);
	(*(f4v *)r)[2] = sqrt((*(f4v *)v1)[2]);
	(*(f4v *)r)[3] = sqrt((*(f4v *)v1)[3]);
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
	*(i4v *)r = (*(f4v *)v1 > *(f4v *)v2);
}

/* Function: Compare vectors, return -1 if v1 is less than v2, 0 otherwise */
static void func_lt(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(f4v *)v1 < *(f4v *)v2);
}

/* Function: Compare vectors, return -1 if v1 is greater than v2, 0 otherwise */
static void func_gte(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(f4v *)v1 >= *(f4v *)v2);
}

/* Function: Compare vectors, return -1 if v1 is less than v2, 0 otherwise */
static void func_lte(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(f4v *)v1 <= *(f4v *)v2);
}

/* Function: Compare vectors, return -1 if v1 is equal to v2, 0 otherwise */
static void func_eq(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(f4v *)v1 == *(f4v *)v2);
}

/* Function: Compare vectors, return 0 if v1 is equal to v2, -1 otherwise */
static void func_neq(void *v1, void *v2, void *r)
{
	*(i4v *)r = (*(f4v *)v1 != *(f4v *)v2);
}
