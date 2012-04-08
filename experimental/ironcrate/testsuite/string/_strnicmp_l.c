#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl _memicmp_l (const char *s1, const char *s2, size_t n, _locale_t pli).

   Flow-graph:
   (1): If s1 or s2 are NULL, then set errno to EINVAL,
   	raise optional invalid_parameter_handler, and return 0x7fffffff.
   (2): Otherwise if LC_CTYPE isn't set use ASCII comparison.
   (3): Else compare strings via _tolower_l converted characters until
	zero-element is reached or n characters are compared.

Tests:
	Test for n == 0 return of zero.
	Test result for <, >, and identity == 0.
*/

int
ic_test_main (int seq, int flags)
{
  int r;
  int (*fct)(const void *, const void *, size_t, _locale_t) =
	ic_test_getsymbol ("_strnicmp_l");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("def", NULL, 3, NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 3, NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, NULL, 3, NULL) == 0x7fffffff && errno == EINVAL);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((r = (*fct)("abc", "abc", 3, NULL)) == 0);
      IC_TEST_CHECK ((r = (*fct)("aad", "abc", 3, NULL)) < 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'a' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("acd", "abc", 3, NULL)) > 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'c' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("ABC", "abc", 3, NULL)) == 0);
      IC_TEST_CHECK ((r = (*fct)("ABCD", "abce", 3, NULL)) == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

