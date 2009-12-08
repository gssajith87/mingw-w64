#include <icrt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/wykz6chs%28VS.71%29.aspx */

int
__iCrt_heapadd (void *mem, size_t sz)
{
  __iCrt_set_errno (ENOSYS);
  return -1;
}
