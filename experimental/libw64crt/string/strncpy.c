#include <w64crt.h>
#include <w64string.h>

char *
strncpy (char *d, const char *s, size_t n)
{
  size_t sl = strlen (s);

  if (!n)
    return d;
  if (sl > (n - 1))
    sl = n - 1;
  memcpy (d, s, sl);
  while (sl < n)
    d[sl++] = 0;
  return d;
}

