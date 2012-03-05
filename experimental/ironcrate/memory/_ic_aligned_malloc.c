#include <ic_stdc.h>

void * __cdecl
_ic_aligned_malloc (size_t sz, size_t align)
{
  return _ic_aligned_offset_malloc (sz, align, 0);
}

