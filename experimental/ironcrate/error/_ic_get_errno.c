#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_get_errno (int *perr)
{
  if (!perr)
    {
      IC_INV_PARAM("Invalid arguments");
      return IC_EINVAL;
    }

  *perr = ic_errno;
  return 0;
}

