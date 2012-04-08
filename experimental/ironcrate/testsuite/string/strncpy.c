#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strncpy (char *d, const char *s, size_t n).

   Flow-graph:
   (1): Copy from s to d until zero character or n-th character.
   (2): Return original d as result.

Tests:
	Test for copy.
	Test for segfault for invalid s or d
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  char * (*fct)(char *, const char *, size_t) =
	ic_test_getsymbol ("strncpy");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, "abc", 4) == buf);
      IC_TEST_CHECK (strcmp (buf, "abc") == 0);
      IC_TEST_CHECK ((*fct)(buf, "", 1) == buf);
      IC_TEST_CHECK (strcmp (buf, "") == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 3) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, NULL, 0) == 0);
      IC_TEST_CHECK ((*fct)(buf, NULL, 1) == 0);
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

