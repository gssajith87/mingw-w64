#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl memset (void *d, int ch, size_t n).

   Flow-graph:
   (1): Is n == 0 then return d;
   (2): Fill n bytes in d from left to right with char ch.
   (4): Return d.

Tests:
	Test for n == 0 and it is first check.
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  void * (*fct)(void *, int, size_t) =
	ic_test_getsymbol ("memset");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, 0, 0) == buf);
      IC_TEST_CHECK ((*fct)(NULL, 0, 0) == NULL);
      IC_TEST_CHECK ((*fct)(buf, 0, 5) == buf);
      IC_TEST_CHECK ((*fct)(buf, 'a', 4) == buf);
      IC_TEST_CHECK (strcmp (buf, "aaaa") == 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

