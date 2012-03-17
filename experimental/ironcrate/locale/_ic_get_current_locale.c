#include <ic_stdc.h>

ic_slocal_t * __cdecl
_ic_get_current_locale (void)
{
  ic_thrdata_t ptd = _ic_getthrdata ();
  ic_slocal_t *p;

  if ((p = ic_calloc (sizeof (ic_slocal_t), 1)) == NULL)
    {
      ic_errno = IC_ENOMEM;
      return NULL;
    }

  __ic_update_tlocinfo ();
  __ic_update_minfo ();

  p->locinfo = ptd->ptlocinfo;
  p->mbcinfo = ptd->ptmbcinfo;

  _ic_lock (_IC_LOCK_SETLOCALE);
  __ic_add_locale_ref (p->locinfo);
  _ic_unlock (_IC_LOCK_SETLOCALE);

  InterlockedIncrement (&p->mbcinfo->refcount);

  return p;
}

