#include <ic_stdc.h>

int __cdecl
_ic_heapmin (void)
{
  if (HeapCompact (_ic_theheap, 0))
    return 0;

  if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
    {
      _ic_doserrno = ERROR_CALL_NOT_IMPLEMENTED;
      ic_errno = IC_ENOSYS;
    }

  return -1;
}

