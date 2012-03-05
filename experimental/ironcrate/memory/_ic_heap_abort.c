#include <ic_stdc.h>

void __cdecl
_ic_heap_abort (void)
{
  _ic_amsg_exit (_ICRT_MSG_HEAP_FAILURE);
}

