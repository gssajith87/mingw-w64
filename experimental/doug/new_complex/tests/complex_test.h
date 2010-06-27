/* Testsuite functions for the complex functions of C99.  */
#ifndef _NEWCOMPLEX_TEST_H
#define _NEWCOMPLEX_TEST_H

/* Support printing of long doubles.  */
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <math.h>
#include <complex.h>

/* Default to double types.  */
#if !(defined (_NEW_COMPLEX_FLOAT) || defined (_NEW_COMPLEX_DOUBLE) || defined (_NEW_COMPLEX_LDOUBLE))
#define _NEW_COMPLEX_DOUBLE 1
#endif

/* Grab the internals for things like __FLT_PI, etc.  */
#include "complex_internal.h"

/* Declare comparisons etc.  */
#if defined(_NEW_COMPLEX_DOUBLE)
# define __FLT_CMP	compare_dbl
# define __FLT_CCMP	compare_cdbl
# define __FLT_DELTA	(2.0 * __DBL_EPSILON__)
# define __FLT_FMT	"%0.32g"
#elif defined (_NEW_COMPLEX_FLOAT)
# define __FLT_CMP	compare_flt
# define __FLT_CCMP	compare_cflt
# define __FLT_DELTA	(2.0F * __FLT_EPSILON__)
# define __FLT_FMT	 "%0.32g"
#elif defined (_NEW_COMPLEX_LDOUBLE)
# define __FLT_CMP	compare_ldbl
# define __FLT_CCMP	compare_cldbl
# define __FLT_DELTA	(2.0L * __LDBL_EPSILON__)
# define __FLT_FMT	 "%0.32Lg"
#endif

struct complex_test
{
  /* The input value to the complex function */
  __FLT_TYPE input_r;
  __FLT_TYPE input_i;
  /* The expected value from the complex function */
  __FLT_TYPE expected_r;
  __FLT_TYPE expected_i;
  /* Some C99 signs are +/-.  When these are true, don't compare signs */
  int real_sign_dontcare;
  int imag_sign_dontcare;
};

/* Definition of the function under test.  */
typedef __FLT_TYPE complex (*complex_function)(__FLT_TYPE complex z);
typedef __FLT_TYPE         (*real_function)(__FLT_TYPE complex z);

/* Some possible behaviors of the function.  */
/* func (conj (z)) = conj (func (z))  */
#define FUNC_BEHAVIOR_CONJ 0x0001
/* func (-z) = -func (z)  */
#define FUNC_BEHAVIOR_ODD  0x0002
/* func (-z) = func (z)  */
#define FUNC_BEHAVIOR_EVEN 0x0004

/* Structure to hold info about the complex function.  */
struct test_func_desc
{
  const char *fname;
  complex_function complex_test;
  real_function    real_test;
  int              behavior;
};

/**
 * Compares expected and test values with a delta tolerance.
 * 0 for pass, 1 for fail.
 * TODO:
 * Tune comparison precision
 **/

static int
__FLT_CMP (__FLT_TYPE expected, __FLT_TYPE in, int sign_dontcare)
{
  int bad = 0;
  if (isnan (expected) || isnan (in))
    {
      /* NaN comparisons */
      bad = isnan (expected) != isnan (in);
    }
  else if (isfinite (expected) && isfinite (in))
    {
      /* Finite value tests */
      if (expected == 0 && in == 0)
	{
	  /* Signed zero comparison */
	  bad = (sign_dontcare) ? 0 : signbit (expected) != signbit (in);
	}
      else
	{
	  bad = (expected > in) ?
		((expected - in) > __FLT_DELTA) :
		((in - expected) > __FLT_DELTA);
	}
    }
  else
    {
      /* Either expected or in is an infinite */
      bad = !isinf(expected) || !isinf(in);
      if (!bad && !sign_dontcare)
	bad =  signbit (expected) != signbit (in);
    }

  return bad;
}

static int
__FLT_CCMP (complex __FLT_TYPE expected,
	    complex __FLT_TYPE in,
	    int real_sign_dontcare,
	    int imag_sign_dontcare)
{
  return (__FLT_CMP (__FLT_ABI(creal)(expected), __FLT_ABI(creal)(in), real_sign_dontcare) ||
	  __FLT_CMP (__FLT_ABI(cimag)(expected), __FLT_ABI(cimag)(in), imag_sign_dontcare));
}

/* Runs comparison and (DEBUG) print error.
   returns 1 on fail, 0 on success.  */
static int
error_check_test (const struct test_func_desc *fdesc,
		  const char* testdescription,
		  int testindex,
		  __FLT_TYPE complex test,
		  __FLT_TYPE complex expected,
		  int real_sign_dontcare,
		  int imag_sign_dontcare)
{
  int bad = 0;
  __FLT_TYPE complex actual;
  if (fdesc->complex_test)
    {
      actual = fdesc->complex_test (test);
      bad = __FLT_CCMP (expected, actual, real_sign_dontcare, imag_sign_dontcare);
      if (bad)
	{
	  printf("%s %s test index %d failed on input " __FLT_FMT " + " __FLT_FMT "i.\n"
		"\tExpected: " __FLT_FMT " + " __FLT_FMT "i\n"
		"\tActual: " __FLT_FMT " + " __FLT_FMT "i (epsilon=" __FLT_FMT ")\n",
		fdesc->fname, testdescription, testindex,
		__FLT_ABI(creal) (test),    __FLT_ABI(cimag) (test),
		__FLT_ABI(creal) (expected), __FLT_ABI(cimag) (expected),
		__FLT_ABI(creal) (actual),   __FLT_ABI(cimag) (actual),
		__FLT_DELTA);
	}
    }
  else
    {
      __real__ actual = fdesc->real_test (test);
      bad = __FLT_CMP (__real__ expected, actual, real_sign_dontcare);
      if (bad)
	{
	  printf("%s %s test index %d failed on input " __FLT_FMT " + " __FLT_FMT "i.\n"
		"\tExpected: " __FLT_FMT "\n"
		"\tActual: " __FLT_FMT " (epsilon=" __FLT_FMT ")\n",
		fdesc->fname, testdescription, testindex,
		__FLT_ABI(creal) (test),    __FLT_ABI(cimag) (test),
		__FLT_ABI(creal) (expected),
		__FLT_ABI(creal) (actual),
		__FLT_DELTA);
	}
    }

  return bad;
}

/* Tests of conjugates, function should satisfy
   func (conj (z)) = conj (func (z)).  func (conj (z)) should return
   the conj of the expected, since expected is the expected result of
   func (z).  */
static int
conjugate_tests (const struct test_func_desc *fdesc,
		 int testindex,
		 __FLT_TYPE complex test,
		 __FLT_TYPE complex expected,
		 int real_sign_dontcare,
		 int imag_sign_dontcare)
{
  int ret = 0;

  /* Conjugate test 1: verify result of func (conj (z)) is conj (expected) */
  __FLT_TYPE complex ctest =    __FLT_ABI(conj) (test);
  __FLT_TYPE complex cexpected = __FLT_ABI(conj) (expected);

  ret |= error_check_test (fdesc, "Congugate of expected", testindex, ctest, cexpected,
			  real_sign_dontcare, imag_sign_dontcare);
  return ret;
}

/* Tests of odd functions, function should satisfy
   func (-z) = -func (z).  func (-z) should result in the -expected result,
   since expected is the expected result of func (z).  */
static int
odd_tests (const struct test_func_desc *fdesc,
	   int testindex,
	   __FLT_TYPE complex test,
	   __FLT_TYPE complex expected,
	   int real_sign_dontcare,
	   int imag_sign_dontcare)
{
  int ret = 0;

  /* Oddness test 1: verify result of func (-z) is -expected */
  __FLT_TYPE complex ctest =    -test;
  __FLT_TYPE complex cexpected = -expected;

  ret |= error_check_test (fdesc, "Oddness", testindex, ctest, cexpected,
			  real_sign_dontcare, imag_sign_dontcare);

  /* Need to do conjugate of the odd values as well */
  ret |= conjugate_tests(fdesc, testindex, ctest, cexpected, real_sign_dontcare,
			imag_sign_dontcare);

  return ret;
}

/* Tests of even functions, function should satisfy
   func (-z) = func (z).  func (-z) should result in the expected result,
   since expected is the expected result of func (z).  */
static int
even_tests (const struct test_func_desc *fdesc,
	   int testindex,
	   __FLT_TYPE complex test,
	   __FLT_TYPE complex expected,
	   int real_sign_dontcare,
	   int imag_sign_dontcare)
{
  int ret = 0;

  /* Evenness test 1: verify result of func (-z) is expected */
  __FLT_TYPE complex ctest =    -test;
  __FLT_TYPE complex cexpected = expected;

  ret |= error_check_test (fdesc, "Evenness", testindex, ctest, cexpected,
			  real_sign_dontcare, imag_sign_dontcare);

  /* Need to do conjugate of the even values as well */
  ret |= conjugate_tests(fdesc, testindex, ctest, cexpected, real_sign_dontcare,
			imag_sign_dontcare);
  return ret;
}

/* Actually run the tests.  */
static int
runtests (const struct test_func_desc *testfunc,
	  const struct complex_test *testarray,
	  int testcount)
{
  int i;
  int ret = 0;

  for (i = 0; i < testcount; i++)
    {
      __FLT_TYPE complex test;
      __FLT_TYPE complex expected;
      __real__ test = testarray[i].input_r;
      __imag__ test = testarray[i].input_i;
      __real__ expected = testarray[i].expected_r;
      __imag__ expected = testarray[i].expected_i;

      /* Main test --- specified in Annex G, et al. */
      ret |= error_check_test (testfunc, "Annex G", i, test, expected,
		testarray[i].real_sign_dontcare, testarray[i].imag_sign_dontcare);

      if (testfunc->behavior & FUNC_BEHAVIOR_CONJ)
	{
	  ret |= conjugate_tests (testfunc, i, test, expected,
		 testarray[i].real_sign_dontcare, testarray[i].imag_sign_dontcare);
	}

      if (testfunc->behavior & FUNC_BEHAVIOR_ODD)
	{
	  ret |= odd_tests (testfunc, i, test, expected,
		 testarray[i].real_sign_dontcare, testarray[i].imag_sign_dontcare);
	}

      if (testfunc->behavior & FUNC_BEHAVIOR_EVEN)
	{
	  ret |= even_tests (testfunc, i, test, expected,
		 testarray[i].real_sign_dontcare, testarray[i].imag_sign_dontcare);
	}
    }

  return ret;
}

#define __FLT_STRING(x) #x
#define __FLT_STRINGIFY(x) __FLT_STRING(x)

/**
 * Defines the test function with a variable name to pass to RUN_TESTS.
 * varname is the varname to use.
 * funcame is the function to test.
 * behavior is the flags of how the function behaves.
 */
#define DEFINE_TEST_FUNCTION(varname, funcname, behavior)	\
  struct test_func_desc varname =				\
  {								\
    __FLT_STRINGIFY(__FLT_ABI(funcname)),			\
    __FLT_ABI(funcname),					\
    NULL,							\
    behavior							\
  }

/**
 * Defines the test function with a variable name to pass to RUN_TESTS.
 * This version is for functions that return a real value.
 * varname is the varname to use.
 * funcame is the function to test.
 * behavior is the flags of how the function behaves.
 */
#define DEFINE_TEST_FUNCTION_REAL(varname, funcname, behavior)	\
  struct test_func_desc varname =					\
  {									\
    __FLT_STRINGIFY(__FLT_ABI(funcname)),				\
    NULL,								\
    __FLT_ABI(funcname),						\
    behavior								\
  }


/* Do not use semicolons with these macros.  */

/**
 * Starts a declaration of tests, with a variable name.
 */
#define TESTS_START(v) const struct complex_test v[] = {

/**
 * Starts a declaration of tests, with a default variable name, for use with
 * RUN_DEFAULT_TESTS.
 */
#define DEFAULT_TESTS_START TESTS_START(_default_tests)

/**
 * Macro to fill a complex_test structure with values while inside a
 * TESTS block.
 */
#define DEFINE_TEST(input_r, input_i, expected_r, expected_i, real_sign_dontcare, imag_sign_dontcare)	\
  { input_r, input_i, expected_r, expected_i, real_sign_dontcare, imag_sign_dontcare },

/**
 * Closes a test block opened with the TESTS_START macros.
 */
#define TESTS_END };

/**
 * Runs the tests specified in testarray using the specified test function
 * definition.
 * testfunc is the function definition specification defined by one of the
 * DEFINE_TEST_FUNCTION macros.
 * testarray is the test array defined by a TESTS_START macro.
 */
#define RUN_TESTS(testfunc, testarray) \
  (runtests(&testfunc, testarray, (sizeof (testarray) / sizeof (*testarray))))

/**
 * Runs the tests specified in testarray using the test function
 * definition declared with DEFINE_DEFAULT_TEST_FUNCTION macros.
 * funcname is the function name passed to the DEFAULT_TEST_FUNCTION* macro.
 * testarray is the test array defined by the TESTS_START macro.
 */
#define RUN_FUNCTION_TESTS(funcname, testarray) \
  RUN_TESTS(_test_##funcname, testarray)

/**
 * Runs the tests specified by DEFAULT_TESTS testarray using the test function
 * definition declared with DEFINE_DEFAULT_TEST_FUNCTION macros.
 * funcname is the function name passed to the DEFAULT_TEST_FUNCTION* macro.
 */
#define RUN_DEFAULT_TESTS(funcname) \
  RUN_TESTS(_test_##funcname, _default_tests)

/**
 * Default test functions available.
 */

/**
 * Defines a test function with a default variable name for use with the
 * RUN_DEFAULT_TESTS macro.
 * funcname is the function family to test.
 * behavior is the function's behavior.
 */
#define _DEFINE_DEFAULT_TEST_FUNCTION(funcname, behavior) \
	DEFINE_TEST_FUNCTION(_test_##funcname, funcname, behavior)

/**
 * Defines a test function with a default variable name for use with the
 * RUN_DEFAULT_TESTS macro.  This version is for functions that return
 * a real value.
 * funcname is the function family to test.
 * behavior is the function's behavior.
 */
#define _DEFINE_DEFAULT_TEST_FUNCTION_REAL(funcname, behavior) \
	DEFINE_TEST_FUNCTION_REAL(_test_##funcname, funcname, behavior)

/**
 * Declare default test functions to be used by test programs.
 */
_DEFINE_DEFAULT_TEST_FUNCTION_REAL (cabs, FUNC_BEHAVIOR_CONJ);
_DEFINE_DEFAULT_TEST_FUNCTION (cacos, FUNC_BEHAVIOR_CONJ);
_DEFINE_DEFAULT_TEST_FUNCTION (cacosh, FUNC_BEHAVIOR_CONJ);
_DEFINE_DEFAULT_TEST_FUNCTION (casin, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (casinh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (catan, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (catanh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (ccos, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_EVEN);
_DEFINE_DEFAULT_TEST_FUNCTION (ccosh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_EVEN);
_DEFINE_DEFAULT_TEST_FUNCTION (cexp, FUNC_BEHAVIOR_CONJ);
_DEFINE_DEFAULT_TEST_FUNCTION (clog, FUNC_BEHAVIOR_CONJ);
/* We don't define this as a CONJ behavior because that uses the conj function.  */
_DEFINE_DEFAULT_TEST_FUNCTION (conj, 0);
_DEFINE_DEFAULT_TEST_FUNCTION (csin, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (csinh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (csqrt, FUNC_BEHAVIOR_CONJ);
_DEFINE_DEFAULT_TEST_FUNCTION (ctan, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);
_DEFINE_DEFAULT_TEST_FUNCTION (ctanh, FUNC_BEHAVIOR_CONJ | FUNC_BEHAVIOR_ODD);

#endif  /* _NEWCOMPLEX_TEST_H */
