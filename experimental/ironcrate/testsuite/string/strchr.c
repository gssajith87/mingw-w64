#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strchr (const char *s, int ch).

   Flow-graph:
   (1): Search in s for first occurance of ch from left to right.  If
	zero character is seen and ch != 0 then return NULL.
   (2): Return found position in s of ch

Tests:
	Test for search of character not in string.
	Test for search of character 0.
	Test for successful search of character != 0.
	Test for s == NULL.
*/

int
ic_test_main (int seq, int flags)
{
  const char *tst_str = "abc";
  char * (*fct)(const char *, int) =
	ic_test_getsymbol ("strchr");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(tst_str, 'A') == NULL);
      IC_TEST_CHECK ((*fct)(tst_str, 0) == (tst_str + strlen (tst_str)));
      IC_TEST_CHECK ((*fct)(tst_str, 'b') == (tst_str + 1));
      IC_TEST_CHECK ((*fct)(NULL, 0) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

