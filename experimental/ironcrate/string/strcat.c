#include <icrt.h>

char *
strcat (char *d, const char *s)
{
  strcpy (d + strlen (d), s);
  return d;
}

