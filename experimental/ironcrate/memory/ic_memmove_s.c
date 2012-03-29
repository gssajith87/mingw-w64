#include <ic_stdc.h>

/* Testcase added at memory/memmove_s.c  */

ic_errno_t __cdecl
ic_memmove_s (void *d, size_t dn, const void *s, size_t n)
{
  if (!n)
    return 0;
  if (!d || !s)
    {
      ic_errno = IC_EINVAL;
      _ic_invalid_parameter ("!d || !s");
      return IC_EINVAL;
    }

  if (dn < n)
    {
      ic_errno = IC_ERANGE;
      _ic_invalid_parameter ("dn < n");
      return IC_ERANGE;
    }

  ic_memmove (d, s, n);

  return 0;
}
