#include <ic_stdc.h>

/* Test memory/memcmp.c */

#if defined (__x86_64__)
__declspec(dllimport) size_t RtlCompareMemory (const void *, const void *, size_t);
#endif

int __cdecl
ic_memcmp (const void *s1, const void *s2, size_t n)
{
  size_t l;

  if (!n)
    return 0;

#if defined (__x86_64__)
  if ((l = RtlCompareMemory (s1, s2, n)) == n)
    return 0;

  s1 = (char *) s1 + l;
  s2 = (char *) s2 + l;
#else 
  for (l = 1; l < n && *(char *) s1 == *(char *) s2; l++)
    {
      s1 = (char *) s1 + 1;
      s2 = (char *) s2 + 1;
    }
#endif
  return (*((unsigned char *) s1) - *((unsigned char *) s2));
}
