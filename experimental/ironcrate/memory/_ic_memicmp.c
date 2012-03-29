#include <ic_stdc.h>

/* Test: memory/memicmp.c  */

int __cdecl
_ic_memicmp (const void *s1, const void *s2, size_t n)
{
  if (__ic_locale_changed == 0)
    {
      if ((!s1 && n != 0) || (!s2 && n != 0))
	{
	  ic_errno = IC_EINVAL;
	  IC_INV_PARAM("Invalid arguments");
	  return 0x7fffffff;
	}

      return __ic_memicmp_a (s1, s2, n);
    }
  return _ic_memicmp_l (s1, s2, n, NULL);
}

