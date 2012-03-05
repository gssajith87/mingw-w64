#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_get_doserrno (unsigned long *pderr)
{
  if (!perr)
    {
      IC_INV_PARAM("Invalid arguments");
      return IC_EINVAL;
    }

  *pderr = _ic_doserrno;
  return 0;
}

