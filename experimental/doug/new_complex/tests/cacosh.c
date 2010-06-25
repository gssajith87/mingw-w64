
#include "complex_test.h"

int main()
{
  /* Annex G.6.2.1 The cacosh functions
     cacosh(conj(z)) = conj(cacosh(z)).
     cacosh(±0 + i0) returns +0 + iπ /2.
     cacosh(x + i ∞) returns +∞ + iπ /2, for finite x.
     cacosh(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite x.
     cacosh(−∞ + iy) returns +∞ + iπ , for positive-signed finite y.
     cacosh(+∞ + iy) returns +∞ + i0, for positive-signed finite y.
     cacosh(−∞ + i ∞) returns +∞ + i3π /4.
     cacosh(+∞ + i ∞) returns +∞ + iπ /4.
     cacosh(±∞ + iNaN) returns +∞ + iNaN.
     cacosh(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating-point exception, for finite y.
     cacosh(NaN + i ∞) returns +∞ + iNaN.
     cacosh(NaN + iNaN) returns NaN + iNaN.  */

  DEFINE_TEST_FUNCTION(cacosh, FUNC_BEHAVIOR_CONJ);

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(0.0), __FLT_CST(0.0), __FLT_PI_2, 0, 0)
  DECLARE_TEST (__FLT_CST(-0.0), __FLT_CST(0.0), __FLT_CST(0.0), __FLT_PI_2, 0, 0)

  DECLARE_TEST (__FLT_CST(42.42), INFINITY, INFINITY, __FLT_PI_2,	0, 0)
  DECLARE_TEST (__FLT_CST(42.42), __FLT_NAN,	    __FLT_NAN     , __FLT_NAN,	0, 0)

  DECLARE_TEST (-INFINITY, __FLT_CST(42.42),	INFINITY, __FLT_PI,		0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(42.42),	INFINITY, __FLT_CST(0.0),	0, 0)
  DECLARE_TEST (-INFINITY, INFINITY,		INFINITY, __FLT_PI_3_4,		0, 0)
  DECLARE_TEST ( INFINITY, INFINITY,		INFINITY, __FLT_PI_4,		0, 0)

  DECLARE_TEST ( INFINITY, __FLT_NAN,	INFINITY, __FLT_NAN,	0, 0)
  DECLARE_TEST (-INFINITY, __FLT_NAN,	INFINITY, __FLT_NAN,	0, 0)

  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42),	__FLT_NAN, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_NAN, INFINITY,		INFINITY, __FLT_NAN,	0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN,		__FLT_NAN, __FLT_NAN,	0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}
