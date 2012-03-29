#include <ic_stdc.h>

wchar_t * __cdecl
ic_wmemchr (const wchar_t *s, wchar_t ch, size_t n)
{
  for (; n > 0; s++, n--)
    {
      if (*s == ch)
	return (wchar_t *) s;
    }

  return 0;
}
