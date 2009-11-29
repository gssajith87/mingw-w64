#include <w64crt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/wykz6chs%28VS.71%29.aspx */

int
__w64crt_heapadd (void *mem, size_t sz)
{
  __w64crt_set_errno (ENOSYS);
  return -1;
}
