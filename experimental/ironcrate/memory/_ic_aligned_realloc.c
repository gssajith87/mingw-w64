#include <ic_stdc.h>

void * __cdecl
_ic_aligned_realloc (void *p, size_t sz, size_t align)
{
  return _ic_aligned_offset_realloc (p, sz, align, 0);
}

