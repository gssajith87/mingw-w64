#include <ic_stdc.h>

/* Test added to memory/memmove.c  */
#if defined (__x86_64__)
__declspec(dllimport) void RtlMoveMemory (void *, const void *, size_t);
#endif

void * __cdecl
ic_memmove (void *d, const void *s, size_t n)
{
  void *r = d;
  
  if (!n)
    return r;

#if defined (__x86_64__)
  RtlMoveMemory (d, s, n);
#else
  if (d <= s || (char *) d >= ((char *) s + n))
    {
      do
	{
	  --n;
	  *(char *)d = *(char *) s;
	  d = (char *) d + 1;
	  s = (char *) s + 1;
	}
      while (n != 0);
    }
  else
    {
      d = (char *) d + n - 1;
      s = (char *) s + n - 1;

      do
	{
	  --n;
	  *(char *) d = *(char *) s;
	  d = (char *) d - 1;
	  s = (char *) s - 1;
	}
      while (n != 0);
    }
#endif
  return r;
}
