#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl strpbrk (const char *s, const char *c);


   Flow-graph:
   (1): Use a bit map of 256 bits to indicate characters described in c.
   (2): Return the position of first mapped character in string s from left to right.
   (3): If none was found return NULL.

Tests:
	Test for all characters in c aren't part of s.
	Test for all characters in s are part of c.
	Test for empty s and/or c.
	Test for c and/or s NULL, or invalid.
*/

int
ic_test_main (int seq, int flags)
{
  const char *t1 = "12a3";
  const char *t2 = "b12a3";
  const char *t3 = "123123";
  char * (*fct)(const char *, const char *) =
	ic_test_getsymbol ("strpbrk");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("", "") == NULL);
      IC_TEST_CHECK ((*fct)("123", "abc") == NULL);
      IC_TEST_CHECK ((*fct)(t1, "abc") == &t1[2]);
      IC_TEST_CHECK ((*fct)(t2, "abc") == &t2[0]);
      IC_TEST_CHECK ((*fct)(t3, "123") == &t3[0]);
      IC_TEST_CHECK ((*fct)(NULL, "abc") == NULL);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("abc", NULL) == NULL);
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

