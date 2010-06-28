#include "complex_test.h"

/**
 * Annex G.6.3.1 The cexp functions
 * cexp(conj(z)) = conj(cexp(z)).
 * cexp(±0 + i0) returns 1 + i0.
 * cexp(x + i ∞) returns NaN + iNaN and raises the ‘‘invalid’’ floating-point exception, for finite x.
 * cexp(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for finite x.
 * cexp(+∞ + i0) returns +∞ + i0.
 * cexp(−∞ + iy) returns +0 cis(y), for finite y.
 * cexp(+∞ + iy) returns +∞ cis(y), for finite nonzero y.
 * cexp(−∞ + i ∞) returns ±0 ± i0 (where the signs of the real and imaginary parts of the result are unspecified).
 * cexp(+∞ + i ∞) returns ±∞ + iNaN and raises the ‘‘invalid’’ floating-point exception (where the sign of the real part of the result is unspecified).
 * cexp(−∞ + iNaN) returns ±0 ± i0 (where the signs of the real and imaginary parts of the result are unspecified).
 * cexp(+∞ + iNaN) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified).
 * cexp(NaN + i0) returns NaN + i0.
 * cexp(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for all nonzero numbers y.
 * cexp(NaN + iNaN) returns NaN + iNaN.
 */

int __FLT_ABI(test_function_cexp) () 
{
  /* cos(42.42) is positive, sin(42.42) is negative */
  /* cos(0), sin(0) positive. */
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST( 0.0),   __FLT_CST(0.0),  __FLT_CST(1.0),  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(-0.0),   __FLT_CST(0.0),  __FLT_CST(1.0),  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42),         INFINITY,       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42),        __FLT_NAN,       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),         INFINITY,       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),        __FLT_NAN,       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (         INFINITY,   __FLT_CST(0.0),        INFINITY,  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (        -INFINITY, __FLT_CST(42.42),  __FLT_CST(0.0), __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST (        -INFINITY,   __FLT_CST(0.0),  __FLT_CST(0.0),  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (         INFINITY, __FLT_CST(42.42),        INFINITY,       -INFINITY, 0, 0)
  DEFINE_TEST (        -INFINITY,         INFINITY,  __FLT_CST(0.0),  __FLT_CST(0.0), 1, 1)
  DEFINE_TEST (         INFINITY,         INFINITY,        INFINITY,       __FLT_NAN, 1, 0)
  DEFINE_TEST (        -INFINITY,        __FLT_NAN,  __FLT_CST(0.0),  __FLT_CST(0.0), 1, 1)
  DEFINE_TEST (         INFINITY,        __FLT_NAN,        INFINITY,       __FLT_NAN, 1, 0)
  DEFINE_TEST (        __FLT_NAN,   __FLT_CST(0.0),       __FLT_NAN,  __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (        __FLT_NAN, __FLT_CST(42.42),       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,         INFINITY,       __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (        __FLT_NAN,        __FLT_NAN,       __FLT_NAN,       __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(cexp);
}
