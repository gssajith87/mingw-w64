#include <icrt.h>

int
strncmp (const char *s1, const char *s2, size_t n)
{
  const char *s2end = s2 + n;
  while (s2 < s2end && *s2 != 0 && *s1 == *s2)
    s1++, s2++;
  if (s2end == s2)
    return 0;
  return (int) ((*s1) - (*s2));
}

