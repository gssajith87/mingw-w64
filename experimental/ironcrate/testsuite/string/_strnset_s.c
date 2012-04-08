#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl _strset_s (char *s, size_t n, int ch, size_t m).

   Flow-graph:
    (1) If s, n, and m are zero return 0.
    (2) If s or n are zero, set errno to EINVAL and return EINVAL.
    (3) Set string in s to value ch until not the terminating zero-
	character of s is reached, or maximal n or m-th chacters are set.
    (4) If the n'th chacter in s was set, then set *s to zero,
	set errno to EINVAL, and return EINVAL.
    (5) Otherwise return 0.
Tests:
	Test for s == NULL.
	Test for valid s & n and ch != 0.
	Test for valid s & n and ch == 0.
	Test for valid s ch != 0, and n == strlen (s).
*/

int
ic_test_main (int seq, int flags)
{
  char tst[] = "abc";
  char ts2[] = "abc";
  char ts3[] = "abcd";
  errno_t (*fct)(char *, size_t, int, size_t) =
	ic_test_getsymbol ("_strnset_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, 0, 'a', 0) == 0);
      IC_TEST_CHECK ((*fct)(tst, 0, 'a', 0) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 4, 'a', 0) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(tst, 4, 'a', 4) == 0);
      IC_TEST_CHECK (tst[0] == tst[1] && tst[2] == tst[1]
		     && tst[1] == 'a');
      IC_TEST_CHECK ((*fct)(ts2, 3, 'a', 4) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(ts3, 5, 0, 5) == 0);
      IC_TEST_CHECK (ts3[0] == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

