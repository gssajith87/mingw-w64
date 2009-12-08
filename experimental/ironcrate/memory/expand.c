#include <icrt.h>
#include <windows.h>

void *
__iCrt_expand (void *mem, size_t sz)
{
  return HeapReAlloc (GetProcessHeap(), HEAP_REALLOC_IN_PLACE_ONLY, mem, sz);
}
