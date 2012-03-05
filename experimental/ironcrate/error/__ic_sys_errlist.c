#include <ic_stdc.h>

#undef _ic_sys_errlist

char ** __cdecl
__ic_sys_errlist (void)
{
  return _ic_sys_errlist;
}

