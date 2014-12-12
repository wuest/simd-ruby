#include "ruby.h"
#include "simd_common.h"

/*
static VALUE allocate(VALUE klass);
static void deallocate(vector_t *vector);
*/

static VALUE method_initialize(VALUE self, VALUE rb_array);
static VALUE method_multiply(VALUE self, VALUE obj);
static VALUE method_divide(VALUE self, VALUE obj);
static VALUE method_add(VALUE self, VALUE obj);
static VALUE method_subtract(VALUE self, VALUE obj);
static VALUE method_to_a(VALUE self);

/*
static f4v_t *internal_allocate_vector_array(unsigned long size);
static int internal_align_vectors(unsigned long v1, unsigned long v2);
*/
static VALUE internal_apply_operation(VALUE self, VALUE obj, bf_operation func);

static f4v func_multiply(f4v v1, f4v v2);
static f4v func_divide(f4v v1, f4v v2);
static f4v func_add(f4v v1, f4v v2);
static f4v func_subtract(f4v v1, f4v v2);
