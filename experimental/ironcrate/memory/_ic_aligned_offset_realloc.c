#include <ic_stdc.h>

void * __cdecl
_ic_aligned_offset_realloc (void *p, size_t sz, size_t align,size_t o)
{
  int free_old = 0;
  ic_errno_t e_sv;
  uintptr_t ip, gap, r, base_p, sz_diff, sz_move, sz_new;

  if (!p)
    return _ic_aligned_offset_malloc (sz, align, o);

  if (!sz)
    {
      _ic_aligned_free (p);
      return NULL;
    }

  if ((align & (align - 1)) != 0
      || (o != 0 && o >= sz))
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  base_p = *((uintptr_t *) ((((uintptr_t) p) & ~(sizeof (void *) - 1)) - sizeof (void *)));

  if (align < sizeof (void *))
    align = sizeof (void *);
  align -= 1;

  gap = (0 - o) & (sizeof (void *) - 1);

  sz_diff = (uintptr_t) p - base_p;
  sz_move = _ic_msize ((void *) base_p) - ((uintptr_t) p - base_p);
  if (sz_move > sz)
    sz_move = sz;
  sz_new = sizeof (void *) + gap + align + sz;

  if ((base_p + align + sizeof (void *) + gap) < (uintptr_t) p)
    {
      free_old = 1;

      if (!(ip = (uintptr_t) ic_malloc (sz_new)))
	return NULL;
    }
  else
    {
      /* Restore old errno on failure  */
      e_sv = ic_errno;
      ip = (uintptr_t) _ic_expand ((void *) base_p, sz_new)

      if (!ip)
	{
	  ic_errno = e_sv;
	  if (!(ip = (uintptr_t) ic_malloc (sz_new)))
	    return NULL;
	  free_old = 1;
	}
      else
	base_p = ip;
    }

  if (ip == ((uintptr_t) p - sz_diff)
      && (((size_t) p + gap + o) & ~align) == 0)
    return p;

  r = ((ip + sizeof (void *) + gap + align + o) & ~align) - o;

  if (sz_move)
    ic_memmove ((void *) r, (void *) (base_p + sz_diff), sz_move);

  if (free_old)
    ic_free ((void *) base_p);
  ((uintptr_t *)(r - gap))[-1] = ip;

  return (void *) r;
}

