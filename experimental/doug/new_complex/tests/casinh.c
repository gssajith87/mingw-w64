#include "complex_test.h"

int main()
{
  /* Annex G.6.2.2 The casinh functions
     casinh(conj(z)) = conj(casinh(z)) and casinh is odd.
     casinh(+0 + i0) returns 0 + i0.
     casinh(x + i ∞) returns +∞ + iπ /2 for positive-signed finite x.
     casinh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite x.
     casinh(+∞ + iy) returns +∞ + i0 for positive-signed finite y.
     casinh(+∞ + i ∞) returns +∞ + iπ /4.
     casinh(+∞ + iNaN) returns +∞ + iNaN.
     casinh(NaN + i0) returns NaN + i0.
     casinh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite nonzero y.
     casinh(NaN + i ∞) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified).
     casinh(NaN + iNaN) returns NaN + iNaN.  */

  DEFINE_TEST_FUNCTION(casinh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(0.0), __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)

  DECLARE_TEST (__FLT_CST(42.42), INFINITY, INFINITY, __FLT_PI_2,	0, 0)
  DECLARE_TEST (__FLT_CST(42.42), __FLT_NAN,	    __FLT_NAN     , __FLT_NAN,	0, 0)

  DECLARE_TEST ( INFINITY, __FLT_CST(42.42),	INFINITY, __FLT_CST(0.0),	0, 0)
  DECLARE_TEST ( INFINITY, INFINITY,		INFINITY, __FLT_PI_4,		0, 0)
  DECLARE_TEST ( INFINITY, __FLT_NAN,	INFINITY, __FLT_NAN,	0, 0)

  DECLARE_TEST (__FLT_NAN, __FLT_CST(0.0),	__FLT_NAN, __FLT_CST(0.0),	0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42),	__FLT_NAN, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_NAN, INFINITY,		INFINITY, __FLT_NAN,	1, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN,		__FLT_NAN, __FLT_NAN,	0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}
