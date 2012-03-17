#include <ic_stdc.h>

void __cdecl
ic_lctemp_init (ic_slocal_t *pli, ic_lctemp_t *h)
{
  ic_memset (h, 0, sizeof (ic_lctemp_t));

  if (pli)
    {
      h->li = *pli;
      return;
    }

  h->ptd = _ic_getthrdata ();
  h->li.locinfo = h->ptd->ptlocinfo;
  h->li.mbcinfo = h->ptd->ptmbcinfo;

  if (h->li.locinfo != __ic_tls_li
      && (h->ptd->_ownlocale & __ic_global_locale_status) == 0)
    h->li.locinfo = __ic_update_tlocinfo ();

  if (h->li.mbcinfo != __ic_ptmbcinfo
      && (h->ptd->_ownlocale & __ic_global_locale_status) == 0)
    h->li.mbcinfo = __ic_update_minfo ();

  if ((h->ptd->_ownlocale & 2) == 0)
    {
      h->ptd->_ownlocale |= 2;
      h->updated = 1;
    }
}

