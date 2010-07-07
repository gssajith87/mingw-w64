#include <icrt.h>
#include <windows.h>

void *
__iCrt_calloc (size_t sz, size_t cnt)
{
  return __iCrt_calloc_noerrno (sz, cnt);
}

void *
__iCrt_calloc_noerrno (size_t sz, size_t cnt)
{
  return HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, sz * cnt);
}
