#include <ic_stdc.h>

/* Function assumes that at pointer P minus two-times pointer-size is
   a magic-marker with 4-bytes size.  If marker is 0xdddd, then the
   address P minus two-times pointer-size is used to call ic_free.
   See also _ic_markalloca.  */

void __cdecl
_ic_freea (void *p)
{
  if (!p)
    return;

  p = (char *) p - sizeof (void *) * 2;

  if (((unsigned int *) p)[0] == 0xdddd)
    ic_free (p);
}

