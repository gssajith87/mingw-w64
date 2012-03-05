#include <ic_stdc.h>

int __cdecl
_ic_callnewh (size_t sz)
{
  return (__ic_newhandle_fct
          && (*__ic_newhandle_fct) (sz) != 0);
}

