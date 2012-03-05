#include <ic_stdc.h>

#undef _ic_sys_nerr

int * __cdecl
__ic_sys_nerr (void)
{
  return &_ic_sys_nerr;
}

