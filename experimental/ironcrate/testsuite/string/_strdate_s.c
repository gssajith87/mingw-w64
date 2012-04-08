#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl _strdate_s (char *d, size_t dn).

   Flow-graph:
   (1): If d or dn is zero, then set errno to EINVAL, and return EINVAL.
   (2): Set *d to zero.
   (3): If dn is less then 9 set errno to ERANGE, and return ERANGE.
   (4): Set d in format MM/DD/YY by result of GetLocalTime.
   (5): Return 0.
Tests:
	Test for d == NULL and/or dn == 0
	Test for d == valid string and dn > 0 && dn < 9
	Test for s == valid string and dn >= 9
*/

int
ic_test_main (int seq, int flags)
{
  char t[12];
  errno_t (*fct)(char *, size_t) =
	ic_test_getsymbol ("_strdate_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, 0) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 1) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(t, 0) == EINVAL && errno == EINVAL);
      t[0] = 'a';
      IC_TEST_CHECK ((*fct)(t, 1) == ERANGE && errno == ERANGE);
      IC_TEST_CHECK (t[0] == 0);
      IC_TEST_CHECK ((*fct)((char *) (size_t) 1, 9) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(t, 9) == 0 && t[2] == '/' && t[5] == '/');
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

