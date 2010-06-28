#include "complex_test.h"

/**
 * Annex G.6 ccos(z) = ccosh(iz)
 * Referecnce Annex G.6.2.4 The ccosh functions
 * ccosh(conj(z)) = conj(ccosh(z)) and ccosh is even.
 * ccosh(+0 + i0) returns 1 + i0.
 * ccosh(+i 0 + i ∞) returns NaN ± i0 (where the sign of the imaginary part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
 * ccosh(+0 + iNaN) returns NaN ± i0 (where the sign of the imaginary part of the result is unspecified).
 * ccosh(x + i ∞) returns NaN + iNaN and raises the ‘‘invalid’’ floating-point exception, for finite nonzero x.
 * ccosh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite nonzero x.
 * ccosh(+∞ + i0) returns +∞ + i0.
 * ccosh(+∞ + iy) returns +∞ cis(y), for finite nonzero y.
 * ccosh(+∞ + i ∞) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
 * ccosh(+∞ + iNaN) returns +∞ + iNaN.
 * ccosh(NaN + i0) returns NaN ± i0 (where the sign of the imaginary part of the result is unspecified).
 * ccosh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for all nonzero numbers y.
 * ccosh(NaN + iNaN) returns NaN + iNaN.
 */

int __FLT_ABI(test_function_ccos) ()
{
  /* cos (42.42) is positive.  sin (42.42) is negative */
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST(-0.0),   __FLT_CST(0.0), __FLT_CST(1.0), __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(-0.0),         INFINITY,       INFINITY, __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(-0.0),        __FLT_NAN,      __FLT_NAN, __FLT_CST(0.0), 0, 1)
  DEFINE_TEST (        -INFINITY,   __FLT_CST(0.0),      __FLT_NAN, __FLT_CST(0.0), 0, 1)
  DEFINE_TEST (        -INFINITY, __FLT_CST(42.42),      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        -INFINITY,         INFINITY,       INFINITY,      __FLT_NAN, 1, 0)
  DEFINE_TEST (        -INFINITY,        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),         INFINITY,       INFINITY,      -INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,   __FLT_CST(0.0),      __FLT_NAN, __FLT_CST(0.0), 0, 1)
  DEFINE_TEST (        __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,         INFINITY,       INFINITY,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(ccos);
}
