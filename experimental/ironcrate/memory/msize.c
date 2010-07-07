#include <icrt.h>
#include <windows.h>

size_t
__iCrt_msize (void *ptr)
{
  return (size_t) HeapSize (GetProcessHeap (), 0, ptr);
}
