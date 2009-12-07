#include <w64crt.h>
#include <windows.h>

void *
__w64crt_malloc (size_t sz)
{
  void *ret = HeapAlloc (GetProcessHeap (), 0, sz);
  if (!ret)
    __w64crt_set_errno (ENOMEM);
  return ret;
}
