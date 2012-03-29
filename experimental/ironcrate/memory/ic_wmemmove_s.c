#include <ic_stdc.h>

ic_errno_t __cdecl
ic_wmemmove_s (wchar_t *d, rsize_t dn, const wchar_t *s, rsize_t n)
{
  return ic_memmove_s (d, dn * sizeof(wchar_t), s, n * sizeof(wchar_t));
}

