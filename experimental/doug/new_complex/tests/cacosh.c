
#include "complex_test.h"

int main()
{
  /* cacosh (conj (z)) = conj (cacosh (z)). */
  DEFINE_TEST_FUNCTION(cacosh, FUNC_BEHAVIOR_CONJ);

  /* cacosh (+/-0 + i*0) = +0 + i*pi/2 */
  /* cacosh (x + i*inf) = +inf + i*pi/2 for finite x */
  /* cacosh (x + i*nan) = nan + i*nan for finite x (optional raise fpexception) */
  /* cacosh (-inf + i*y) = +inf + i*pi for positive-signed finite y */
  /* cacosh (+inf + i*y) = +inf + i*0  for positive-signed finite y */
  /* cacosh (-inf + i*inf) = +inf + i*3*pi/4 */
  /* cacosh (+inf + i*inf) = +inf + i*pi/4 */
  /* cacosh (+/-inf + i*nan) = +inf + i*nan */
  /* cacosh (nan + i*y) = nan + i*nan for all finite y (optional raise fpexception) */
  /* cacosh (nan + i*inf) = +inf + i*nan */
  /* cacosh (nan + i*nan) = nan + i*nan */

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
