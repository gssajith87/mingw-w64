#include <icrt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/fc7etheh%28VS.71%29.aspx */

int
__iCrt_heapmin (void)
{
  if (!HeapCompact (GetProcessHeap (), 0))
    {
      if (GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
        __iCrt_set_doserrno (GetLastError ());
      else
	__iCrt_set_errno (ENOSYS);
      return -1;
    }
  return 0;
}
