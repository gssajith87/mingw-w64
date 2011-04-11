#include "../testlib/main_test.c"
#include <errno.h>

/* char * __cdecl _strdup (const char *s).

   Flow-graph:
   (1): If s is NULL then return NULL.
   (2): Allocate via malloc length of string s plus one character.
   (3): If allocation fails return NULL.
   (4): Else copy string s into allocated buffer by strcpy.
   (5): Return pointer of new allocated buffer.

Tests:
	Test for s == NULL.
	Test for s == valid string
	Test for s == invalid string.
*/

int
ic_test_main (int seq, int flags)
{
  char *r;
  char * (*fct)(const char *) =
	ic_test_getsymbol ("_strdup");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((r = (*fct)("abc")) !=NULL && strcmp (r, "abc") == 0);
      IC_TEST_CHECK ((r = (*fct)(NULL)) == NULL);
      IC_TEST_CHECK ((*fct)((char *) (size_t) 1) == 0);
      return IC_TEST_RSLT_FAILED;
    case 1:
      IC_TEST_CHECK (ic_test_segfault != 0);
      ic_test_reset_internal_vars ();
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

