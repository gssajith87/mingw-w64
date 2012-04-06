#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl _strlwr_s_l (char *s, size_t n, _locale_t pli).

   Flow-graph:
   (1): If s is nil, then return and set errno to EINVAL.
   (2): If n is less then strnlen of s, then set *s to zero, set errno 
	EINVAL, and return EINVAL,
   (3): If the LC_CTYPE locale isn't set, then convert range 'A'-'Z'
	to 'a'-'z', and return 0.
   (4): Map string s to LC_CTYPE locale and convert lower-case.
   (5): If mapping fails set errno to EILSEQ and return EILSEQ.
   (6): If n is smaller then amount of mapped characters then
	set *s zero, set errno to ERANGE, and return ERANGE.
   (7): Return zero.
Tests:
	Test for s == NULL.
	Test for n == (size_t) -1.
	Test for strnlen (s, n) >= n.
*/

int
ic_test_main (int seq, int flags)
{
  char tst[] = "abcABC";
  char ts2[] = "jOEJoe";
  errno_t (*fct)(char *, size_t, _locale_t) =
	ic_test_getsymbol ("_strlwr_s_l");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, (size_t) -1, NULL) == EINVAL && errno == EINVAL);
      IC_TEST_CHECK ((*fct)(tst, (size_t) -1, NULL) == 0);
      IC_TEST_CHECK (tst[0] == tst[3] && tst[1] == tst[4] && tst[2] == tst[5]);
      IC_TEST_CHECK ((*fct)(tst, 6, NULL) == EINVAL && tst[0] == 0);
      IC_TEST_CHECK ((*fct)(ts2, 7, NULL) == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

