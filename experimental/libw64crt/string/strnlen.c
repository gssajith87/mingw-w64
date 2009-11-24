#include <w64crt.h>
#include <w64string.h>

/* Returns the amount of characters in a string without terminating zero.  */
size_t
strnlen (const char *s, size_t n)
{
  const char *p = s;
  /* We don't check here for NULL pointers.  */
  for (;*p != 0 && n > 0; p++, n--)
    ;
  return (size_t) (p - s);
}

