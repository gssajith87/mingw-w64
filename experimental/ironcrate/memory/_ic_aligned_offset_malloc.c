#include <ic_stdc.h>

void * __cdecl
_ic_aligned_offset_malloc (size_t sz, size_t align, size_t o)
{
  uintptr_t ip, gap, r;

  if ((align & (align - 1)) != 0 || (o != 0 && o >= sz))
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  if (align < sizeof (void *))
    align = sizeof (void *);
  align -= 1;

  gap = (0 - o) & (sizeof (void *) - 1);

  if (!(ip = (uintptr_t) ic_malloc (sizeof (void *) + gap + align + sz)))
    return NULL;

  r = ((ip + sizeof (void *) + gap + align + o) & ~align) - o;

  ((uintptr_t *)(r - gap))[-1] = ip;

  return (void *) r;
}

