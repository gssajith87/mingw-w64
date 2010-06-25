
#include "complex_test.h"

int main() 
{
  /* Annex G.6.4.2 The csqrt functions
     csqrt(conj(z)) = conj(csqrt(z)).
     csqrt(±0 + i0) returns +0 + i0.
     csqrt(x + i ∞) returns +∞ + i ∞, for all x (including NaN).
     csqrt(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for finite x.
     csqrt(−∞ + iy) returns +0 + i ∞, for finite positive-signed y.
     csqrt(+∞ + iy) returns +∞ + i0, for finite positive-signed y.
     csqrt(−∞ + iNaN) returns NaN ± i ∞ (where the sign of the imaginary part of the result is unspecified).
     csqrt(+∞ + iNaN) returns +∞ + iNaN.
     csqrt(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for finite y.
     csqrt(NaN + iNaN) returns NaN + iNaN.  */

  DEFINE_TEST_FUNCTION (csqrt, FUNC_BEHAVIOR_CONJ);

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-0.0), __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)

  DECLARE_TEST (__FLT_CST(42.42), INFINITY, INFINITY, INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), INFINITY, INFINITY, INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST(42.42), __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  DECLARE_TEST (-INFINITY, __FLT_CST(0.0),  __FLT_CST(0.0), INFINITY, 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(0.0),  INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-INFINITY, __FLT_CST(42.42),  __FLT_CST(0.0), INFINITY, 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(42.42),  INFINITY, __FLT_CST(0.0), 0, 0)

  DECLARE_TEST (-INFINITY, __FLT_NAN, __FLT_NAN, INFINITY, 0, 1)
  DECLARE_TEST (INFINITY, __FLT_NAN, INFINITY, __FLT_NAN, 0, 0)

  DECLARE_TEST (__FLT_NAN, __FLT_CST(0.0),  __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42), __FLT_NAN, __FLT_NAN, 0, 0)
  /* special case of x + infi */
  DECLARE_TEST (__FLT_NAN, INFINITY, INFINITY, INFINITY, 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}

