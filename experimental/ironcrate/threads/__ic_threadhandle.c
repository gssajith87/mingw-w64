#include <ic_stdc.h>

uintptr_t __cdecl
__ic_threadhandle (void)
{
  return (uintptr_t) GetCurrentThread ();
}

