#include <ic_stdc.h>

void __cdecl
_ic_mapwinerr (unsigned long werr)
{
  _ic_doserrno = werr;
  ic_errno = _ic_get_errno_from_winerr (werr);
}

