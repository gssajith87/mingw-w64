#include "../testlib/main_test.c"
#include <errno.h>

/* int __cdecl tolower (int).

   Flow-graph:
   (1): If locale was changed call _toupper_l.
   (2): Else if c is in range of 'A'-'Z', return uppercase letter
	otherwise return c.
Tests:
	Test for range of c > -1 .. c < 0x100.
*/

int
ic_test_main (int seq, int flags)
{
  int (*fct)(int) =
	ic_test_getsymbol ("tolower");
  int i;
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      for (i = 0; i < 'A'; i++)
	IC_TEST_CHECK ((*fct)(i) == i);
      for (; i <= 'Z'; i++)
	IC_TEST_CHECK (((*fct)(i) - i) == ('a' - 'A'));
      for (; i < 256; i++)
	IC_TEST_CHECK ((*fct)(i) == i);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

