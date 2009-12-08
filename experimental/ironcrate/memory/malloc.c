#include <icrt.h>
#include <windows.h>

void *
__iCrt_malloc (size_t sz)
{
  void *ret = HeapAlloc (GetProcessHeap (), 0, sz);
  if (!ret)
    __iCrt_set_errno (ENOMEM);
  return ret;
}
