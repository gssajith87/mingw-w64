#include <ic_stdc.h>

/* Test: memory/memicmp_l.c  */

int __cdecl
_ic_memicmp_l (const void *s1, const void *s2, size_t n, ic_slocal_t *pli)
{
  int c1 = 0, c2 = 0;
  const char *d = (const char *) s1;
  const char *s = (const char *) s2;
  ic_lctemp_t hlp;

  if ((!s1 && n != 0) || (!s2 && n != 0))
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return 0x7fffffff;
    }

  ic_lctemp_init (pli, &hlp);

  if (hlp.li.locinfo)[IC_LC_CTYPE] == 0)
    {
      ic_lctemp_dest (&hlp);
      return __ic_memicmp_a (s1, s2, n);
    }

  while (n != 0 && c1 == c2)
    {
      --n;
      c1 = _ic_tolower_l ((unsigned char) (*(d++)), &hlp.li);
      c2 = _ic_tolower_l ((unsigned char) (*(s++)), &hlp.li);
    }
  ic_lctemp_dest (&hlp);
  return (c1 - c2);
}
