#ifndef _INC_NETIOAPI
#define _INC_NETIOAPI
#if (_WIN32_WINNT >= 0x0600)

#ifdef __IPHLPAPI_H__
#define NETIO_STATUS DWORD
#define NETIOAPI_API_ WINAPI
#else
#define NETIO_STATUS NTSTATUS
#define NETIOAPI_API_ NTAPI
#endif

#define NETIOAPI_API NETIO_STATUS NETIOAPI_API_


NETIOAPI_API CancelMibChangeNotify2(
  __in  HANDLE NotificationHandle
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NETIOAPI*/
