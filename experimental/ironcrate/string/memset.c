#include <w64crt.h>
#include <w64string.h>

void *
memset (void *d, int ch, size_t n)
{
  char *dc;

  dc = (char *) d;

  while (n > 0)
    {
      *dc++ = (char) ch;
      --n;
    }

  return d;
}

