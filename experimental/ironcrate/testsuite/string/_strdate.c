#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl _strdate (char *d).

   Flow-graph:
   (1): If d is zero, then set errno to EINVAL, and return NULL.
   (2): Set d in format HH:MM:SS by result of GetLocalTime.
   (3): Return d.
Tests:
	Test for d == NULL
	Test for d == valid string d
	Test for s == invalid string d
*/

int
ic_test_main (int seq, int flags)
{
  char t[12];
  char * (*fct)(char *) =
	ic_test_getsymbol ("_strdate");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL) == NULL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)((char *) (size_t) 1) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(t) == t && t[2] == '/' && t[5] == '/');
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

