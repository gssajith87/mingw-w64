#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl _strncoll (const char *s1, const char *s2, size_t n).

   Flow-graph:
   (1): If s1 or s2 are NULL and the locale wasn't changed, then set errno to EINVAL,
   	raise optional invalid_parameter_handler, and return 0x7fffffff. Otherwise
   	do comparision via _strncmp.
   (2): Otherwise call _strncoll_l with NULL as locale.

Tests:
	Test result for <, >, and identity == 0.
*/

int
ic_test_main (int seq, int flags)
{
  int r;
  int (*fct)(const char *, const char *, size_t) =
	ic_test_getsymbol ("_strncoll");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("def", NULL, 3) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 3) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, NULL, 3) == 0x7fffffff && errno == EINVAL);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((r = (*fct)("abc", "abc", 4)) == 0);
      IC_TEST_CHECK ((r = (*fct)("aad", "abc", 4)) < 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'a' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("acd", "abc", 3)) > 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'c' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("ABC", "abc",3)) != 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

