#include <ic_stdc.h>

/* This routine places VAL at the beginning of the memory
   address P with 4 bytes size.
   The return is the address of P plus two-times pointer-size.  */
void * __cdecl
_ic_markalloca (void *p, unsigned int val)
{
  if (!p)
    return NULL;

  *((unsigned int *) p) = val;
  return ((char *) p + sizeof (void *) * 2);
}

