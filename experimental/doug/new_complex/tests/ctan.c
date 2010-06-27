#include "complex_test.h"

/**
 * Annex G.6 ctan(z) = -i ctanh(iz)
 * Reference: Annex G.6.2.6 The ctanh functions
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

int main() 
{
  /* sin (42.42) is negative */
  DEFAULT_TESTS_START

  DEFINE_TEST (  __FLT_CST(0.0),   __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(0.0),         INFINITY,  __FLT_CST(0.0), __FLT_CST(1.0), 0, 0)
  DEFINE_TEST (  __FLT_CST(0.0),        __FLT_NAN,  __FLT_CST(0.0),      __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),        __FLT_NAN,       __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(42.42),         INFINITY, __FLT_CST(-0.0), __FLT_CST(1.0), 0, 0)
  DEFINE_TEST (        INFINITY, __FLT_CST(42.42),       __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (        INFINITY,         INFINITY,  __FLT_CST(0.0), __FLT_CST(1.0), 1, 0)
  DEFINE_TEST (        INFINITY,        __FLT_NAN,       __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN, __FLT_CST(42.42),       __FLT_NAN,      __FLT_NAN, 0, 0)
  DEFINE_TEST (       __FLT_NAN,         INFINITY,  __FLT_CST(0.0), __FLT_CST(1.0), 1, 0)
  DEFINE_TEST (       __FLT_NAN,        __FLT_NAN,       __FLT_NAN,      __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(ctan);
}
