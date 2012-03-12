#include <ic_stdc.h>

void * __cdecl
_ic_lfind (const void *k, const void *b, unsigned int *pn, size_t sz,
	   int (__cdecl *fcmp)(const void *, const void *))
{
  unsigned int p;

  if (!k || !b || !sz || !pn || !fcmp)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return NULL;
    }

  for (p = *pn; p > 0; p--)
    {
      if ((*fcmp) (k, b) == 0)
	return (void *) b;
      b = (const char *) b + sz;
    }

  return NULL;
}

