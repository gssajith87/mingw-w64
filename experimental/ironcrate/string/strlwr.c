#include <icrt.h>

char *
strlwr (char *d)
{
  char *p = d;

  while (*p != 0)
   {
     if (*p >= 'A' && *p <= 'Z')
       *p = (*p) - 'A' + 'a';
     ++p;
   }
  return d;
}

