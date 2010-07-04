#ifndef _INC_VSBACKUP
#define _INC_VSBACKUP
#include <windows.h>

HRESULT ShouldBlockRevert(
  LPCWSTR wszVolumeName,
  WINBOOL *pbBlock
);

#endif /*_INC_VSBACKUP*/
