#include <icrt.h>
#include <windows.h>

void *
__iCrt_malloc (size_t sz)
{
  void *ret;
  
  ret = __iCrt_malloc_noerrno (sz);
  if (!ret)
    __iCrt_set_errno (ENOMEM);
  return ret;
}

void *
__iCrt_malloc_noerrno (size_t sz)
{
  if (sz == 0)
    sz = 1;
  return (void *) HeapAlloc (GetProcessHeap (), 0, sz);
}