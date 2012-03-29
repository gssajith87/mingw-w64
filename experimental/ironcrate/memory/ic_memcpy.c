#include <ic_stdc.h>

/* Test memory/memcpy.c  */

void * __cdecl
ic_memcpy (void *d, const void *s, size_t n)
{
  void *r = d;

  if (!n)
    return r;
  do
    {
      --n;
      *(char *) d = *(char *) s;
      d = (char *) d + 1;
      s = (char *) s + 1;
    }
  while (n != 0);

  return r;
}
