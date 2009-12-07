#include <icrt.h>

void *
memccpy (void *d, const void *s, int end, size_t n)
{
  const char *sc, *se;
  char *dc, *ret = NULL;

  dc = (char *) d;
  sc = (const char *) s;
  se = sc + n;
  if (se != sc)
    {
      do {
        *dc++ = *sc++;
        if (sc[-1] == end)
	  {
	    ret = dc;
            break;
	  }
      } while (sc < se);
    }
  return ret;
}

