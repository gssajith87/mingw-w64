#include "../testlib/main_test.c"
#include <errno.h>

/* size_t __cdecl strcspn (const char *s, const char *c);


   Flow-graph:
   (1): Use a bit map of 256 bits to indicate characters described in c. The 0 is indicated, too.
   (2): Return the number of characters in string s from left to right, which aren't indicated
   	in map.

Tests:
	Test for all characters in c aren't part of s.
	Test for all characters in s are part of c.
	Test for empty s and/or c.
	Test for c and/or s NULL, or invalid.
*/

int
ic_test_main (int seq, int flags)
{
  size_t (*fct)(const char *, const char *) =
	ic_test_getsymbol ("strcspn");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("", "") == 0);
      IC_TEST_CHECK ((*fct)("123", "abc") == 3);
      IC_TEST_CHECK ((*fct)("12a3", "abc") == 2);
      IC_TEST_CHECK ((*fct)("123123", "123") == 0);
      IC_TEST_CHECK ((*fct)(NULL, "abc") == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc", NULL) == 0);
      return IC_TEST_RSLT_FAILED;
    case 2:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

