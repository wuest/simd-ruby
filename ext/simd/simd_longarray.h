#include "ruby.h"
#include "simd_common.h"

extern VALUE SIMD_LongArray;

static VALUE method_initialize(VALUE self, VALUE rb_array);
static VALUE method_multiply(VALUE self, VALUE obj);
static VALUE method_divide(VALUE self, VALUE obj);
static VALUE method_add(VALUE self, VALUE obj);
static VALUE method_and(VALUE self, VALUE obj);
static VALUE method_or(VALUE self, VALUE obj);
static VALUE method_xor(VALUE self, VALUE obj);
static VALUE method_subtract(VALUE self, VALUE obj);
static VALUE method_to_a(VALUE self);

static void func_multiply(void *v1, void *v2, void *r);
static void func_divide(void *v1, void *v2, void *r);
static void func_add(void *v1, void *v2, void *r);
static void func_subtract(void *v1, void *v2, void *r);
static void func_and(void *v1, void *v2, void *r);
static void func_or(void *v1, void *v2, void *r);
static void func_xor(void *v1, void *v2, void *r);
