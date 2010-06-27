#include "complex_test.h"

/**
 * Annex G.6.1.1 The cacos functions
 * cacos (conj (z)) = conj (cacos (z)).
 * cacos(±0 + i0) returns π /2 − i0.
 * cacos(±0 + iNaN) returns π /2 + iNaN.
 * cacos(x + i ∞) returns π /2 − i ∞, for finite x.
 * cacos(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for nonzero finite x.
 * cacos(−∞ + iy) returns π − i ∞, for positive-signed finite y.
 * cacos(+∞ + iy) returns +0 − i ∞, for positive-signed finite y.
 * cacos(−∞ + i ∞) returns 3π /4 − i ∞.
 * cacos(+∞ + i ∞) returns π /4 − i ∞.
 * cacos(±∞ + iNaN) returns NaN ± i ∞ (where the sign of the imaginary part of the result is unspecified).
 * cacos(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite y.
 * cacos(NaN + i ∞) returns NaN − i ∞.
 * cacos(NaN + iNaN) returns NaN + iNaN.
 */

int main()
{
  DEFAULT_TESTS_START

  DEFINE_TEST ( __FLT_CST( 0.0),   __FLT_CST(0.0),     __FLT_PI_2, __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST ( __FLT_CST(-0.0),   __FLT_CST(0.0),     __FLT_PI_2, __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST ( __FLT_CST( 0.0),        __FLT_NAN,     __FLT_PI_2,       __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(-0.0),        __FLT_NAN,     __FLT_PI_2,       __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY,     __FLT_PI_2,       -INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (       -INFINITY, __FLT_CST(42.42),       __FLT_PI,       -INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42), __FLT_CST(0.0),       -INFINITY, 0, 0)
  DEFINE_TEST (       -INFINITY,         INFINITY,   __FLT_PI_3_4,       -INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY,     __FLT_PI_4,       -INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY,        __FLT_NAN,      __FLT_NAN,        INFINITY, 0, 1)
  DEFINE_TEST (       -INFINITY,        __FLT_NAN,      __FLT_NAN,        INFINITY, 0, 1)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,       __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY,      __FLT_NAN,       -INFINITY, 0, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,      __FLT_NAN,       __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(cacos);
}
