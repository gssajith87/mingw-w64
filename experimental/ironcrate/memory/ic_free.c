#include <ic_stdc.h>

void __cdecl
ic_free (void *p)
{
  if (!p)
    return;

  if (!HeapFree (_ic_theheap, 0, p))
    ic_errno = _ic_get_errno_from_winerr (GetLastError ());
}

