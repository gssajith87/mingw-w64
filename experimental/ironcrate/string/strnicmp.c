#include <icrt.h>

#define TOUPPER(CH) \
  (((CH) >= 'a' && (CH) <= 'z') ? ((CH) - 'a' + 'A') : (CH))

int
strnicmp (const char *s1, const char *s2, size_t n)
{
  const char *s2end = s2 + n;

  while (s2 < s2end && *s2 != 0 && TOUPPER (*s1) == TOUPPER (*s2))
    s1++, s2++;
  if (s2end == s2)
    return 0;
  return (int) (TOUPPER (*s1) - TOUPPER (*s2));
}

