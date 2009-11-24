#include <w64crt.h>
#include <w64string.h>

char *
strchr (const char *s, int ch)
{
  if (!ch)
    return (char *) &s[strlen (s)];
  while (*s != 0)
   {
     if (*s == ch)
       return (char *) s;
     ++s;
   }
  return NULL;
}

