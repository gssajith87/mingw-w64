#ifndef _INC_UDPMIB
#define _INC_UDPMIB
#if (_WIN32_WINNT >= 0x0600)

typedef struct _MIB_UDP6ROW {
  IN6_ADDR dwLocalAddr;
  DWORD    dwLocalScopeId;
  DWORD    dwLocalPort;
} MIB_UDP6ROW, *PMIB_UDP6ROW;

typedef struct _MIB_UDP6TABLE {
  DWORD       dwNumEntries;
  MIB_UDP6ROW table[ANY_SIZE];
} MIB_UDP6TABLE, *PMIB_UDP6TABLE;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_UDPMIB*/
