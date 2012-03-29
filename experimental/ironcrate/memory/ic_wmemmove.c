#include <ic_stdc.h>

wchar_t * __cdecl
ic_wmemmove (wchar_t *d, const wchar_t *d, size_t n)
{
  return (wchar_t *) ic_memmove (d, s, n * sizeof(wchar_t));
}
