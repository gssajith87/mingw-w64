#include <w64crt.h>
#include <w64string.h>

int
memcmp (const void *s1, const void *s2, size_t n)
{
  const char *sc1 = (const char *) s1;
  const char *sc2 = (const char *) s2;
  const char *sc2end = sc2 + n;

  while (sc2 < sc2end && *sc1 == *sc2)
    sc1++, sc2++;
  if (sc2 == sc2end)
    return 0;
  return (int) (*sc1 - *sc2);
}

