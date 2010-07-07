#include <icrt.h>
#include <windows.h>

void *
__iCrt_realloc (void *ptr, size_t sz)
{
  if (!ptr && !sz)
    return NULL;
  if (!ptr)
    return __iCrt_malloc (sz);
  if (sz)
    return HeapReAlloc (GetProcessHeap (), 0, ptr, sz);
  __iCrt_free (ptr);
  return NULL;
}

void *
__iCrt_realloc_noerrno (void *ptr, size_t sz)
{
  if (!ptr && !sz)
    return NULL;
  if (!ptr)
    return __iCrt_malloc_noerrno (sz);
  if (sz)
    return HeapReAlloc (GetProcessHeap (), 0, ptr, sz);
  __iCrt_free_noerrno (ptr);
  return NULL;
}
