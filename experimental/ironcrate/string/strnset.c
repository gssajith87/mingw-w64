#include <w64crt.h>
#include <w64string.h>

char *
strnset (char *d, int ch, size_t n)
{
  size_t dl = strlen (d);
  if (dl < n)
    n = dl;
  if (n)
    memset (d, ch, n);
  return d;
}

