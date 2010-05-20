#undef WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#ifdef IP_DEFAULT_MULTICAST_LOOP
#error WinSock1 macros leaked to WinSock2
#endif

#ifndef LPWSAEVENT
#error WinSock2 macros not present
#endif

