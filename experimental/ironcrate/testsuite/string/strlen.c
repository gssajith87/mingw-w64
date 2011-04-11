#include "../testlib/main_test.c"
#include <errno.h>

/* size_t __cdecl strlen (const char *s).

   Flow-graph:
   (1): Save orginal pointer s.
   (2): While charcter pointed by s != 0 increase pointer s.
   (3): Return difference between pointer s and the saved pointer of s.
Tests:
	Test for s == NULL.
	Test for s == valid string
	Test for s == invalid string.
*/

int
ic_test_main (int seq, int flags)
{
  size_t (*fct)(const char *) =
	ic_test_getsymbol ("strlen");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc") == 3);
      IC_TEST_CHECK ((*fct)("") == 0);
      IC_TEST_CHECK ((*fct)(NULL) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      IC_TEST_CHECK ((*fct)((char *) (size_t) 1) == 0);
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

