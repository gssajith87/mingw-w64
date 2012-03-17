#include <ic_stdc.h>

ic_threadlocinfo_t * __cdecl
__ic_update_tlocinfo (void)
{
  ic_thrdata_t ptd = _ic_getthrdata ();
  ic_threadlocinfo_t *d = NULL, *h;

  if ((ptd->_ownlocale & __ic_global_locale_status) != 0
      && ptd->ptlocinfo)
    {
      if ((d = _ic_getthrdata ()->ptlocinfo) == NULL)
	_ic_amsg_exit (_ICRT_LOCALE_INIT_FAILED);

      return d;
    }

  _ic_lock (_IC_LOCK_SETLOCALE);

  if (__ic_tls_li)
    {
      h = ptd->ptlocinfo;

      if (h != __ic_tls_li)
	{
	  ptd->ptlocinfo = __ic_tls_li;
	  __ic_add_locale_ref (__ic_tls_li);
	  if (h)
	    __ic_release_locale_ref (h);

	  if (h && h->refcount == 0 && h != &__ic_global_locinfo)
	    __ic_free_thrdlocinfo (h);

	}
      d = __ic_tls_li;
    }

  _ic_unlock (_IC_LOCK_SETLOCALE);

  if (!d)
    _ic_amsg_exit (_ICRT_LOCALE_INIT_FAILED);

  return d;
}

