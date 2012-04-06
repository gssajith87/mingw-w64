#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strlwr (char *s).

   Flow-graph:
   (1): If s is nil, then return NULL, set errno to EINVAL.
   (2): If locale was changed, return result of _strlwr_s_l (s, -1, NULL).
   (3): For each characer in s until the zero-character convert the
	characters 'A'-'Z' into 'a'-'z'.
   (4): Result is s on success.
Tests:
	Test for s == NULL.
	Test for s == valid string
*/

int
ic_test_main (int seq, int flags)
{
  char tst[] = "abcABC";
  char * (*fct)(char *) =
	ic_test_getsymbol ("_strlwr");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL) == NULL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(tst) == tst);
      IC_TEST_CHECK (tst[0] == tst[3] && tst[1] == tst[4] && tst[2] == tst[5]);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

