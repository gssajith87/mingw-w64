#include <ic_stdc.h>

void * __cdecl
_ic_recalloc (void *p, size_t n, size_t sz)
{
  void *r;
  size_t  n_sz, o_sz = 0;

  if (n > 0 && sz > (_IC_HEAP_MAX_REQUESTED_SIZE / n))
    {
      ic_errno = IC_ENOMEM;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  n_sz = sz * n;

  if (p)
    o_sz = _ic_msize (p);

  if ((r = ic_realloc (p, n_sz)) != NULL && o_sz < n_sz)
    ic_memset ((char *) r + o_sz, 0, n_sz - o_sz);

  return r;
}

