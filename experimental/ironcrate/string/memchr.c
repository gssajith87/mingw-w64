#include <icrt.h>

void *
memchr (const void *s, int ch, size_t n)
{
  const char *sc = (const char *) s;

  if (!n)
    return NULL;

  do
    {
      if (*sc == ch)
        return (char *) sc;
      ++sc;
    }
  while (--n > 0);

  return NULL;
}

