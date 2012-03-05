#include <ic_stdc.h>

unsigned long * __cdecl
__ic_doserrno (void)
{
  static unsigned long def_wcode = ERROR_NOT_ENOUGH_MEMORY;
  ic_thrdata_t ptd;

  if (!(ptd = _ic_get_internal_thrdata ()))
    return &def_wcode;
  return &ptd->_tdoserrno;
}

