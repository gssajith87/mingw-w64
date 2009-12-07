#include <icrt.h>
#include <windows.h>

size_t
__w64crt_msize (void *ptr)
{
  return (size_t) HeapSize (GetProcessHeap (), 0, ptr);
}
