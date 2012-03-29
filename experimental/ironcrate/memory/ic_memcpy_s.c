#include <ic_stdc.h>

/* Test memory/memcpy_s.c */

ic_errno_t __cdecl
ic_memcpy_s (void *d, size_t dn, const void *s, size_t n)
{
  if (!n)
    return 0;

  if (!d || !s)
    {
      if (d)
        ic_memset (d, 0, dn);
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return IC_EINVAL;
    }

  if (dn < n)
    {
      ic_memset (d, 0, dn);

      ic_errno = IC_ERANGE;
      IC_INV_PARAM("Invalid arguments");
      return IC_ERANGE;
    }

  ic_memcpy (d, s, n);

  return 0;
}
