#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl strncat_s (char *d, size_t dn, const char *s, size_t n).

   Flow-graph:
	(1) If n and d and dn are zero, return 0.
	(2) If s, d, or dn is zero/NULL set errno to EINVAL, raise optional
	invalid parameter handler, and return EINVAL.  If d and n aren't
	NULL/zero, but s, then set first character of d to zero.
	(3) Find position in d of zero character. If position is wider
	then range specified by n, then set first character in d to zero,
	set errno to EINVAL, raise optional invalid parameter handler,
	and return EINVAL.
	(4) Cat s to d until nul-character of s, or range n is exceeded,
	or range dn is exceeded.
	(5) If range dn is overflowing then set first character of d to
	zero, set errno to ERANGE, raise optional invalid parameter
	handle, and return ERANGE.
	(6) Return 0 as result.
Tests:
	Test for d and/or n zero.
	Test for s == NULL and d != NULL, and n != 0.
	Test for string in d is wider then specified n.
	Test for d + s is wider then specifed n.
	Test successful state.
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  errno_t (*fct)(char *, size_t, const char *, size_t) =
	ic_test_getsymbol ("strncat_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      buf[0] = 0;
      IC_TEST_CHECK ((*fct)(NULL, 0, NULL, 0) == 0);
      IC_TEST_CHECK ((*fct)(buf, 0, "test", 0) == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 1, "test", 0) == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 1, NULL, 0) == EINVAL);
      buf[0] = 'x'; buf[1] = 0;
      IC_TEST_CHECK ((*fct)(buf, 1, NULL, 1) == EINVAL);
      IC_TEST_CHECK (buf[0] == 0);
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, 2, "a", 1) == EINVAL && buf[0] == 0);
      strcpy (buf, "x");
      IC_TEST_CHECK ((*fct)(buf, 3, "abc", 3) == ERANGE && buf[0] == 0);
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, 10, "abc", 4) == 0 && strcmp (buf, "__abc") == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

