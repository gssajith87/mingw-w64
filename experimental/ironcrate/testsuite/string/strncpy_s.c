#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl strncpy_s (char *d, size_t dn, const char *s, size_t n).

   Flow-graph:
	(1) If n, dn, and d are zero, return 0.
	(2) If s, d, dn, or n is zero/NULL set errno to EINVAL, raise optional
	invalid parameter handler, and return EINVAL.  If d and n aren't
	NULL/zero, but s, then set first character of d to zero.
	(3) Copy s to d until nul-character of s, or range n is exceeded, or
	range dn is exceeded.
	(4) If range dn is overflowing then set first character of d to
	zero, set errno to ERANGE, raise optional invalid parameter
	handle, and return ERANGE. If n == -1, then set d[dn -1] to zero,
	and return STRUNCATE.
	(5) Return 0 as result.
Tests:
	Test for d and/or n zero.
	Test for s == NULL and d != NULL, and n != 0.
	Test for s is wider then specifed n.
	Test successful state.
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  errno_t (*fct)(char *, size_t, const char *, size_t) =
	ic_test_getsymbol ("strncpy_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      buf[0] = 0;
      IC_TEST_CHECK ((*fct)(buf, 0, "test", 4) == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 0, "test", 4) == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 0, NULL, 4) == EINVAL);
      buf[0] = 'x'; buf[1] = 0;
      IC_TEST_CHECK ((*fct)(buf, 1, NULL, 2) == EINVAL);
      IC_TEST_CHECK (buf[0] == 0);
      strcpy (buf, "x");
      IC_TEST_CHECK ((*fct)(buf, 3, "abc", 4) == ERANGE && buf[0] == 0);
      IC_TEST_CHECK ((*fct)(buf, 10, "abc", 4) == 0 && strcmp (buf, "abc") == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

