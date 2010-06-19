#ifndef _INC_NDHELPER
#define _INC_NDHELPER
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef LPVOID DRMHSESSION;

HRESULT WINAPI DRMCreateClientSession(
  DRMCALLBACK pfnCallback,
  UINT uCallbackVersion,
  PWSTR wszGroupIDProviderType,
  PWSTR wszGroupID,
  DRMHSESSION *phClient
);

HRESULT WINAPI DRMAcquireIssuanceLicenseTemplate(
  DRMHSESSION hClient,
  UINT uFlags,
  VOID *pvReserved,
  UINT cReserved,
  PWSTR *pwszReserved,
  PWSTR wszURL,
  VOID *pvContext
);

HRESULT DRMIsWindowProtected(
  HWND hwnd,
  WINBOOL *pfProtected
);

HRESULT DRMRegisterProtectedWindow(
  DRMENVHANDLE hEnv,
  HWND hwnd
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NDHELPER*/
