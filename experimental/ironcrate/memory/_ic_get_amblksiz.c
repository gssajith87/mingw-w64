#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_get_amblksiz (size_t *sz)
{
  if (!sz || !_ic_theheap)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("sz has invalid value");
      return IC_EINVAL;
    }

  *sz =  _ic_amblksiz;

  return 0;
}

