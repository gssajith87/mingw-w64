#include <ic_stdc.h>

ic_errno_t __cdecl
_ic_set_amblksiz (size_t sz)
{
  if (!sz || sz > 0xffffffffU || !_ic_theheap)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("sz has invalid value");
      return IC_EINVAL;
    }

   _ic_amblksiz = (unsigned int) sz;

  return 0;
}

