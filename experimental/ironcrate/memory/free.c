#include <icrt.h>
#include <windows.h>

void
__w64crt_free (void *ptr)
{
  HeapFree (GetProcessHeap (), 0, ptr);
}
