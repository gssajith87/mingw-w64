#ifndef _INC_WDSCLIENTAPI
#define _INC_WDSCLIENTAPI
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

#ifndef WDSTCIAPI
#define WDSTCIAPI WINAPI
#endif

/* CALLBACKS

VOID CALLBACK PFN_WdsTransportClientReceiveContents(
  HANDLE hSessionKey,
  PVOID pCallerData,
  PVOID pMetadata,
  ULONG ulSize,
  PULARGE_INTEGER pContentOffset
);

VOID CALLBACK PFN_WdsTransportClientReceiveMetadata(
  __in  HANDLE hSessionKey,
  __in  PVOID pCallerData,
  __in  PVOID pMetadata,
  __in  ULONG ulSize
);

VOID CALLBACK PFN_WdsTransportClientSessionComplete(
  __in  HANDLE hSessionKey,
  __in  PVOID pCallerData,
  __in  DWORD dwError
);

VOID CALLBACK PFN_WdsTransportClientSessionStart(
  __in  HANDLE hSessionKey,
  __in  PVOID pCallerData,
  __in  PULARGE_INTEGER FileSize
);

VOID CALLBACK PFN_WdsTransportClientSessionStartEx(
  __in  HANDLE hSessionKey,
  __in  PVOID pCallerData,
  __in  PTRANSPORTCLIENT_SESSION_INFO Info
);

*/

DWORD WDSTCIAPI WdsTransportClientStartSession(
  HANDLE hSessionKey
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WDSCLIENTAPI*/
