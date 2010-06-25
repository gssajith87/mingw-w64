#include "complex_test.h"

int main() 
{
  /* ctanh (conj (z)) = conj (ctanh (z)). */
  /* ctanh (-z) = -ctanh (z), ctanh is odd. */
  DEFINE_TEST_FUNCTION(ctanh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);

  /* ctanh (+0 + i*0) = +0 + i*0 */
  /* ctanh (x + i*inf) = nan + i*nan for finite x (raise fpexception) */
  /* ctanh (x + i*nan) = nan + i*nan for finite x (optional raise fpexception) */
  /* ctanh (+inf + i*y) = 1 + i*0*sin(2y) for positive-signed finite y */
  /* ctanh (+inf + i*inf) = 1 +/- i*0 (unspecified sign of zero for C99) */
  /* ctanh (+inf + i*nan) = 1 +/- i*0 (unspecified sign of zero for C99) */
  /* ctanh (nan + i*0) = nan + i*0 */
  /* ctanh (nan + i*y) = nan + i*nan for all nonzero y (optional raise fpexception) */
  /* ctanh (nan + i*nan) = nan + i*nan */

  TEST_PROLOGUE

  DECLARE_TEST (__FLT_CST(0.0), __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_CST(42.42), INFINITY, __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_CST(42.42), __FLT_NAN, 	    __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (INFINITY , __FLT_CST(42.42), __FLT_CST(1.0),  __FLT_CST(0.0) * __FLT_ABI(sin) (__FLT_CST(2.0)*__FLT_CST(42.42)), 0, 0)
  DECLARE_TEST (INFINITY, INFINITY, __FLT_CST(1.0), __FLT_CST(0.0), 0, 1)
  DECLARE_TEST (INFINITY, __FLT_NAN, __FLT_CST(1.0), __FLT_CST(0.0), 0, 1)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(0.0), __FLT_NAN, __FLT_CST(0.0), 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_CST(42.42), __FLT_NAN, __FLT_NAN, 0, 0)
  DECLARE_TEST (__FLT_NAN, __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  TEST_EPILOGUE

  return RUNTESTS;
}
