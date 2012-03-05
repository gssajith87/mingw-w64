#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_set_errno (int err)
{
  ic_thrdata_t ptd;

  if (!(ptd = _ic_get_internal_thrdata ()))
    return IC_ENOMEM;

  ic_errno = err;
  return 0;
}

