#include <ic_stdc.h>

wchar_t * __cdecl
ic_wmemset (wchar_t *d, wchar_t ch, size_t n)
{
  wchar_t *p = d;

  for (; n > 0; n--)
    *p++ = ch;

  return d;
}

