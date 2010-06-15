#ifndef _INC_WS2IPDEF
#define _INC_WS2IPDEF
#if (_WIN32_WINNT >= 0x0600)

typedef struct _sockaddr_in6_pair {
  PSOCKADDR_IN6 SourceAddress;
  PSOCKADDR_IN6 DestinationAddress;
} SOCKADDR_IN6_PAIR, *PSOCKADDR_IN6_PAIR;

typedef union _SOCKADDR_INET {
  SOCKADDR_IN    Ipv4;
  SOCKADDR_IN6   Ipv6;
  ADDRESS_FAMILY si_family;
} SOCKADDR_INET, *PSOCKADDR_INET;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WS2IPDEF*/
