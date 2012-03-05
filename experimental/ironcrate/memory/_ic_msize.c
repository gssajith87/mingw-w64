#include <ic_stdc.h>

size_t __cdecl
_ic_msize (void *p)
{
  if (!p)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("p is NULL");
      return -1;
    }

  return (size_t) HeapSize (_ic_theheap, 0, p);
}

