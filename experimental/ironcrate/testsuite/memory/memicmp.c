#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl _memicmp (const void *s1, const void *s2, size_t n).

   Flow-graph:
   (1): If n != 0 and s1 or s2 are NULL and the locale wasn't changed, then set errno to EINVAL,
   	raise optional invalid_parameter_handler, and return 0x7fffffff. Otherwise
   	do ASCII comparision.
   (2): Otherwise call _memicmp_l with NULL as locale.

Tests:
	Test for n == 0 return of zero.
	Test result for <, >, and identity == 0.
*/

int
ic_test_main (int seq, int flags)
{
  int r;
  int (*fct)(const void *, const void *, size_t) =
	ic_test_getsymbol ("_memicmp");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, NULL, 0) == 0);
      IC_TEST_CHECK ((*fct)("abc", NULL, 0) == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 0) == 0);
      IC_TEST_CHECK ((*fct)("def", "abc", 0) == 0);
      IC_TEST_CHECK ((*fct)("def", NULL, 3) == 0x7fffffff);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 3) == 0x7fffffff);
      IC_TEST_CHECK ((*fct)(NULL, NULL, 3) == 0x7fffffff);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((r = (*fct)("abc", "abc", 3)) == 0);
      IC_TEST_CHECK ((r = (*fct)("aad", "abc", 3)) < 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'a' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("acd", "abc", 3)) > 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'c' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("ABC", "abc", 3)) == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

