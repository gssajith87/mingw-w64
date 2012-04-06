#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strset (char *s, int ch).

   Flow-graph:
   (1) Set all characters in string s to value of ch, until s'
       nil-character.
Tests:
	Test for s == NULL.
	Test for valid s and ch != 0.
	Test for valid s and ch == 0.
*/

int
ic_test_main (int seq, int flags)
{
  char tst[] = "abcABC";
  char * (*fct)(char *, int) =
	ic_test_getsymbol ("_strset");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, 0) == tst);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0 && 1);
      ic_test_reset_internal_vars ();

      IC_TEST_CHECK ((*fct)(tst, 'a') == tst);
      IC_TEST_CHECK (tst[0] == tst[3] && tst[1] == tst[4] && tst[2] == tst[5]
		     && tst[0] == tst[1] && tst[0] == tst[2] && tst[1] == 'a');
      IC_TEST_CHECK ((*fct)(tst, 0) == tst);
      IC_TEST_CHECK (tst[0] == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

