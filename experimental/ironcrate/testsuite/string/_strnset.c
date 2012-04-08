#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl _strnset (char *s, int ch, size_t n).

   Flow-graph:
   (1) Set all characters in string s to value of ch, until s'
       nil-character or n-th character is reached.
Tests:
	Test for s == NULL.
	Test for valid s and ch != 0.
	Test for valid s and ch == 0.
*/

int
ic_test_main (int seq, int flags)
{
  char tst[] = "abcABC";
  char * (*fct)(char *, int, size_t) =
	ic_test_getsymbol ("_strnset");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, 0, 0) == NULL);
      IC_TEST_CHECK ((*fct)(NULL, 0, 1) == NULL);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0 && 1);
      ic_test_reset_internal_vars ();

      IC_TEST_CHECK ((*fct)(tst, 'a', 6) == tst);
      IC_TEST_CHECK (tst[0] == tst[3] && tst[1] == tst[4] && tst[2] == tst[5]
		     && tst[0] == tst[1] && tst[0] == tst[2] && tst[1] == 'a');
      IC_TEST_CHECK ((*fct)(tst, 'b', 3) == tst);
      IC_TEST_CHECK (tst[0] == tst[2] && tst[0] == tst[1] && tst[0] == 'b'
		     && tst[3] == tst[4] && tst[3] == tst[5] && tst[3] == 'a');
      IC_TEST_CHECK ((*fct)(tst, 0, 7) == tst);
      IC_TEST_CHECK (tst[0] == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

