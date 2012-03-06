#include <ic_stdc.h>

unsigned long __cdecl
__ic_threadid (void)
{
  return GetCurrentThreadId ();
}

