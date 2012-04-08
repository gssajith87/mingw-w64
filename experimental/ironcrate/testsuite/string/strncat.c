#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strncat (char *d, const char *s, size_t n).

   Flow-graph:
   (1): Copy from s to end of d until zero character or n-th character
	is copied.
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
	ic_test_getsymbol ("strncat");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, "abc", 3) == buf);
      IC_TEST_CHECK (strcmp (buf, "__abc") == 0);
      buf[0] = 0;
      IC_TEST_CHECK ((*fct)(buf, "", 1) == buf);
      IC_TEST_CHECK (strcmp (buf, "") == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc", 4) == buf);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0 && 1);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, NULL, 4) == buf);
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

