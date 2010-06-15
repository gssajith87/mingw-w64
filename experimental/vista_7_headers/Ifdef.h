#ifndef _INC_IFDEF
#define _INC_IFDEF
#include <_mingw.h>

#if (_WIN32_WINNT >= 0x0600)

#define IF_TYPE_OTHER 1
#define IF_TYPE_ETHERNET_CSMACD 6
#define IF_TYPE_ISO88025_TOKENRING 9
#define IF_TYPE_PPP 23
#define IF_TYPE_SOFTWARE_LOOPBACK 24
#define IF_TYPE_ATM 37
#define IF_TYPE_IEEE80211 71
#define IF_TYPE_TUNNEL 131
#define IF_TYPE_IEEE1394 144

typedef union _NET_LUID {
  ULONG64 Value;
  struct DUMMYSTRUCTNAME {
    ULONG64 Reserved  :24;
    ULONG64 NetLuidIndex  :24;
    ULONG64 IfType  :16;
  } Info;
} NET_LUID, *PNET_LUID;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_IFDEF*/
