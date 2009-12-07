#include <w64crt.h>
#include <w64string.h>

char *
strrev (char *d)
{
  size_t dl = strlen (d);
  char *l, *r;

  if (!dl)
    return d;
  l = d;
  r = d + dl -1;
  while (l < r)
    {
      l[0]^=r[0]^=l[0]^=r[0];
      l++, --r;
    }
  return d;
}

