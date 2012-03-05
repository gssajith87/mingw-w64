#include <ic_stdc.h>

void __cdecl
_ic_heap_term (void)
{
  if (_ic_theheap)
    HeapDestroy (_ic_theheap);
  _ic_theheap = NULL;
}

