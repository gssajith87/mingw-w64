#include "complex_test.h"

int main()
{
  /* conj fully defined in 7.3.9.3 --- inverse sign of imagingary */
  
  /* We don't define this as a CONJ behavior because that uses the conj function.  */
  DEFINE_TEST_FUNCTION(conj, 0);
  
  TEST_PROLOGUE
  /* only change sign of imaginary part */
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_CST( 42.42), __FLT_CST( 42.42), __FLT_CST(-42.42), 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_CST(-42.42), __FLT_CST( 42.42), __FLT_CST( 42.42), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_CST( 42.42), __FLT_CST(-42.42), __FLT_CST(-42.42), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_CST(-42.42), __FLT_CST(-42.42), __FLT_CST( 42.42), 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_CST( 0.0), __FLT_CST( 42.42), __FLT_CST(-0.0), 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), __FLT_CST(-0.0), __FLT_CST( 42.42), __FLT_CST( 0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_CST( 0.0), __FLT_CST(-42.42), __FLT_CST(-0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), __FLT_CST(-0.0), __FLT_CST(-42.42), __FLT_CST( 0.0), 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42),  INFINITY, __FLT_CST( 42.42), -INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), -INFINITY, __FLT_CST( 42.42),  INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42),  INFINITY, __FLT_CST(-42.42), -INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), -INFINITY, __FLT_CST(-42.42),  INFINITY, 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42),  __FLT_NAN, __FLT_CST( 42.42), -__FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST( 42.42), -__FLT_NAN, __FLT_CST( 42.42),  __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42),  __FLT_NAN, __FLT_CST(-42.42), -__FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(-42.42), -__FLT_NAN, __FLT_CST(-42.42),  __FLT_NAN, 0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}

