#include <ic_stdc.h>

void __cdecl
ic_lctemp_dest (ic_lctemp_t *h)
{
  if (h && h->updated)
    h->ptd->_ownlocale = h->ptd->_ownlocale & ~2;
}

