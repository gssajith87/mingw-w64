#include <icrt.h>

char *
strset (char *d, int ch)
{
  size_t dl = strlen (d);
  if (dl)
    memset (d, ch, dl);
  return d;
}

