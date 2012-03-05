#include <ic_stdc.h>

int __cdecl
_ic_heap_init (int mt)
{
#ifdef __x86_64__
  ULONG HeapType = 2;

  if (!(_ic_theheap = HeapCreate (0, 0x1000, 0)))
    return 0;
  HeapSetInformation (_ic_theheap, HeapCompatibilityInformation, &HeapType, 4);
#else
  if (!(_ic_theheap = HeapCreate (mt ? 0 : HEAP_NO_SERIALIZE, 0x1000, 0)))
    return 0;
#endif

  return 1;
}

