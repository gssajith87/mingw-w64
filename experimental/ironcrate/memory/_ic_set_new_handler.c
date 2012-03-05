#include <ic_stdc.h>

ic_new_handler_t __cdecl
_ic_set_new_handler (ic_new_handler_t p)
{
  ic_new_handler_t r;

  _ic_lock (_IC_LOCK_HEAP);
  r = __ic_newhandle_fct;
  __ic_newhandle_fct = p;
  _ic_unlock (_IC_LOCK_HEAP);

  return r;
}

