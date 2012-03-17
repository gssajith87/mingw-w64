#include <ic_stdc.h>

ic_tmbinfo_t * __cdecl
__ic_update_minfo (void)
{
  ic_tmbinfo_t *pmi;

  ic_thrdata_t ptd = _ic_getthrdata ();
  if ((ptd->_ownlocale & __ic_global_locale_status) != 0
      && ptd->ptlocinfo)
  {
    if (!(pmi = ptd->ptmbcinfo))
      _ic_amsg_exit (_ICRT_LOCALE_INIT_FAILED);

    return pmi;
  }

  _ic_lock (_IC_LOCK_MBCODEPAGE);
  if ((pmi = ptd->ptmbcinfo) != __ic_ptmbcinfo)
    {
      if (pmi
          && !InterlockedDecrement ((volatile LONG *) &pmi->refcount)
          && pmi != &__ic_global_mbcinfo)
	ic_free (pmi);

      pmi = ptd->ptmbcinfo = __ic_ptmbcinfo;
      InterlockedIncrement ((volatile LONG *) &pmi->refcount);
    }
  _ic_unlock (_IC_LOCK_MBCODEPAGE);

  if (!pmi)
    _ic_amsg_exit (_ICRT_LOCALE_INIT_FAILED);

  return pmi;
}

