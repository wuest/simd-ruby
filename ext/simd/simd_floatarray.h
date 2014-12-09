#include "ruby.h"

typedef double __attribute__ ((vector_size (16))) v2d;
typedef union d2v_t
{
	v2d v;
	double f[2];
} d2v_t;

typedef struct double_vector_wrapper
{
	d2v_t *data;
	unsigned long len;
} double_vector_wrapper;

static VALUE allocate(VALUE klass);
static void deallocate(double_vector_wrapper *floatarray);

static VALUE method_initialize(VALUE self, VALUE rb_array);
static VALUE method_multiply(VALUE self, VALUE obj);
static VALUE method_length(VALUE self);
static VALUE method_to_a(VALUE self);
