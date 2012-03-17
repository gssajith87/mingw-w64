#include <ic_stdc.h>

/* See http://msdn.microsoft.com/en-us/library/26c0tb7x%28VS.80%29.aspx for some details.  */

int __cdecl
_ic_configthreadlocale (int type)
{
  ic_thrdata_t ptd = _ic_getthrdata ();
  int r = (ptd->_ownlocale & 2) == 0 ? IC_NO_TL : IC_TL;

  switch (type)
    {
    case -1 :
      __ic_global_locale_status = -1;
      return r;
    case 0 :
      return r;
    case IC_TL:
      ptd->_ownlocale = ptd->_ownlocale | 2;
      return r;
    case IC_NO_TL:
      ptd->_ownlocale = ptd->_ownlocale & ~2;
      return r;
    default:
      break;
    }

  ic_errno = IC_EINVAL;
  IC_INV_PARAM("Invalid arguments");
  return -1;
}

