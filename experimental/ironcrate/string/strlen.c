#include <w64crt.h>
#include <w64string.h>

/* Returns the amount of characters in a string without terminating zero.  */
size_t
strlen (const char *s)
{
  const char *p = s;
  /* We don't check here for NULL pointers.  */
  for (;*p != 0; p++)
    ;
  return (size_t) (p - s);
}

