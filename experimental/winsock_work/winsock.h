/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

#include <_timeval.h>
#include <inaddr.h>
#include <_ws_helpers/_bsd_types.h>
#include <_ws_helpers/_socket_types.h>
#include <_ws_helpers/_fd_types.h>
#include <_ws_helpers/_ip_types.h>
#include <_ws_helpers/_ip_mreq1.h>
#include <_ws_helpers/_wsadata.h>
#include <_ws_helpers/_ws_ioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

  extern int WINAPI __WSAFDIsSet(SOCKET,fd_set *);

#ifdef __cplusplus
}
#endif

#define IPPROTO_IP 0
#define IPPROTO_ICMP 1
#define IPPROTO_IGMP 2
#define IPPROTO_GGP 3
#define IPPROTO_TCP 6
#define IPPROTO_PUP 12
#define IPPROTO_UDP 17
#define IPPROTO_IDP 22
#define IPPROTO_ND 77

#define IPPROTO_RAW 255
#define IPPROTO_MAX 256

#define IPPORT_ECHO 7
#define IPPORT_DISCARD 9
#define IPPORT_SYSTAT 11
#define IPPORT_DAYTIME 13
#define IPPORT_NETSTAT 15
#define IPPORT_FTP 21
#define IPPORT_TELNET 23
#define IPPORT_SMTP 25
#define IPPORT_TIMESERVER 37
#define IPPORT_NAMESERVER 42
#define IPPORT_WHOIS 43
#define IPPORT_MTP 57

#define IPPORT_TFTP 69
#define IPPORT_RJE 77
#define IPPORT_FINGER 79
#define IPPORT_TTYLINK 87
#define IPPORT_SUPDUP 95

#define IPPORT_EXECSERVER 512
#define IPPORT_LOGINSERVER 513
#define IPPORT_CMDSERVER 514
#define IPPORT_EFSSERVER 520

#define IPPORT_BIFFUDP 512
#define IPPORT_WHOSERVER 513
#define IPPORT_ROUTESERVER 520

#define IPPORT_RESERVED 1024

#define IMPLINK_IP 155
#define IMPLINK_LOWEXPER 156
#define IMPLINK_HIGHEXPER 158


#define IN_CLASSA(i) (((long)(i) & 0x80000000)==0)
#define IN_CLASSA_NET 0xff000000
#define IN_CLASSA_NSHIFT 24
#define IN_CLASSA_HOST 0x00ffffff
#define IN_CLASSA_MAX 128

#define IN_CLASSB(i) (((long)(i) & 0xc0000000)==0x80000000)
#define IN_CLASSB_NET 0xffff0000
#define IN_CLASSB_NSHIFT 16
#define IN_CLASSB_HOST 0x0000ffff
#define IN_CLASSB_MAX 65536

#define IN_CLASSC(i) (((long)(i) & 0xe0000000)==0xc0000000)
#define IN_CLASSC_NET 0xffffff00
#define IN_CLASSC_NSHIFT 8
#define IN_CLASSC_HOST 0x000000ff

#define INADDR_ANY (u_long)0x00000000
#define INADDR_LOOPBACK 0x7f000001
#define INADDR_BROADCAST (u_long)0xffffffff
#define INADDR_NONE 0xffffffff


#define IP_OPTIONS 1
#define IP_MULTICAST_IF 2
#define IP_MULTICAST_TTL 3
#define IP_MULTICAST_LOOP 4
#define IP_ADD_MEMBERSHIP 5
#define IP_DROP_MEMBERSHIP 6
#define IP_TTL 7
#define IP_TOS 8
#define IP_DONTFRAGMENT 9

#define IP_DEFAULT_MULTICAST_TTL 1
#define IP_DEFAULT_MULTICAST_LOOP 1
#define IP_MAX_MEMBERSHIPS 20

#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_RDM 4
#define SOCK_SEQPACKET 5

#define SO_DEBUG 0x0001
#define SO_ACCEPTCONN 0x0002
#define SO_REUSEADDR 0x0004
#define SO_KEEPALIVE 0x0008
#define SO_DONTROUTE 0x0010
#define SO_BROADCAST 0x0020
#define SO_USELOOPBACK 0x0040
#define SO_LINGER 0x0080
#define SO_OOBINLINE 0x0100

#define SO_DONTLINGER (u_int)(~SO_LINGER)

#define SO_SNDBUF 0x1001
#define SO_RCVBUF 0x1002
#define SO_SNDLOWAT 0x1003
#define SO_RCVLOWAT 0x1004
#define SO_SNDTIMEO 0x1005
#define SO_RCVTIMEO 0x1006
#define SO_ERROR 0x1007
#define SO_TYPE 0x1008

#define TCP_NODELAY 0x0001

#define AF_UNSPEC 0
#define AF_UNIX 1
#define AF_INET 2
#define AF_IMPLINK 3
#define AF_PUP 4
#define AF_CHAOS 5
#define AF_IPX 6
#define AF_NS 6
#define AF_ISO 7
#define AF_OSI AF_ISO
#define AF_ECMA 8
#define AF_DATAKIT 9
#define AF_CCITT 10
#define AF_SNA 11
#define AF_DECnet 12
#define AF_DLI 13
#define AF_LAT 14
#define AF_HYLINK 15
#define AF_APPLETALK 16
#define AF_NETBIOS 17
#define AF_VOICEVIEW 18
#define AF_FIREFOX 19
#define AF_UNKNOWN1 20
#define AF_BAN 21

#define AF_MAX 22

#define PF_UNSPEC AF_UNSPEC
#define PF_UNIX AF_UNIX
#define PF_INET AF_INET
#define PF_IMPLINK AF_IMPLINK
#define PF_PUP AF_PUP
#define PF_CHAOS AF_CHAOS
#define PF_NS AF_NS
#define PF_IPX AF_IPX
#define PF_ISO AF_ISO
#define PF_OSI AF_OSI
#define PF_ECMA AF_ECMA
#define PF_DATAKIT AF_DATAKIT
#define PF_CCITT AF_CCITT
#define PF_SNA AF_SNA
#define PF_DECnet AF_DECnet
#define PF_DLI AF_DLI
#define PF_LAT AF_LAT
#define PF_HYLINK AF_HYLINK
#define PF_APPLETALK AF_APPLETALK
#define PF_VOICEVIEW AF_VOICEVIEW
#define PF_FIREFOX AF_FIREFOX
#define PF_UNKNOWN1 AF_UNKNOWN1
#define PF_BAN AF_BAN

#define PF_MAX AF_MAX

#define SOL_SOCKET 0xffff

#define SOMAXCONN 5

#define MSG_OOB 0x1
#define MSG_PEEK 0x2
#define MSG_DONTROUTE 0x4

#define MSG_MAXIOVLEN 16

#define MSG_PARTIAL 0x8000

#define MAXGETHOSTSTRUCT 1024


#include <_ws_helpers/_wsa_errnos.h>

#ifdef __cplusplus
extern "C" {
#endif

  SOCKET WINAPI accept(SOCKET s,struct sockaddr *addr,int *addrlen);
  int WINAPI bind(SOCKET s,const struct sockaddr *addr,int namelen);
  int WINAPI closesocket(SOCKET s);
  int WINAPI connect(SOCKET s,const struct sockaddr *name,int namelen);
  int WINAPI ioctlsocket(SOCKET s,long cmd,u_long *argp);
  int WINAPI getpeername(SOCKET s,struct sockaddr *name,int *namelen);
  int WINAPI getsockname(SOCKET s,struct sockaddr *name,int *namelen);
  int WINAPI getsockopt(SOCKET s,int level,int optname,char *optval,int *optlen);
  u_long WINAPI htonl(u_long hostlong);
  u_short WINAPI htons(u_short hostshort);
  unsigned long WINAPI inet_addr(const char *cp);
  char *WINAPI inet_ntoa(struct in_addr in);
  int WINAPI listen(SOCKET s,int backlog);
  u_long WINAPI ntohl(u_long netlong);
  u_short WINAPI ntohs(u_short netshort);
  int WINAPI recv(SOCKET s,char *buf,int len,int flags);
  int WINAPI recvfrom(SOCKET s,char *buf,int len,int flags,struct sockaddr *from,int *fromlen);
  int WINAPI select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,const struct timeval *timeout);
  int WINAPI send(SOCKET s,const char *buf,int len,int flags);
  int WINAPI sendto(SOCKET s,const char *buf,int len,int flags,const struct sockaddr *to,int tolen);
  int WINAPI setsockopt(SOCKET s,int level,int optname,const char *optval,int optlen);
  int WINAPI shutdown(SOCKET s,int how);
  SOCKET WINAPI socket(int af,int type,int protocol);
  struct hostent *WINAPI gethostbyaddr(const char *addr,int len,int type);
  struct hostent *WINAPI gethostbyname(const char *name);
  int WINAPI gethostname(char *name,int namelen);
  struct servent *WINAPI getservbyport(int port,const char *proto);
  struct servent *WINAPI getservbyname(const char *name,const char *proto);
  struct protoent *WINAPI getprotobynumber(int proto);
  struct protoent *WINAPI getprotobyname(const char *name);
  int WINAPI WSAStartup(WORD wVersionRequired,LPWSADATA lpWSAData);
  int WINAPI WSACleanup(void);
  void WINAPI WSASetLastError(int iError);
  int WINAPI WSAGetLastError(void);
  WINBOOL WINAPI WSAIsBlocking(void);
  int WINAPI WSAUnhookBlockingHook(void);
  FARPROC WINAPI WSASetBlockingHook(FARPROC lpBlockFunc);
  int WINAPI WSACancelBlockingCall(void);
  HANDLE WINAPI WSAAsyncGetServByName(HWND hWnd,u_int wMsg,const char *name,const char *proto,char *buf,int buflen);
  HANDLE WINAPI WSAAsyncGetServByPort(HWND hWnd,u_int wMsg,int port,const char *proto,char *buf,int buflen);
  HANDLE WINAPI WSAAsyncGetProtoByName(HWND hWnd,u_int wMsg,const char *name,char *buf,int buflen);
  HANDLE WINAPI WSAAsyncGetProtoByNumber(HWND hWnd,u_int wMsg,int number,char *buf,int buflen);
  HANDLE WINAPI WSAAsyncGetHostByName(HWND hWnd,u_int wMsg,const char *name,char *buf,int buflen);
  HANDLE WINAPI WSAAsyncGetHostByAddr(HWND hWnd,u_int wMsg,const char *addr,int len,int type,char *buf,int buflen);
  int WINAPI WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
  int WINAPI WSAAsyncSelect(SOCKET s,HWND hWnd,u_int wMsg,long lEvent);

#ifdef __cplusplus
}
#endif

#include <_ws_helpers/_mswsock_1.h>

#define WSAMAKEASYNCREPLY(buflen,error) MAKELONG(buflen,error)
#define WSAMAKESELECTREPLY(event,error) MAKELONG(event,error)
#define WSAGETASYNCBUFLEN(lParam) LOWORD(lParam)
#define WSAGETASYNCERROR(lParam) HIWORD(lParam)
#define WSAGETSELECTEVENT(lParam) LOWORD(lParam)
#define WSAGETSELECTERROR(lParam) HIWORD(lParam)

#ifdef IPV6STRICT
#error WINSOCK2 required.
#endif
#endif
