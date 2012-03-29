#include <ic_stdc.h>

void * __cdecl
_ic_memccpy (void *d, const void *s, int ch, size_t n)
{
  const char *cs = (const char *) s;
  char *r = (char *) d;

  while (n)
    {
      ++r;
      ++cs;
      r[-1] = cs[-1];
      if (r[-1] == (char) ch)
        break;
      --n;
    }

  return (!n ? NULL : r);
}
