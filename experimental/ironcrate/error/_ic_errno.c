#include <ic_stdc.h>

int * __cdecl
_ic_errno (void)
{
  static int def_ecode = IC_ENOMEM;
  ic_thrdata_t ptd;

  if (!(ptd = _ic_get_internal_thrdata ()))
    return &def_ecode;

  return &ptd->_terrno;
}

