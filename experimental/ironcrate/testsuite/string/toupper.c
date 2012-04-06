#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl toupper (int).

   Flow-graph:
   (1): If locale was changed call _toupper_l.
   (2): Else if c is in range of 'a'-'z', return uppercase letter
	otherwise return c.
Tests:
	Test for range of c > -1 .. c < 0x100.
*/

int
ic_test_main (int seq, int flags)
{
  int (*fct)(int) =
	ic_test_getsymbol ("toupper");
  int i;
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      for (i = 0; i < 'a'; i++)
	IC_TEST_CHECK ((*fct)(i) == i);
      for (; i <= 'z'; i++)
	IC_TEST_CHECK (((*fct)(i) - i) == ('A' - 'a'));
      for (; i < 256; i++)
	IC_TEST_CHECK ((*fct)(i) == i);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

