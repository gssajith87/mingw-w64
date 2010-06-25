#include "complex_test.h"

int main() 
{
  /* Annex G.6.3.2 The clog functions
     clog(conj(z)) = conj(clog(z)).
     clog(−0 + i0) returns −∞ + iπ and raises the ‘‘divide-by-zero’’ floating-point exception.
     clog(+0 + i0) returns −∞ + i0 and raises the ‘‘divide-by-zero’’ floating-point exception.
     clog(x + i ∞) returns +∞ + iπ /2, for finite x.
     clog(x + iNaN) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for finite x.
     clog(−∞ + iy) returns +∞ + iπ , for finite positive-signed y.
     clog(+∞ + iy) returns +∞ + i0, for finite positive-signed y.
     clog(−∞ + i ∞) returns +∞ + i3π /4.
     clog(+∞ + i ∞) returns +∞ + iπ /4.
     clog(±∞ + iNaN) returns +∞ + iNaN.
     clog(NaN + iy) returns NaN + iNaN and optionally raises the ‘‘invalid’’ floating- point exception, for finite y.
     clog(NaN + i ∞) returns +∞ + iNaN.
     clog(NaN + iNaN) returns NaN + iNaN.  */

  DEFINE_TEST_FUNCTION (clog, FUNC_BEHAVIOR_CONJ);

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST(-0.0), __FLT_CST(0.0),  -INFINITY, __FLT_PI, 0, 0)
  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(0.0),  -INFINITY, __FLT_CST(0.0), 0, 0)

  DECLARE_TEST (__FLT_CST( 42.42), INFINITY, INFINITY, __FLT_PI_2, 0, 0)
  DECLARE_TEST (__FLT_CST(   0.0), INFINITY, INFINITY, __FLT_PI_2, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), INFINITY, INFINITY, __FLT_PI_2, 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(   0.0), __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  DECLARE_TEST (-INFINITY, __FLT_CST(0.0), INFINITY, __FLT_PI, 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(0.0), INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-INFINITY, __FLT_CST(42.42), INFINITY, __FLT_PI, 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(42.42), INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-INFINITY, INFINITY, INFINITY, __FLT_PI_3_4, 0, 0)
  DECLARE_TEST ( INFINITY, INFINITY, INFINITY, __FLT_PI_4, 0, 0)
  DECLARE_TEST (-INFINITY, __FLT_NAN, INFINITY, __FLT_NAN, 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_NAN, INFINITY, __FLT_NAN, 0, 0)

  DECLARE_TEST (__FLT_NAN, __FLT_CST(0.0),  __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42), __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_NAN, INFINITY, INFINITY, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}

