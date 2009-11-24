#ifndef __W64STRING_H
#define __W64STRING_H

#include <w64crt_defs.h>

size_t strlen (const char *);
char *strcpy (char *, const char *);
char *strncpy (char *, const char *, size_t);
int strcmp (const char *, const char *);

void *memcpy (void *, const void *, size_t);

#endif

