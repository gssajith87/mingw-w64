#ifndef compare_flt_include
#define compare_flt_include

#include <math.h>
#include <complex.h>
#define DELTA_FLOAT (2.0F * __FLT_MIN__)
#define DELTA_DOUBLE (4.0 * __DBL_MIN__)
#define DELTA_LDOUBLE (16.0L * __LDBL_MIN__)

#if defined (__STRICT_ANSI__)
#define INLINE_M
#else
#if defined (__STDC_VERSION__) && (__STDC_VERSION__) == (199901L)
#define INLINE_M static inline
#else
#define INLINE_M extern inline
#endif
#endif

/**
 * Compares expected and test values with a delta tolerance.
 * 0 for pass, 1 for fail.
 * TODO:
 * Tune comparison precision
 **/

INLINE_M int
compare_flt (const float expected, const float in)
{
  return ((fabsf (expected - in)) <= DELTA_FLOAT) ? 0 : 1;
}

INLINE_M int
compare_dbl (const double expected, const double in)
{
  return ((fabs (expected - in)) <= DELTA_DOUBLE) ? 0 : 1;
}

INLINE_M int
compare_ldbl (const long double expected, const long double in)
{
  return ((fabsl (expected - in)) <= DELTA_LDOUBLE) ? 0 : 1;
}

INLINE_M int
compare_cflt (const complex float expected, const complex float in)
{
  long double realpart_ex = crealf (expected);
  long double imagpart_ex = cimagf (expected);
  long double realpart_in = crealf (in);
  long double imagpart_in = cimagf (in);
  return (compare_flt (realpart_ex, realpart_in) |
	  compare_ldbl (imagpart_ex, imagpart_in));
}

INLINE_M int
compare_cdbl (const complex double expected, const complex double in)
{
  long double realpart_ex = creal (expected);
  long double imagpart_ex = cimag (expected);
  long double realpart_in = creal (in);
  long double imagpart_in = cimag (in);
  return (compare_dbl (realpart_ex, realpart_in) |
	  compare_ldbl (imagpart_ex, imagpart_in));
}

INLINE_M int
compare_cldbl (const complex long double expected,
	       const complex long double in)
{
  long double realpart_ex = creall (expected);
  long double imagpart_ex = cimagl (expected);
  long double realpart_in = creall (in);
  long double imagpart_in = cimagl (in);
  return (compare_ldbl (realpart_ex, realpart_in) |
	  compare_ldbl (imagpart_ex, imagpart_in));
}
#endif /* compare_flt_include */
