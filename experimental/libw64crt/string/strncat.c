#include <w64crt.h>
#include <w64string.h>

char *
strncat (char *d, const char *s, size_t n)
{
  size_t sl = strlen (s);
  size_t dl = strlen (d);
  if (!n || !sl)
    return d;
  /* Remark that string gets always terminating zero, so n + 1 is possible
     written, too.  */
  if (sl > n)
   sl = n;
  memcpy (d + dl, s, sl);
  d[dl + sl] = 0;
  return d;
}
