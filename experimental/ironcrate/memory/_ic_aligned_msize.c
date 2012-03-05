#include <ic_stdc.h>

size_t __cdecl
_ic_aligned_msize (void *p, size_t align, size_t o)
{
  size_t sz, sz_top, sz_bottom;
  uintptr_t ip, gap;

  if (!p)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return -1;
    }

  ip = *((uintptr_t *) ((((uintptr_t) p) & ~(sizeof (void *) - 1)) - sizeof (void *)));

  if (align < sizeof (void *))
    align = sizeof (void *);
  align -= 1;
  gap = (0 - o) & (sizeof (void *) - 1);

  sz = _ic_msize ((void*) ip);
  sz_top = (uintptr_t) p - ip;
  sz_bottom = gap + align + sizeof (void *) - sz_top;

  return (sz - (sz_top + sz_bottom));
}

