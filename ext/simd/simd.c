#include "simd.h"
VALUE SIMD       = Qnil;

void Init_simd()
{
	SIMD = rb_define_module("SIMD");
	Init_SIMD_FloatArray(SIMD);
}
