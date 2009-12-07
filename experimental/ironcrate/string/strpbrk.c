#include <w64crt.h>
#include <w64string.h>

char *strpbrk(const char *s1, const char *s2)
{
  while (*s1 != 0)
    {
      char *r = strchr (s2, *s1);
      if (r)
        return r;
      ++s1;
    }
  return NULL;
}

