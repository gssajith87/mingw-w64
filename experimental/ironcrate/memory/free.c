#include <icrt.h>
#include <windows.h>

void
__iCrt_free (void *ptr)
{
  __iCrt_free_noerrno (ptr);
}

void
__iCrt_free_noerrno (void *ptr)
{
  if (ptr)
    HeapFree (GetProcessHeap (), 0, ptr);
}
