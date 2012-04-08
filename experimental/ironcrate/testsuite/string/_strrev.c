#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl _strrev (char *d).

   Flow-graph:
   (1): Invert characters in string d until terminating zero-character.
   (2): Return d;
Tests:
	Test for d == valid string d
	Test for s == invalid string d
*/

int
ic_test_main (int seq, int flags)
{
  char t[] = "abcde";
  char * (*fct)(char *) =
	ic_test_getsymbol ("_strrev");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(NULL) == NULL);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(t) == t && t[0] == 'e' && t[1] == 'd'
		     && t[2] == 'c' && t[3] == 'b' && t[4] == 'a');
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

