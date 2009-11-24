#include <w64crt.h>
#include <w64string.h>

char *
strcpy (char *d, const char *s)
{
  if (s != d)
    memcpy (d, s, strlen (s) + 1);
  return s;
}

