#include "complex_test.h"

/**
 * Annex G.6 conj (z) is fully defined in section 7.3.9.3.
 * (Note, the test suite doesn't define the behavior as conj since that is what is
 * actually under test, so we manually define the tests).
 */

int __FLT_ABI(test_function_conj) ()
{
  DEFAULT_TESTS_START

  DEFINE_TEST (__FLT_CST( 42.42), __FLT_CST( 42.42), __FLT_CST( 42.42), __FLT_CST(-42.42), 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42), __FLT_CST(-42.42), __FLT_CST( 42.42), __FLT_CST( 42.42), 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42), __FLT_CST( 42.42), __FLT_CST(-42.42), __FLT_CST(-42.42), 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42), __FLT_CST(-42.42), __FLT_CST(-42.42), __FLT_CST( 42.42), 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),   __FLT_CST( 0.0), __FLT_CST( 42.42),   __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),   __FLT_CST(-0.0), __FLT_CST( 42.42),   __FLT_CST( 0.0), 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),   __FLT_CST( 0.0), __FLT_CST(-42.42),   __FLT_CST(-0.0), 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),   __FLT_CST(-0.0), __FLT_CST(-42.42),   __FLT_CST( 0.0), 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),          INFINITY, __FLT_CST( 42.42),         -INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),         -INFINITY, __FLT_CST( 42.42),          INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),          INFINITY, __FLT_CST(-42.42),         -INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),         -INFINITY, __FLT_CST(-42.42),          INFINITY, 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),         __FLT_NAN, __FLT_CST( 42.42),        -__FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST( 42.42),        -__FLT_NAN, __FLT_CST( 42.42),         __FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),         __FLT_NAN, __FLT_CST(-42.42),        -__FLT_NAN, 0, 0)
  DEFINE_TEST (__FLT_CST(-42.42),        -__FLT_NAN, __FLT_CST(-42.42),         __FLT_NAN, 0, 0)

  TESTS_END

  return RUN_DEFAULT_TESTS(conj);
}
