#include "ruby.h"
#include "simd_types.h"

static VALUE allocate(VALUE klass);
static void deallocate(d2v_container *floatarray);

static VALUE method_initialize(VALUE self, VALUE rb_array);
static VALUE method_multiply(VALUE self, VALUE obj);
static VALUE method_length(VALUE self);
static VALUE method_to_a(VALUE self);

static d2v_t *internal_allocate_vector_array(unsigned long size);
static int internal_align_vectors(unsigned long v1, unsigned long v2);
static VALUE internal_apply_operation(VALUE self, VALUE obj, b_operation func);

static d2v func_multiply(d2v v1, d2v v2);
