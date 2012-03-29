#include <ic_stdc.h>

wchar_t * __cdecl
ic_wmemcpy (wchar_t *d, const wchar_t *s, size_t n)
{
  return (wchar_t *) ic_memcpy (d, s, n * sizeof (wchar_t));
}

