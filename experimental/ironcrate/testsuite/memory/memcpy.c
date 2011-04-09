#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl memcpy (void *d, const void *s, size_t n).

   Flow-graph:
   (1): Is n == 0 then return d;
   (2): copy n charcters from s to d.
   (3): return original d

Tests:
	Test for n == 0 return of d.
	Test copying and result
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  void * (*fct)(void *, const void *, size_t) =
	ic_test_getsymbol ("memcpy");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL, NULL, 0) == NULL);
      IC_TEST_CHECK ((*fct)(buf, "abc", 0) == buf);
      IC_TEST_CHECK ((*fct)(buf, "abc", 4) == buf);
      IC_TEST_CHECK (memcmp (buf, "abc", 4) == 0);
      IC_TEST_CHECK ((*fct)(buf, "defghi", 4) == buf);
      IC_TEST_CHECK (memcmp (buf, "defg", 4) == 0);

      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

