#include "ruby.h"
#include "simd_common.h"

/*
static VALUE allocate(VALUE klass);
static void deallocate(d2v_container *floatarray);
*/

static VALUE method_initialize(VALUE self, VALUE rb_array);
static VALUE method_multiply(VALUE self, VALUE obj);
static VALUE method_divide(VALUE self, VALUE obj);
static VALUE method_add(VALUE self, VALUE obj);
static VALUE method_subtract(VALUE self, VALUE obj);
static VALUE method_to_a(VALUE self);

/*
static d2v_t *internal_allocate_vector_array(unsigned long size);
static int internal_align_vectors(unsigned long v1, unsigned long v2);
*/
static VALUE internal_apply_operation(VALUE self, VALUE obj, b_operation func);

static d2v func_multiply(d2v v1, d2v v2);
static d2v func_divide(d2v v1, d2v v2);
static d2v func_add(d2v v1, d2v v2);
static d2v func_subtract(d2v v1, d2v v2);
