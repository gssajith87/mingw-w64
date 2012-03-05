#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_set_doserrno (unsigned long derr)
{
  ic_thrdata_t ptd;

  if (!(ptd = _ic_get_internal_thrdata ()))
    return IC_ENOMEM;
  _ic_doserrno = derr;
  return 0;
}

