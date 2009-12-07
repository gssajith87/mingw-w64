#include <icrt.h>

void *
memmove (void *d, const void *s, size_t n)
{
  char *dc = (char *) d;
  const char *sc = (const char *) s;
  if (dc == sc || (dc < sc && (dc + n) <= sc))
    return memcpy (d, s, n);
  else if (dc > sc && (sc + n) <= dc)
    return memcpy (d, s, n);
  sc += n;
  dc += n;
  while (n > 0)
   {
     --sc, --dc;
     *dc = *sc;
     --n;
   }
  return d;
}

