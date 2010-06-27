#include "complex_test.h"

/**
 * Annex G.6.2.3 The catanh functions
 * catanh(conj(z)) = conj(catanh(z)) and catanh is odd.
 * catanh(+0 + i0) returns +0 + i0.
 * catanh(+0 + iNaN) returns +0 + iNaN.
 * catanh(+1 + i0) returns +∞ + i0 and raises the ‘‘divide-by-zero’’ floating-point exception.
 * catanh(x + i ∞) returns +0 + iπ /2, for finite positive-signed x.
 * catanh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for nonzero finite x.
 * catanh(+∞ + iy) returns +0 + iπ /2, for finite positive-signed y.
 * catanh(+∞ + i ∞) returns +0 + iπ /2.
 * catanh(+∞ + iNaN) returns +0 + iNaN.
 * catanh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite y.
 * catanh(NaN + i ∞) returns ±0 + iπ /2 (where the sign of the real part of the result is unspecified).
 * catanh(NaN + iNaN) returns NaN + iNaN.
 */

int main() 
{
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST(0.0),   __FLT_CST(0.0), __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(0.0),        __FLT_NAN, __FLT_CST(0.0),      __FLT_NAN, 0, 0)
  DEFINE_TEST (  __FLT_CST(1.0),   __FLT_CST(0.0),       INFINITY, __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY, __FLT_CST(0.0),     __FLT_PI_2, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        INFINITY,   __FLT_CST(0.0), __FLT_CST(0.0),     __FLT_PI_2, 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42), __FLT_CST(0.0),     __FLT_PI_2, 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY, __FLT_CST(0.0),     __FLT_PI_2, 0, 0)
  DEFINE_TEST (        INFINITY,        __FLT_NAN, __FLT_CST(0.0),      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,   __FLT_CST(0.0),      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),      __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY, __FLT_CST(0.0),     __FLT_PI_2, 1, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,      __FLT_NAN,      __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(catanh);
}
