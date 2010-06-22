#ifndef compare_flt_include
#define compare_flt_include

#include <stdio.h>
#include <math.h>
#include <complex.h>

#define DELTA_FLOAT (2.0F * __FLT_EPSILON__)
#define DELTA_DOUBLE (2.0 * __DBL_EPSILON__)
#define DELTA_LDOUBLE (2.0L * __LDBL_EPSILON__)

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
  const val = (expected > in) ?
	   ((expected - in) > DELTA_FLOAT) :
	   ((in - expected) > DELTA_FLOAT);

#ifdef DEBUG
  if (val)
    printf("float test failed: expected %0.12f, got %0.12f, epsilon %0.12f\n",
	expected, in, DELTA_FLOAT);
#endif
  return val;
}

INLINE_M int
compare_dbl (const double expected, const double in)
{
  const val = (expected > in) ?
	   ((expected - in) > DELTA_DOUBLE) :
	   ((in - expected) > DELTA_DOUBLE);

#ifdef DEBUG
  if (val)
    printf("double test failed: expected %0.12f, got %0.12f, epsilon %0.12f\n",
	expected, in, DELTA_DOUBLE);
#endif
  return val;
}

INLINE_M int
compare_ldbl (const long double expected, const long double in)
{
  const val = (expected > in) ?
	   ((expected - in) > DELTA_LDOUBLE) :
	   ((in - expected) > DELTA_LDOUBLE);

#ifdef DEBUG
  if (val)
    printf("long double test failed: expected %0.12f, got %0.12f, epsilon %0.12f\n",
	expected, in, DELTA_LDOUBLE);
#endif
  return val;
}

INLINE_M int
compare_cflt (const complex float expected, const complex float in)
{
  return (compare_flt (crealf(expected), crealf(in)) ||
	  compare_flt (cimagf(expected), cimagf(in)));
}

INLINE_M int
compare_cdbl (const complex double expected, const complex double in)
{
  return (compare_dbl (creal(expected), creal(in)) ||
	  compare_dbl (cimag(expected), cimag(in)));
}

INLINE_M int
compare_cldbl (const complex long double expected,
	       const complex long double in)
{
  return (compare_ldbl (creall(expected), creall(in)) ||
	  compare_ldbl (cimagl(expected), cimagl(in)));
}
#endif /* compare_flt_include */
