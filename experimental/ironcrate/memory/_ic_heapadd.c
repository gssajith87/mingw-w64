#include <ic_stdc.h>

int __cdecl
_ic_heapadd (void *p, size_t sz)
{
  ic_errno = IC_ENOSYS;
  return -1;
}

