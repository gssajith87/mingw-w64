#include <ic_stdc.h>

int __cdecl
ic_wmemcmp (const wchar_t *s1, const wchar_t *s2, size_t n)
{
  for (; n > 0; s1++, s2++, --n)
    {
      if (*s1 != *s2)
	return (*s1 < *s2 ? -1 : 1);
    }

  return 0;
}

