#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strcpy (char *d, const char *s).

   Flow-graph:
   (1): Copy from s to d until zero character
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
	ic_test_getsymbol ("strcpy");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, "abc") == buf);
      IC_TEST_CHECK (strcmp (buf, "abc") == 0);
      IC_TEST_CHECK ((*fct)(buf, "") == buf);
      IC_TEST_CHECK (strcmp (buf, "") == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc") == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, NULL) == 0);
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

