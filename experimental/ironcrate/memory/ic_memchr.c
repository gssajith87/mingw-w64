#include <ic_stdc.h>

/* Test memory/memchr.c  */

void * __cdecl
ic_memchr (const void *s, int ch, size_t n)
{
  const unsigned char *q = (const unsigned char *) s;
  while (n != 0 && *q != (unsigned char) ch)
    {
      ++q;
      --n;
    }

  return (!n ? NULL : (void *) q);
}
