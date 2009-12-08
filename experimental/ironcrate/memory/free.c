#include <icrt.h>
#include <windows.h>

void
__iCrt_free (void *ptr)
{
  HeapFree (GetProcessHeap (), 0, ptr);
}
