#include "../testlib/main_test.c"
#include <errno.h>

/* size_t __cdecl __strncnt (const char *s, size_t n).

   Flow-graph:
   (1): Iterate through s until n characters are checked, or *s == 0.
   (2): Return number of read chacters without the optional tailing zero.
Tests:
	Test for s == NULL and n == 0, that 0 is returned.
	Test for s == valid string with bigger n then strlen(s) + 1.
	Test for s == valid string with smaller n then strlen (s)
	Test for s == invalid string with n == 0 returning zero.
	Test for s == invalid string with n > 0 is seg-faulting.
*/

int
ic_test_main (int seq, int flags)
{
  size_t (*fct)(const char *, size_t) =
	ic_test_getsymbol ("__strncnt");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc", 3) == 3);
      IC_TEST_CHECK ((*fct)("abc", 2) == 2);
      IC_TEST_CHECK ((*fct)("abc", 5) == 3);
      IC_TEST_CHECK ((*fct)("", 1) == 0);
      IC_TEST_CHECK ((*fct)(NULL, 0) == 0);
      IC_TEST_CHECK ((*fct)((void *) (size_t) 1, 0) == 0);
      IC_TEST_CHECK ((*fct)(NULL, 1) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      IC_TEST_CHECK ((*fct)((char *) (size_t) 1, 1) == 0);
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

