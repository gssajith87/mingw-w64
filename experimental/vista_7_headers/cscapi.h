#ifndef _INC_CSCAPI
#define _INC_CSCAPI
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

DWORD OfflineFilesEnable(
  WINBOOL bEnable,
  BOOL *pbRebootRequired
);
DWORD OfflineFilesQueryStatus(
  WINBOOL *pbActive,
  WINBOOL *pbEnabled
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_CSCAPI*/
