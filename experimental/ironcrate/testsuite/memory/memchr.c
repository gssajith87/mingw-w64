#include "../testlib/main_test.c"
#include <errno.h>

/* void * __cdecl memchr (const void *buf, int ch, size_t n).

   Flow-graph:
   (1): Is n == 0 then return NULL;
   (2): Search in range of n characters for first occurance of ch
   (3): If ch wasn't found return NULL, otherwise place of match

Tests:
	For n == 0 return always NULL	
	If ch isn't found in n characters thenreturn NULL.
	If ch is found return its position.
*/

int
ic_test_main (int seq, int flags)
{
  void *r;
  void * (*fct)(void *, int, size_t) =
	ic_test_getsymbol ("memchr");
  if (!fct)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      IC_TEST_CHECK ((*fct)("test", 'J', 0) == NULL);
      IC_TEST_CHECK ((*fct)(NULL, 'J', 0) == NULL);
      IC_TEST_CHECK ((*fct)("test XX", 'J', 8) == NULL);
      IC_TEST_CHECK ((r = (*fct)("test JA", 'J', 8)) != NULL);
      IC_TEST_CHECK (r && *((char*)r) == 'J');

      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}

