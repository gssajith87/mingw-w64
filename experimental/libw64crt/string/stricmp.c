#include <w64crt.h>
#include <w64string.h>

#define TOUPPER(ch) \
  ((CH) >= 'a' && (CH) <= 'z') ? ((CH) - 'a' + 'A') : (CH))

int
stricmp (const char *s1, const char *s2)
{
  while (*s2 != 0 && TOUPPER (*s1) == TOUPPER (*s2))
    s1++, s2++;
  return (int) (TOUPPER (*s1) - TOUPPER (*s2));
}

