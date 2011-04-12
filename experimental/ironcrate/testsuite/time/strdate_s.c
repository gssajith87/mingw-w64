#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl _strdate_s (char *d,size_t n)

   Flow-graph:
   (1): If d == NULL and/or n == 0 set errno to EINVAL, raise optional invalid
   	parameter handler, and return EINVAL.
   (2): Set d[0] = 0
   (2): If n < 9 then set errno to ERANGE, raise optional invalid parameter
   	handler, and return ERANGE.
   (2): Get local time via GetLocalTime Win32 API and format string d as MM/DD/YY.
   (3): Return 0.

Tests:
	Test for valid d and n >= 9.
	Test for d == NULL and/or n == 0 returning EINVAL and errno is set to EINVAL.
	Test for d != NULL and n < 9 returning ERANGE and errno is set to ERAMGE. Additional
	d[0] is 0.
	Test for segfault for invalid d with 9 > n > 0
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  errno_t (*fct)(char *, size_t) =
	ic_test_getsymbol ("_strdate_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, 10) == 0 && strlen (buf) == 8);
      IC_TEST_CHECK ((*fct)(buf, 9) == 0 && strlen (buf) == 8);
      IC_TEST_CHECK ((*fct)(buf, 8) == ERANGE && errno == ERANGE && strlen (buf) == 0);
      strcpy (buf, "1");
      IC_TEST_CHECK ((*fct)(buf, 0) == EINVAL && errno == EINVAL && strlen (buf) == 1);
      IC_TEST_CHECK ((*fct)(NULL, 0) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 8) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 9) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 10) == EINVAL && errno == EINVAL);

      IC_TEST_CHECK ((*fct)((void *) (size_t) 1, 10) == 0);
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

