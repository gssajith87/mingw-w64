#ifndef _INC_WDSBP
#define _INC_WDSBP
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

#ifndef WDSBPAPI
#define WDSBPAPI WINAPI
#endif

/* Wdsbp.dll is missing an implib because Vista clients don't have the dll to generate it from */

HRESULT WDSBPAPI WdsBpAddOption(
  HANDLE hHandle,
  ULONG uOption,
  ULONG uValueLen,
  PVOID pValue
);

HRESULT WDSBPAPI WdsBpCloseHandle(
  HANDLE hHandle
);

HRESULT WDSBPAPI WdsBpGetOptionBuffer(
  HANDLE hHandle,
  ULONG uBufferLen,
  PVOID pBuffer,
  PULONG puBytes
);

#define WDSBP_PK_TYPE_DHCP 1
#define WDSBP_PK_TYPE_WDSNBP 2
#define WDSBP_PK_TYPE_BCD 4

HRESULT WDSBPAPI WdsBpInitialize(
  BYTE bPacketType,
  HANDLE *phHandle
);

HRESULT WDSBPAPI WdsBpParseInitialize(
  PVOID pPacket,
  ULONG uPacketLen,
  PBYTE pbPacketType,
  HANDLE *phHandle
);

HRESULT WDSBPAPI WdsBpQueryOption(
  HANDLE hHandle,
  ULONG uOption,
  ULONG uValueLen,
  PVOID pValue,
  PULONG puBytes
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WDSBP*/
