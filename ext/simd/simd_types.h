#pragma once

/*
 * Types for SmallFloatArray
 *
 * Since ruby internally uses doubles for the Float type, SIMD::SmallFloatArray
 * provides reduced-size floats for faster operation when it's known that the
 * lack of precision and range will not be a detriment.
 */
typedef float __attribute__ ((vector_size (16))) f4v;
typedef union f4v_t
{
	f4v v;
	float f[4];
} f4v_t;

/*
 * Types for FloatArray
 *
 * Since ruby internally uses doubles for the Float type, SIMD::FloatArray will
 * use packed double operations by default.
 */
typedef double __attribute__ ((vector_size (16))) d2v;
typedef union d2v_t
{
	d2v v;
	double f[2];
} d2v_t;

/*
 * Types for IntArray
 */
typedef int __attribute__ ((vector_size (16))) i4v;
typedef union i4v_t
{
	i4v v;
	int f[4];
} i4v_t;

/*
 * Types for BooleanArray
 */
typedef bool bv;
typedef union bv_t
{
	bv v;
	bool;
} bv_t;

/*
 * Types for LongArray
 */
typedef long long int __attribute__ ((vector_size (16))) l2v;
typedef union l2v_t
{
	l2v v;
	long long int f[2];
} l2v_t;

typedef struct vector_t
{
	void *data;
	unsigned long long int len;
} vector_t;

typedef void (b_operation)(void *v1, void *v2, void *r);
