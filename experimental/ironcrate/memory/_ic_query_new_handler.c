#include <ic_stdc.h>

ic_new_handler_t __cdecl
_ic_query_new_handler (void)
{
  return __ic_newhandle_fct;
}

