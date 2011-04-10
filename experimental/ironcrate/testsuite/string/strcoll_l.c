#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl _strcoll_l (const char *s1, const char *s2, _locale_t pli).

   Flow-graph:
	(1) If s1 and/or s2 are NULL then set errno to EINVAL, raise optional
	invalid parameter handler, and return 0x7fffffff.
	(2) If LC_COLLATE isn't set for pli, then return result of strcmp().
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
  int (*fct)(const char *, const char *, _locale_t) =
	ic_test_getsymbol ("_strcoll_l");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, "abc", NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)("abc", NULL, NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, NULL, NULL) == 0x7fffffff && errno == EINVAL);
      IC_TEST_CHECK ((*fct)("abc", "abc", NULL) == 0);
      IC_TEST_CHECK ((*fct)("abc", "abcd", NULL) == -1);
      IC_TEST_CHECK ((*fct)("abcd", "abc", NULL) == 1);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

