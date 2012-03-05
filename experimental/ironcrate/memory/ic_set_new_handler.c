#include <ic_stdc.h>

ic_new_handler_t __cdecl
ic_set_new_handler (ic_new_handler_t p /* unused */)
{
  _ic_set_new_handler (NULL);

  return NULL;
}

