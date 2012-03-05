#include <ic_stdc.h>

intptr_t __cdecl
_ic_get_heap_handle (void)
{
  return (intptr_t) _ic_theheap;
}

