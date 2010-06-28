#include "complex_test.h"

/**
 * Annex G, carg (z) == atan2 (__imag__ z, __real__ z).
 *
 * Annex F.9, Unless otherwise specified, where the symbol "±" occurs in both
 * an argument and the result, the result has the same sign as the argument.
 *
 * Annex F.9.1.4 The atan2 functions
 * atan2(±0, −0) returns ±π (footnote: no invalid or divide-by-zero exceptions)
 * atan2(±0, +0) returns ±0.
 * atan2(±0, x) returns ±π for x < 0.
 * atan2(±0, x) returns ±0 for x > 0.
 * atan2(y, ±0) returns −π /2 for y < 0.
 * atan2(y, ±0) returns π /2 for y > 0.
 * atan2(±y, −∞) returns ±π for finite y > 0.
 * atan2(±y, +∞) returns ±0 for finite y > 0.
 * atan2(±∞, x) returns ±π /2 for finite x.
 * atan2(±∞, −∞) returns ±3π /4.
 * atan2(±∞, +∞) returns ±π /4.
 *
 */
  
int __FLT_ABI(test_function_carg) ()
{
  /* These tests return a real -- expected imaginary is ignored.  */
  /* Note to self - reverse input for correct expected, since the imaginary value
     is the first to be passed to atan2.  */
  DEFAULT_TESTS_START

  DEFINE_TEST (-__FLT_CST(0.0), -__FLT_CST(0.0),       -__FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST (-__FLT_CST(0.0),  __FLT_CST(0.0),        __FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(0.0), -__FLT_CST(0.0), -__FLT_CST(0.0), __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(0.0),  __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_NAN, 0, 0)

  DEFINE_TEST (-__FLT_CST(0.0), -__FLT_CST(42.42), -__FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(0.0), -__FLT_CST(42.42), -__FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST (-__FLT_CST(0.0),  __FLT_CST(42.42),  __FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(0.0),  __FLT_CST(42.42),  __FLT_PI_2, __FLT_NAN, 0, 0)

  DEFINE_TEST (-__FLT_CST(42.42), -__FLT_CST(0.0),       -__FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST (-__FLT_CST(42.42),  __FLT_CST(0.0),        __FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42), -__FLT_CST(0.0), -__FLT_CST(0.0), __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42),  __FLT_CST(0.0),  __FLT_CST(0.0), __FLT_NAN, 0, 0)

  DEFINE_TEST (-__FLT_CST(42.42), -INFINITY, -__FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42), -INFINITY, -__FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST (-__FLT_CST(42.42),  INFINITY,  __FLT_PI_2, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(42.42),  INFINITY,  __FLT_PI_2, __FLT_NAN, 0, 0)

  DEFINE_TEST (-INFINITY, -__FLT_CST(42.42),       -__FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST (-INFINITY,  __FLT_CST(42.42),        __FLT_PI, __FLT_NAN, 0, 0)
  DEFINE_TEST ( INFINITY, -__FLT_CST(42.42), -__FLT_CST(0.0), __FLT_NAN, 0, 0)
  DEFINE_TEST ( INFINITY,  __FLT_CST(42.42),  __FLT_CST(0.0), __FLT_NAN, 0, 0)

  DEFINE_TEST (-INFINITY, -INFINITY, -__FLT_PI_3_4, __FLT_NAN, 0, 0)
  DEFINE_TEST (-INFINITY,  INFINITY,  __FLT_PI_3_4, __FLT_NAN, 0, 0)
  DEFINE_TEST ( INFINITY, -INFINITY,   -__FLT_PI_4, __FLT_NAN, 0, 0)
  DEFINE_TEST ( INFINITY,  INFINITY,    __FLT_PI_4, __FLT_NAN, 0, 0)

  DEFINE_TEST (      __FLT_NAN,  __FLT_CST(0.0), __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (      __FLT_NAN, -__FLT_CST(0.0), __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST ( __FLT_CST(0.0),       __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (-__FLT_CST(0.0),       __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (      __FLT_NAN,        INFINITY, __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (      __FLT_NAN,       -INFINITY, __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (       INFINITY,       __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)
  DEFINE_TEST (      -INFINITY,       __FLT_NAN, __FLT_NAN, __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(carg);
}
