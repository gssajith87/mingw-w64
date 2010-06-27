#include "complex_test.h"

/**
 * Annex G.6.2.5 The csinh functions
 * csinh(conj(z)) = conj(csinh(z)) and csinh is odd.
 * csinh(+0 + i0) returns +0 + i0.
 * csinh(+0 + i ∞) returns ±0 + iNaN (where the sign of the real part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
 * csinh(+0 + iNaN) returns ±0 + iNaN (where the sign of the real part of the result is unspecified).
 * csinh(x + i ∞) returns NaN + iNaN and raises the ‘‘invalid’’ floating-point exception, for positive finite x.
 * csinh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite nonzero x.
 * csinh(+∞ + i0) returns +∞ + i0.
 * csinh(+∞ + iy) returns +∞ cis(y), for positive finite y.
 * csinh(+∞ + i ∞) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
 * csinh(+∞ + iNaN) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified).
 * csinh(NaN + i0) returns NaN + i0.
 * csinh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for all nonzero numbers y.
 * csinh(NaN + iNaN) returns NaN + iNaN.
 */

int main()
{
  /* cos (42.42) is positive, sin(42.42) is negative */
  DEFAULT_TESTS_START

  DEFINE_TEST ( __FLT_CST( 0.0),   __FLT_CST(0.0), __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DEFINE_TEST ( __FLT_CST( 0.0),         INFINITY, __FLT_CST(0.0),      __FLT_NAN, 1, 0)
  DEFINE_TEST ( __FLT_CST( 0.0),        __FLT_NAN, __FLT_CST(0.0),      __FLT_NAN, 1, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        INFINITY,   __FLT_CST(0.0),       INFINITY, __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42),       INFINITY,      -INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY,       INFINITY,      __FLT_NAN, 1, 0)
  DEFINE_TEST (        INFINITY,        __FLT_NAN,       INFINITY,      __FLT_NAN, 1, 0)
  DEFINE_TEST (       __FLT_NAN,   __FLT_CST(0.0),      __FLT_NAN, __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(csinh);
}
