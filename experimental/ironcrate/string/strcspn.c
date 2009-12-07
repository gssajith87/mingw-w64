#include <icrt.h>

size_t
strcspn (const char *s1, const char *s2)
{
  const char *d = s1;
  while (*d != 0 && strchr (s2, *d) == NULL)
    d++;
  return (size_t) (d - s1);
}

