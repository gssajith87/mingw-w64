#ifndef _INC_ATACCT
#define _INC_ATACCT
#include <windows.h>

HRESULT GetNetScheduleAccountInformation(
  LPCWSTR pwszServerName,
  DWORD ccAccount,
  WCHAR wszAccount[]
);

HRESULT SetNetScheduleAccountInformation(
  LPCWSTR pwszServerName,
  LPCWSTR pwszAccount,
  LPCWSTR pwszPassword
);

#endif /*_INC_ATACCT*/
