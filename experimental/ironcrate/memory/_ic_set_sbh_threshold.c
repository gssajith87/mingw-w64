#include <ic_stdc.h>

int __cdecl
_ic_set_sbh_threshold (size_t threshold)
{
  if (!_ic_theheap)
    return 0;
#ifndef __x86_64__
  return 1;
#else
  ic_errno = IC_EINVAL;
  return 0;
#endif
}

