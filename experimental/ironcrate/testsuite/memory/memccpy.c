#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl _memccpy (void *d, const void *s, int ch, size_t n).

   Flow-graph:
   (1): Is n == 0 then return NULL;
   (2): Copy until first occurance of ch characer s to d
   (3): Copy maximal n characters from s to d
   (4): If ch wasn't found return NULL, otherwise place of match + 1

Tests:
	For n == 0 return always NULL	
	If ch isn't found copy n characters and return NULL.
	If ch is found copy until this character and return next position.
*/

int
ic_test_main (int seq, int flags)
{
  char buf[20];
  void * (*fct)(void *, const void *, int, size_t) =
	ic_test_getsymbol ("_memccpy");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)(buf, "test", 'J', 0) == NULL);
      IC_TEST_CHECK ((*fct)(NULL, "test", 'J', 0) == NULL);
      IC_TEST_CHECK ((*fct)(buf, NULL, 'J', 0) == NULL);
      IC_TEST_CHECK ((*fct)(buf, "test XX", 'J', 8) == NULL);
      buf[8] = 0;
      IC_TEST_CHECK (strcmp (buf, "test XX") == 0);
      IC_TEST_CHECK ((*fct)(buf, "test JA", 'J', 8) == &buf[6]);
      buf[6] = 0;
      IC_TEST_CHECK (strcmp (buf, "test J") == 0);

      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

