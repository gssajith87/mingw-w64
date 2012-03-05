#include <ic_stdc.h>

void * __cdecl
_ic_aligned_recalloc (void *p, size_t n, size_t sz, size_t align)
{
  return _ic_aligned_offset_recalloc (p, n, sz, align, 0);
}

