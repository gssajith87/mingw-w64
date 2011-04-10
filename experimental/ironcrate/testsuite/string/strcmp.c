#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl strcmp (const char *s1, const char *s2).

   Flow-graph:
	(1) Compare s1 with s2 from left to right until zero charcter
	is found or non-equal character is found.
	(2) Is the same character return 0, else if unsigned comparison
	of different character is *s1 < *s2 return -1, otherwise 1.
Tests:
	Test for identity.
	Test for s1 < s2.
	Test for s1 > s2.
	Test for s1 or s2 NULL.
*/

int
ic_test_main (int seq, int flags)
{
  int (*fct)(const char *, const char *) =
	ic_test_getsymbol ("strcmp");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc", "abc") == 0);
      IC_TEST_CHECK ((*fct)("abc", "abcd") == -1);
      IC_TEST_CHECK ((*fct)("abcd", "abc") == 1);
      IC_TEST_CHECK ((*fct)(NULL, "abc") == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc", NULL) == 0);
      return IC_TEST_RSLT_FAILED;
    case 2:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

