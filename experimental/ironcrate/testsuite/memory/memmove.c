#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl memmove_s (void *d, const void *s, size_t n).

   Flow-graph:
   (1): Is n == 0 then return d;
   (2): If d <= s or (s + n) < d then copy byte-wise from left to right.
   (3): Otherwise copy byte-wise from right to left.
   (4): Return d.

Tests:
	Test for n == 0 and it is first check.
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  void * (*fct)(void *, const void *, size_t) =
	ic_test_getsymbol ("memmove");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, "test", 0) == buf);
      IC_TEST_CHECK ((*fct)(NULL, NULL, 0) == NULL);
      IC_TEST_CHECK ((*fct)(buf, "test", 5) == buf);
      IC_TEST_CHECK ((*fct)(buf, &buf[1], 4) == buf);
      IC_TEST_CHECK (strcmp (buf, "est") == 0);
      IC_TEST_CHECK ((*fct)(&buf[1], buf, 4) == &buf[1]);
      IC_TEST_CHECK (strcmp (buf, "eest") == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

