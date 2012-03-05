#include <ic_stdc.h>

void * __cdecl
_ic_aligned_offset_recalloc (void *p, size_t n, size_t sz, size_t align, size_t o)
{
  void *r = NULL;
  size_t sz_dta, p_dta = 0;
  uintptr_t ip = 0;

  if (n > 0 && (_IC_HEAP_MAX_REQUESTED_SIZE / n) < sz)
    {
      ic_errno = IC_ENOMEM;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  sz_dta = sz * n;

  if (p != NULL)
    p_dta = _ic_aligned_msize (p, align, o);

  r = _ic_aligned_offset_realloc (p, sz_dta, align, o);

  if (r && p_dta < sz_dta)
    ic_memset ((char *) r + p_dta, 0, sz_dta - p_dta);
  return r;
}

