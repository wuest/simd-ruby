#pragma once

#include "ruby.h"
#include "simd_types.h"

VALUE allocate(VALUE klass);
void deallocate(vector_t *vector);

VALUE method_length(VALUE self);

void *internal_allocate_vector_array(unsigned long count);
int internal_align_vectors(unsigned long v1, unsigned long v2, unsigned int modulo);
VALUE internal_apply_operation(VALUE self, VALUE obj, size_t size, VALUE klass, b_operation func);
void internal_sanitize_unaligned_final_vector(vector_t *rv, size_t size);
