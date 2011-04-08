#include "../testlib/main_test.c"
#include <errno.h>

/* errno_t __cdecl memmove_s (void *d, size_t dn, const void *s, size_t n).

   Flow-graph:
   (1): Is n == 0 then return 0;
   (2): Is d or s NULL then set errno to EINVAL (with possible invalid_para
	notice) and return EINVAL.
   (3): Is dn < n then set errno to ERANGE (with possible invalid_para notice)
	and return ERANGE
   (4): Call memmove and return 0.

Tests:
	Test for n == 0 and it is first check.
	Test for s or d NULL is second check.
	Test for dn < n is third check.
*/

int
ic_test_main (int seq, int flags)
{
  char buf1[20], but2[20];
  errno_t (*fct)(void *, size_t, const void *, size_t) =
	ic_test_getsymbol ("memmove_s");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      if ((*fct)(buf, 20, "test", 0) != 0) break;
      if ((*fct)(NULL, 0, NULL, 0) != 0) break;
      if (ic_test_segfault || ic_test_invalid_parameter_called)
	break;
      if ((*fct)(NULL, 0, NULL, 4) != EINVAL) break;
      ic_test_reset_internal_vars ();
      if ((*fct)(NULL, 4, NULL, 4) != EINVAL) break;
      ic_test_reset_internal_vars ();
      if ((*fct)(buf, 3, "test", 4) != ERANGE) break;
      ic_test_reset_internal_vars ();
      if ((*fct)(buf, 4, "test", 4) != 0) break;
      if ((*fct)(buf, 5, "test", 4) != 0) break;
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

