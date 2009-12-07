#include <w64crt.h>
#include <w64string.h>

size_t
strspn(const char *s1, const char *s2)
{
  const char *d = s1;
  while (*d != 0 && strchr (s2, *d) != NULL)
    d++;
  return (size_t) (d - s1);
}

