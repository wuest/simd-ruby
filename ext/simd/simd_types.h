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

typedef struct d2v_container
{
	d2v_t *data;
	unsigned long len;
} d2v_container;

typedef d2v (*b_operation)(d2v v1, d2v v2);
