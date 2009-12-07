#include <icrt.h>

char *
strupr (char *d)
{
  char *p = d;
  while (*p != 0)
    {
      if (*p >= 'a' && *p <= 'z')
        *p = (*p) - 'a' + 'A';
      ++p;
    }
  return d;
}

