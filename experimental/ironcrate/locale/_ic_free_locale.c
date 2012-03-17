#include <ic_stdc.h>

/* See http://msdn.microsoft.com/en-us/library/beadd31b.aspx  */

void __cdecl
_ic_free_locale (ic_slocal_t *pli)
{
  if (!pli)
    return;

  if (pli->mbcinfo != NULL
      && !InterlockedDecrement (&pli->mbcinfo->refcount)
      && pli->mbcinfo != &__ic_global_mbcinfo)
    ic_free (pli->mbcinfo);

  if (pli->locinfo)
    {
      _ic_lock (_IC_LOCK_SETLOCALE);
      __ic_release_locale_ref (pli->locinfo);

      if (pli->locinfo
	  && pli->locinfo->refcount == 0
	  && pli->locinfo != &__ic_global_locinfo)
	__ic_free_thrdlocinfo (pli->locinfo);
      _ic_unlock (_IC_LOCK_SETLOCALE);
    }

  /* Make sure that on access we produce segfault.  */
  pli->locinfo = (void *) (uintptr_t) 0xdeadbeef;
  pli->mbcinfo = (void *) (uintptr_t) 0xdeadbeef;
  ic_free (pli);
}

