#include <ic_stdc.h>

void * __cdecl
ic_bsearch_s (const void *k, const void *b, size_t n, size_t e_sz,
	      int (__cdecl *fcmp)(void *, const void *, const void *), void *ctx)
{
  const char *l, *r, *c;
  size_t p;
  int e;

  if ((!b && n) || !e_sz || !fcmp)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  l = (const char *) b;
  r = l + (n - 1) * e_sz;

  while (l <= r && n)
    {
      if ((p = n / 2) == 0)
        return ((*fcmp) (ctx, k, l) ? NULL : l);

      c = l + ((n & 1) != 0 ? p : (p - 1)) * e_sz;
      if (!(e = (*fcmp)(ctx, k, c)))
	return c;

      if (e > 0)
	{
	  l = c + e_sz;
	  n = p;
	}
      else
	{
	  r = c - e_sz;
	  n = ((n & 1) != 0 ? p : p - 1);
	}
    }

  return NULL;
}

