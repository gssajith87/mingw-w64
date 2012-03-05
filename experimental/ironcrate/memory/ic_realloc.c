#include <ic_stdc.h>

void * __cdecl
ic_realloc (void *p, size_t n)
{
  void *r;

  if (!p)
    return ic_malloc (n);

  if (!n)
    {
      ic_free (p);
      return NULL;
    }

  if (n > _IC_HEAP_MAX_REQUESTED_SIZE)
    {
      _ic_callnewh (n);
      ic_errno = IC_ENOMEM;
      return NULL;
    }

  do
    {
      if ((r = HeapReAlloc (_ic_theheap, 0, p, n)) != NULL)
        return r;
    }
  while (_ic_newmode && _ic_callnewh (n));

  ic_errno = _ic_get_errno_from_winerr (GetLastError ());
  return NULL;
}

