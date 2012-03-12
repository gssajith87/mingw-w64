#include <ic_stdc.h>

void * __cdecl
_ic_lsearch (const void *key, void *b, unsigned int *pn, size_t sz,
	     int (__cdecl *fcmp)(const void *, const void *))
{
  unsigned int p;

  if (!key || !pn || !b || !sz || !fcmp)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  for (p = *pn; p > 0; p--)
    {
      if ((*fcmp) (key, b) == 0)
	return b;
      b = (char *) b + sz;
    }

  ic_memcpy (b, key, sz);
  pn[0] += 1;

  return b;
}

