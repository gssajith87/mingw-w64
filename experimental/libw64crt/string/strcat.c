#include <w64crt.h>
#include <w64string.h>

char *
strcat (char *d, const char *s)
{
  strcpy (d + strlen (d), s);
  return d;
}

