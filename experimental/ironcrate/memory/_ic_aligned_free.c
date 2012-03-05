#include <ic_stdc.h>

void  __cdecl
_ic_aligned_free (void *p)
{
  if (!p)
    return;

  ic_free ((void *) *((uintptr_t *) ((((uintptr_t) p) & ~(sizeof (void *) - 1)) - sizeof (void *))));
}

