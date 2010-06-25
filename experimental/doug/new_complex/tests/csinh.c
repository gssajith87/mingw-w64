#include "complex_test.h"

int main()
{
  /* Annex G.6.2.5 The csinh functions
     csinh(conj(z)) = conj(csinh(z)) and csinh is odd.
     csinh(+0 + i0) returns +0 + i0.
     csinh(+0 + i ∞) returns ±0 + iNaN (where the sign of the real part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
     csinh(+0 + iNaN) returns ±0 + iNaN (where the sign of the real part of the result is unspecified).
     csinh(x + i ∞) returns NaN + iNaN and raises the ‘‘invalid’’ floating-point exception, for positive finite x.
     csinh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite nonzero x.
     csinh(+∞ + i0) returns +∞ + i0.
     csinh(+∞ + iy) returns +∞ cis(y), for positive finite y.
     csinh(+∞ + i ∞) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified) and raises the ‘‘invalid’’ floating-point exception.
     csinh(+∞ + iNaN) returns ±∞ + iNaN (where the sign of the real part of the result is unspecified).
     csinh(NaN + i0) returns NaN + i0.
     csinh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for all nonzero numbers y.
     csinh(NaN + iNaN) returns NaN + iNaN.  */

  DEFINE_TEST_FUNCTION(csinh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(0.0), __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST( 0.0), INFINITY, __FLT_CST(0.0), __FLT_NAN, 1, 0)
  DECLARE_TEST (__FLT_CST( 0.0), __FLT_NAN, __FLT_CST(0.0), __FLT_NAN, 1, 0)

  DECLARE_TEST (__FLT_CST(42.42), INFINITY, __FLT_NAN, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_CST(42.42), __FLT_NAN,	    __FLT_NAN     , __FLT_NAN,	0, 0)

  DECLARE_TEST ( INFINITY, __FLT_CST(0.0),	INFINITY, __FLT_CST(0.0),	0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(42.42),	INFINITY*__FLT_ABI(cos)(__FLT_CST(42.42)), INFINITY*__FLT_ABI(sin)(__FLT_CST(42.42)),	0, 0)
  DECLARE_TEST ( INFINITY, INFINITY,		INFINITY, __FLT_NAN,		1, 0)
  DECLARE_TEST ( INFINITY, __FLT_NAN,	INFINITY, __FLT_NAN,	1, 0)

  DECLARE_TEST (__FLT_NAN, __FLT_CST(0.0),	__FLT_NAN, __FLT_CST(0.0),	0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42),	__FLT_NAN, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_NAN, INFINITY,		__FLT_NAN, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN,		__FLT_NAN, __FLT_NAN,	0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}
