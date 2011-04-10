#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strcat (char *d, const char *s).

   Flow-graph:
   (1): Copy from s to end of d until zero character
   (2): Return original d as result.

Tests:
	Test for copy.
	Test for segfault for invalid s or d
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  char * (*fct)(char *, const char *) =
	ic_test_getsymbol ("strcat");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, "abc") == buf);
      IC_TEST_CHECK (strcmp (buf, "__abc") == 0);
      buf[0] = 0;
      IC_TEST_CHECK ((*fct)(buf, "") == buf);
      IC_TEST_CHECK (strcmp (buf, "") == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc") == buf);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0 && 1);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, NULL) == buf);
      return IC_TEST_RSLT_FAILED;
    case 2:
      IC_TEST_CHECK (ic_test_segfault != 0 && 2);
      ic_test_reset_internal_vars ();
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

