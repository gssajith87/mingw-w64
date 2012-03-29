#include <ic_stdc.h>

struct ic_lconv_t * __cdecl
_ic_localeconv (void)
{
  ic_thrdata_t ptd = _ic_getthrdata ();
  ic_threadlocinfo_t *p = ptd->ptlocinfo;

  if (p != __ic_tls_li && !(ptd->_ownlocale & __ic_global_locale_status))
    __ic_update_tlocinfo ();
  return __ic_lconv;
}

