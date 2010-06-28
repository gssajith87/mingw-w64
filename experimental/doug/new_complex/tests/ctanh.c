#include "complex_test.h"

/**
 * Annex G.6.2.6 The ctanh functions
 * ctanh(conj(z)) = conj(ctanh(z))and ctanh is odd.
 * ctanh(+0 + i0) returns +0 + i0.
 * ctanh(x + i ∞) returns NaN + iNaN and raises the ‘‘invalid’’ floating-point exception, for finite x.
 * ctanh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite x.
 * ctanh(+∞ + iy) returns 1 + i0 sin(2y), for positive-signed finite y.
 * ctanh(+∞ + i ∞) returns 1 ± i0 (where the sign of the imaginary part of the result is unspecified).
 * ctanh(+∞ + iNaN) returns 1 ± i0 (where the sign of the imaginary part of the result is unspecified).
 * ctanh(NaN + i0) returns NaN + i0.
 * ctanh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for all nonzero numbers y.
 * ctanh(NaN + iNaN) returns NaN + iNaN.
 */

int __FLT_ABI(test_function_ctanh) () 
{
  /* sin(2*42.42) is negative */
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST(0.0),   __FLT_CST(0.0), __FLT_CST(0.0),  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY,      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42), __FLT_CST(1.0), __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY, __FLT_CST(1.0),  __FLT_CST(0.0), 0, 1)
  DEFINE_TEST (        INFINITY,        __FLT_NAN, __FLT_CST(1.0),  __FLT_CST(0.0), 0, 1)
  DEFINE_TEST (       __FLT_NAN,   __FLT_CST(0.0),      __FLT_NAN,  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY,      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,      __FLT_NAN,       __FLT_NAN, 0, 0)

  TESTS_END

  /* these are some checks at boundary conditions of zeros with sin (2y).  */
  /* these are actually tested against the value returned by the sin function */
  /* sin(0) = +0.0  sin(PI) = +0.0 sin(2PI) = +0.0 */
  TESTS_START(pis)

  DEFINE_TEST (INFINITY, __FLT_CST(0.0), __FLT_CST(1.0), __FLT_CST(0.0) * __FLT_ABI(sin) (__FLT_CST(0.0)),           0, 0)
  DEFINE_TEST (INFINITY,     __FLT_PI_2, __FLT_CST(1.0), __FLT_CST(0.0) * __FLT_ABI(sin) (__FLT_CST(4.0) * __FLT_ABI(atan) (__FLT_CST(1.0))), 0, 0)
  DEFINE_TEST (INFINITY,       __FLT_PI, __FLT_CST(1.0), __FLT_CST(0.0) * __FLT_ABI(sin) (__FLT_CST(8.0) * __FLT_ABI(atan) (__FLT_CST(1.0))), 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(ctanh) | RUN_FUNCTION_TESTS(ctanh, pis);
}
