#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock.h>

#ifndef IP_DEFAULT_MULTICAST_LOOP
#error WinSock1 macros not present
#endif

#ifdef LPWSAEVENT
#error WinSock2 macros leaked to WinSock1
#endif

