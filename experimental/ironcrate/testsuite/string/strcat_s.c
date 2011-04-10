#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl strcat_s (char *d, size_t n, const char *s).

   Flow-graph:
	(1) If s, d, or n is zero/NULL set errno to EINVAL, raise optional
	invalid parameter handler, and return EINVAL.  If d and n aren't
	NULL/zero, but s, then set first character of d to zero.
	(2) Find position in d of zero character. If position is wider
	then range specified by n, then set first character in d to zero,
	set errno to EINVAL, raise optional invalid parameter handler,
	and return EINVAL.
	(3) Cat s to d until nul-character of s, or range n is exceeded.
	(4) If range n is overflowing then set first character of d to
	zero, set errno to ERANGE, raise optional invalid parameter
	handle, and return ERANGE.
	(5) Return 0 as result.
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
  errno_t (*fct)(char *, size_t, const char *) =
	ic_test_getsymbol ("strcat_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      buf[0] = 0;
      IC_TEST_CHECK ((*fct)(buf, 0, "test") == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 0, "test") == EINVAL);
      IC_TEST_CHECK ((*fct)(NULL, 0, NULL) == EINVAL);
      buf[0] = 'x'; buf[1] = 0;
      IC_TEST_CHECK ((*fct)(buf, 1, NULL) == EINVAL);
      IC_TEST_CHECK (buf[0] == 0);
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, 2, "a") == EINVAL && buf[0] == 0);
      strcpy (buf, "x");
      IC_TEST_CHECK ((*fct)(buf, 3, "abc") == ERANGE && buf[0] == 0);
      strcpy (buf, "__");
      IC_TEST_CHECK ((*fct)(buf, 10, "abc") == 0 && strcmp (buf, "__abc") == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

