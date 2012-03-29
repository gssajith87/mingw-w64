#include <ic_stdc.h>

/* Testcase at memory/memset.c  */

#if defined (__x86_64__)
__declspec(dllimport) void RtlFillMemory (void *, size_t, char);
#endif

void * __cdecl
ic_memset (void *d, int ch, size_t n)
{
  void *r = d;

#if defined (__x86_64__)
  RtlFillMemory (d, n, (char) ch);
#else
  if (!n)
    return r;
  do
    {
      *(char *) d = (char) ch;
      d = (char *) d + 1;
      --n;
    }
  while (n != 0);
#endif
  return r;
}
