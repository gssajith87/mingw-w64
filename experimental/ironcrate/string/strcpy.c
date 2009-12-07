#include <icrt.h>

char *
strcpy (char *d, const char *s)
{
  memcpy (d, s, strlen (s) + 1);
  return d;
}

