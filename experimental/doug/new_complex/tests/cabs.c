#include "complex_test.h"

int main()
{
  /* Annex F.9.4.3 of the hypot function
     cabs (z) == hypot (__real__ z, __imag__ z).
     hypot (x, y) == hypot (x, -y), therefore is conjugate.
     hypot (x, y) == hypot (y, x).
     hypot (x, +/-0) == fabs (x).
     hypot (+/-inf, y) == +inf, for all y (including NaN).  */
  
  DEFINE_REAL_TEST_FUNCTION(cabs, FUNC_BEHAVIOR_CONJ);
  
  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST( 0.0), __FLT_CST(42.42), __FLT_CST(42.42), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-0.0), __FLT_CST(42.42), __FLT_CST(42.42), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST ( INFINITY, __FLT_CST(42.42), INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-INFINITY, __FLT_CST(42.42), INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (INFINITY,  __FLT_NAN, INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-INFINITY, __FLT_NAN, INFINITY, __FLT_CST(0.0), 0, 0)
  /* check x,y == y,x */
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_CST(0.0), __FLT_CST(42.42), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_CST(0.0), __FLT_CST(42.42), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), INFINITY, INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), INFINITY, INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST ( __FLT_NAN, INFINITY, INFINITY, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (-__FLT_NAN, INFINITY, INFINITY, __FLT_CST(0.0), 0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}

