#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl memcmp (const void *s1, const void *s2, size_t n).

   Flow-graph:
   (1): Is n == 0 then return 0;
   (2): loop from i = 1 to i < n while s1[i - 1] == s2[i - 1]
   (3): return difference of s1[i] - s2[i]

Tests:
	Test for n == 0 return of zero.
	Test result for <, >, and identity == 0.
*/

int
ic_test_main (int seq, int flags)
{
  int r;
  int (*fct)(const void *, const void *, size_t) =
	ic_test_getsymbol ("memcmp");
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
      
      IC_TEST_CHECK ((r = (*fct)("abc", "abc", 3)) == 0);
      IC_TEST_CHECK ((r = (*fct)("aad", "abc", 3)) < 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'a' - (unsigned char) 'b'));
      IC_TEST_CHECK ((r = (*fct)("acd", "abc", 3)) > 0);
      IC_TEST_CHECK (r == (int) ((unsigned char) 'c' - (unsigned char) 'b'));

      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

