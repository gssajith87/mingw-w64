#include <icrt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/2xse74he%28VS.71%29.aspx */

int
__w64crt_heapchk (void)
{
  if (!GetProcessHeap ())
    {
      __w64crt_set_doserrno (GetLastError());
      return _HEAPBADBEGIN;
    }
  if (!HeapValidate (GetProcessHeap (), 0, NULL))
    {
      __w64crt_set_doserrno (GetLastError());
      return _HEAPBADNODE;
  }
  return _HEAPOK;
}
