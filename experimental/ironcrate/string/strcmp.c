#include <icrt.h>

int
strcmp (const char *s1, const char *s2)
{
  while (*s2 != 0 && *s1 == *s2)
    s1++, s2++;
  return (int) ((*s1) - (*s2));
}

