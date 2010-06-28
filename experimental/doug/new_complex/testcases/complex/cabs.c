#include "complex_test.h"

/**
 * Annex F.9.4.3 of the hypot function
 * cabs (z) == hypot (__real__ z, __imag__ z).
 * hypot (x, y) == hypot (x, -y), therefore is conjugate.
 * hypot (x, y) == hypot (y, x).
 * hypot (x, +/-0) == fabs (x).
 * hypot (+/-inf, y) == +inf, for all y (including NaN).
 */
  
int __FLT_ABI(test_function_cabs) ()
{
  DEFAULT_TESTS_START

  DEFINE_TEST (__FLT_CST( 0.0), __FLT_CST(42.42), __FLT_CST(42.42), __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-0.0), __FLT_CST(42.42), __FLT_CST(42.42), __FLT_NAN, 0, 0)
  DEFINE_TEST (       INFINITY, __FLT_CST(42.42),         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (      -INFINITY, __FLT_CST(42.42),         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (       INFINITY,        __FLT_NAN,         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (      -INFINITY,        __FLT_NAN,         INFINITY, __FLT_NAN, 0, 0)

  /* check x,y == y,x */
  DEFINE_TEST (__FLT_CST( 42.42), __FLT_CST(0.0), __FLT_CST(42.42), __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42), __FLT_CST(0.0), __FLT_CST(42.42), __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),       INFINITY,         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),       INFINITY,         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,       INFINITY,         INFINITY, __FLT_NAN, 0, 0)
  DEFINE_TEST (       -__FLT_NAN,       INFINITY,         INFINITY, __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(cabs);
}
