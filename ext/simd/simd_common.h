#pragma once

#include "ruby.h"
#include "simd_types.h"

VALUE allocate(VALUE klass);
void deallocate(vector_t *vector);

VALUE method_length(VALUE self);

void *internal_allocate_vector_array(unsigned long count, size_t size);
int internal_align_vectors(unsigned long v1, unsigned long v2, unsigned int modulo);
