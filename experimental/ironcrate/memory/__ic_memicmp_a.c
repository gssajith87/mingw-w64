#include <ic_stdc.h>

int __cdecl
__ic_memicmp_a (const void *s1, const void *s2, size_t n)
{
  int c1 = 0, c2 = 0;

  while (n != 0)
    {
      unsigned char us1, us2;
      --n;
      us1 = *((unsigned char *) s1);
      us2 = *((unsigned char *) s2);
      if (us1 == us2
          || ((c1 = ((us1 >= 'A' && us1 <= 'Z') ? (us1 | 0x20) : us1))
              == ((c2 = ((us2 >= 'A' && us2 <= 'Z') ? (us2 | 0x20) : us2)))
	{
	  s1 = (char *) s1 + 1;
	  s2 = (char *) s2 + 1;
	}
      else
	break;
    }
  return (c1 - c2);
}

