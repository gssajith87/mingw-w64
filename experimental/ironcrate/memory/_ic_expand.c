#include <ic_stdc.h>

void * __cdecl
_ic_expand (void *p, size_t sz)
{
  void *ret;
#ifdef __x86_64__
    size_t oldsize;
#endif

  if (!p)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("p is NULL");
      return NULL;
    }

  if (sz > _IC_HEAP_MAX_REQUESTED_SIZE)
    {
      ic_errno = IC_ENOMEM;
      return NULL;
    }

  if (!sz)
    sz = 1;

#ifdef __x86_64__
  oldsize = (size_t) HeapSize (_ic_theheap, 0, p);
#endif

  if (!(ret = HeapReAlloc (_ic_theheap, HEAP_REALLOC_IN_PLACE_ONLY, p, sz)))
    {
#ifdef __x86_64__
      if (oldsize != (size_t) -1 && sz <= oldsize)
	return p;
#endif
      ic_errno = _ic_get_errno_from_winerr (GetLastError ());
    }

  return ret;
}

