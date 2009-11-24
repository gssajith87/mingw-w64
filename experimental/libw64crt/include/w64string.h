#ifndef __W64STRING_H
#define __W64STRING_H

#include <w64crt_defs.h>

size_t strlen (const char *);
char *strcpy (char *, const char *);
char *strncpy (char *, const char *, size_t);
int strcmp (const char *, const char *);
int stricmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);
int strnicmp (const char *, const char *, size_t);
char *strcat (char *, const char *);
char *strncat (char *, const char *, size_t);
char *strchr (const char *, int);
char *strrchr (const char *, int);

void *memcpy (void *, const void *, size_t);

#endif

