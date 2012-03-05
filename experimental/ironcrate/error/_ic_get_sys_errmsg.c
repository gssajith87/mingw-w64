#include <ic_stdc.h>

#undef _ic_sys_nerr
#undef _ic_sys_errlist

const char * __cdecl
_ic_get_sys_errmsg (int err);
{
  if (err < 0 || err > _ic_sys_nerr)
    err = _ic_sys_nerr;
  return _ic_sys_errlist[err];
}

