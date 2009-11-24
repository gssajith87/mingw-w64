#include <w64crt.h>
#include <w64string.h>

char *
strrchr (const char *s, int ch)
{
  const char *sc = s + strlen (s);
  if (!ch)
    return (char *) sc;
  while (sc > s)
   {
     --sc;
     if (*sc == ch)
       return (char *) sc;
   }
  return NULL;
}

