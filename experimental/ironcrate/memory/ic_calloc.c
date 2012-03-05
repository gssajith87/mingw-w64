#include <ic_stdc.h>

void * __cdecl
ic_calloc (size_t n, size_t sz)
{
  size_t sv_sz;
  void *r;

  if (n != 0 && sz > (_IC_HEAP_MAX_REQUESTED_SIZE / n))
    {
      ic_errno = IC_ENOMEM;
      IC_INV_PARAM("Invalid argument");
      return NULL;
    }

  if ((sz = sv_sz = sz * n) == 0)
    sz = 1;

  if (sz > _IC_HEAP_MAX_REQUESTED_SIZE)
    {
      while (_ic_newmode && _ic_callnewh (sz))
        ;
      ic_errno = IC_ENOMEM;
      return NULL;
    }

  do
    {
      if ((r = HeapAlloc (_ic_theheap, HEAP_ZERO_MEMORY, sz)) != NULL)
        return r;
    }
  while (_ic_newmode && _ic_callnewh (sz));

  ic_errno = IC_ENOMEM;

  return r;
}

