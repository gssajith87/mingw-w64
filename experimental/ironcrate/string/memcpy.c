#include <w64crt.h>
#include <w64string.h>

void *
memcpy (void *d, const void *s, size_t n)
{
  const char *sc, *se;
  char *dc;

  dc = (char *) d;
  sc = (const char *) s;
  se = sc + n;

  if (se != sc)
    {
      do {
       *dc++ = *sc++;
      } while (sc < se);
    }
  return d;
}

