#include "complex_test.h"

/**
 * Annex G.6 casin(z) = -i casinh(iz)
 * Reference: Annex G.6.2.2 The casinh functions
 * casinh(conj(z)) = conj(casinh(z)) and casinh is odd.
 * casinh(+0 + i0) returns 0 + i0.
 * casinh(x + i ∞) returns +∞ + iπ /2 for positive-signed finite x.
 * casinh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite x.
 * casinh(+∞ + iy) returns +∞ + i0 for positive-signed finite y.
 * casinh(+∞ + i ∞) returns +∞ + iπ /4.
 * casinh(+∞ + iNaN) returns +∞ + iNaN.
 * casinh(NaN + i0) returns NaN + i0.
 * casinh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite nonzero y.
 * casinh(NaN + i ∞) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified).
 * casinh(NaN + iNaN) returns NaN + iNaN.
 */

int main()
{
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST(0.0),   __FLT_CST(0.0), __FLT_CST(0.0),__FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(0.0),	__FLT_NAN, __FLT_CST(0.0),     __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,      __FLT_NAN,     __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY, __FLT_CST(0.0),      INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42),     __FLT_PI_2,      INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY,     __FLT_PI_4,      INFINITY, 0, 0)
  DEFINE_TEST (        INFINITY,        __FLT_NAN,      __FLT_NAN,      INFINITY, 0, 1)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,     __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY,      __FLT_NAN,      INFINITY, 0, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,      __FLT_NAN,     __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(casin);
}
