#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl strcoll (const char *s1, const char *s2).

   Flow-graph:
	(1) If s1 and/or s2 are NULL then set errno to EINVAL, raise optional
	invalid parameter handler, and return 0x7fffffff.
	(2) If LC_COLLATE isn't set, then return result of strcmp().
	(3) Do string comparision by using LC_COLLATE information.
	(4) Return on identity zero, if if comparision of s1 is less to s2
	return -1, otherwise 1.
Tests:
	Test for s1 and/or s2 NULL.
	Test successful state.
*/

int
ic_test_main (int seq, int flags)
{
  int (*fct)(const char *, const char *) =
	ic_test_getsymbol ("strcoll");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, "abc") == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)("abc", NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)("abc", "abc") == 0);
      IC_TEST_CHECK ((*fct)("abc", "abcd") == -1);
      IC_TEST_CHECK ((*fct)("abcd", "abc") == 1);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

