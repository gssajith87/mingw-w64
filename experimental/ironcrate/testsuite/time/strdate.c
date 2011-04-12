#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl _strdate (char *d);

   Flow-graph:
   (1): If d == NULL set errno to EINVAL, raise optional invalid parameter
   	handler, and return NULL.
   (2): Get local time via GetLocalTime Win32 API and format string d as MM/DD/YY.
   (3): Return d.

Tests:
	Test for valid d.
	Test for d == NULL returning NULL and errno is set to EINVAL.
	Test for segfault for invalid d
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  char * (*fct)(char *) =
	ic_test_getsymbol ("_strdate");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf) == buf && strlen (buf) == 8);
      IC_TEST_CHECK ((*fct)(NULL) == NULL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)((void *) (size_t) 1) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

