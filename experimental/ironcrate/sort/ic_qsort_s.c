#include <ic_stdc.h>

static void __cdecl
l_qsort (char *l, char *r, size_t sz, char *hswap,
	   int (__cdecl *fcmp) (void *, const void *, const void *), void *ctx)
{
  char *p, *max;

  while (r > l)
    {
      max = l;
      for (p = l + sz; p <= r; p += sz)
	{
	  if ((*fcmp) (ctx, p, max) > 0)
	    max = p;
	}

      if (max != r)
        {
	  ic_memcpy (hswap, max, sz);
	  ic_memcpy (max, r, sz);
	  ic_memcpy (r, hswap, sz);
	}

      r -= sz;
    }
}

void __cdecl
ic_qsort_s (void *addr, size_t n, size_t sz,
	    int (__cdecl *fcmp) (void *, const void *, const void *), void *ctx)
{
  char *l_sv[8 * sizeof (void *)], *r_sv[8 * sizeof (void *)];
  char *l, *l_p, *r, *r_p, *c, *hswap;
  size_t len;
  int deepth = 1;

  if ((!addr && n) || !sz || !fcmp)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return;
    }

  if (n < 2)
    return;

  hswap = alloca (sz);

  l_sv[0] = (char *) addr;
  r_sv[0] = (char *) addr + sz * (n - 1);

  do
    {
      --deepth;
      l = l_sv[deepth];
      r = r_sv[deepth];

      len = ((r - l) / sz) + 1;

      if (len <= 8)
        {
	  l_qsort (l, r, sz, hswap, fcmp, ctx);
	  if (!deepth)
	    break;
	  continue;
	}

      c = l + (len / 2) * sz;

      if ((*fcmp) (ctx, l, c) > 0)
	{
	  ic_memcpy (hswap, l, sz);
	  ic_memcpy (l, c, sz);
	  ic_memcpy (c, hswap, sz);
	}
      if ((*fcmp) (ctx, l, r) > 0)
	{
	  ic_memcpy (hswap, l, sz);
	  ic_memcpy (l, r, sz);
	  ic_memcpy (r, hswap, sz);
	}
      if ((*fcmp) (ctx, c, r) > 0)
        {
	  ic_memcpy (hswap, c, sz);
	  ic_memcpy (c, r, sz);
	  ic_memcpy (r, hswap, sz);
	}

      l_p = l;
      r_p = r;

      for (;;)
	{
	  if (c > l_p)
	    {
	      do
		l_p += sz;
	      while (l_p < c && (*fcmp) (ctx, l_p, c) <= 0);
	    }
	  if (c <= l_p)
	    {
	      do
		l_p += sz;
	      while (l_p <= r && (*fcmp) (ctx, l_p, c) <= 0);
	    }

	  do
	    r_p -= sz;
	  while (r_p > c && (*fcmp) (ctx, r_p, c) > 0);

	  if (r_p < l_p)
	    break;

	  if (l_p != r_p)
	    {
	      ic_memcpy (hswap, l_p, sz);
	      ic_memcpy (l_p, r_p, sz);
	      ic_memcpy (r_p, hswap, sz);
	    }

	  if (c == r_p)
	    c = l_p;
	}

      r_p += sz;
      if (c < r_p)
	{
	  do
	    r_p -= sz;
	  while (r_p > c && (*fcmp) (ctx, r_p, c) == 0);
	}

      if (c >= r_p)
	{
	  do
	    r_p -= sz;
	  while (r_p > l && (*fcmp) (ctx, r_p, c) == 0);
	}

      if ((r_p - l) >= (r - l_p))
	{
	  if (l < r_p)
	    {
	      l_sv[deepth] = l;
	      r_sv[deepth] = r_p;
	      ++deepth;
	    }

	  if (l_p < r)
	    {
	      l = l_p;
	      l_sv[deepth] = l;
	      r_sv[deepth] = r;
	      ++deepth;
	      continue;
	    }
	}
      else
	{
	  if (l_p < r)
	    {
	      l_sv[deepth] = l_p;
	      r_sv[deepth] = r;
	      ++deepth;               /* save big recursion for later */
	    }

	  if (l < r_p)
	    {
	      r = r_p;
	      l_sv[deepth] = l;
	      r_sv[deepth] = r;
	      ++deepth;
	      continue;
	    }
	}
    }
  while (deepth > 0);
}

