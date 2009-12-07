#ifndef __W64STRING_H
#define __W64STRING_H

#include <w64crt_defs.h>

size_t strlen (const char *);
size_t strnlen (const char *, size_t);
char *strcpy (char *, const char *);
char *strncpy (char *, const char *, size_t);
int strcmp (const char *, const char *);
int stricmp (const char *, const char *);
int strcmpi (const char *, const char *);
int strncmp (const char *, const char *, size_t);
int strnicmp (const char *, const char *, size_t);
char *strcat (char *, const char *);
char *strncat (char *, const char *, size_t);
char *strchr (const char *, int);
char *strrchr (const char *, int);
char *strnset (char *, int, size_t);
char *strset (char *, int);
char *strlwr (char *);
char *strupr (char *);
char *strrev (char *);
char *strstr (const char *, const char *);
char *strpbrk(const char *, const char *);
size_t strspn(const char *, const char *);
size_t strcspn(const char *, const char *);

void *memcpy (void *, const void *, size_t);
void *memccpy (void *, const void *, int, size_t);
void *memset (void *, int, size_t);
void *memchr (const void *, int, size_t);
void *memmove (void *, const void *, size_t);
int memcmp (const void *, const void *, size_t);
int memicmp (const void *s1, const void *s2, size_t n);

#endif

