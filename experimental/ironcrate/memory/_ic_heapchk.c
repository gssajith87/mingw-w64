#include <ic_stdc.h>

int __cdecl
_ic_heapchk (void)
{
  if (HeapValidate (_ic_theheap, 0, NULL))
    return IC_HEAP_OK;

  if (GetLastError () != ERROR_CALL_NOT_IMPLEMENTED)
    return IC_HEAP_BAD_NODE;

  _ic_doserrno = ERROR_CALL_NOT_IMPLEMENTED;
  ic_errno = IC_ENOSYS;
  return IC_HEAP_OK;
}

