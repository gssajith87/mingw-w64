#ifndef _INC_TCPMIB
#define _INC_TCPMIB
#if (_WIN32_WINNT >= 0x0600)

typedef enum _TCP_CONNECTION_OFFLOAD_STATE {
  TcpConnectionOffloadStateInHost       = 0,
  TcpConnectionOffloadStateOffloading   = 1,
  TcpConnectionOffloadStateOffloaded    = 2,
  TcpConnectionOffloadStateUploading    = 3,
  TcpConnectionOffloadStateMax          = 4 
} TCP_CONNECTION_OFFLOAD_STATE;

typedef struct _MIB_TCP6ROW {
  MIB_TCP_STATE State;
  IN6_ADDR      LocalAddr;
  DWORD         dwLocalScopeId;
  DWORD         dwLocalPort;
  IN6_ADDR      RemoteAddr;
  DWORD         dwRemoteScopeId;
  DWORD         dwRemotePort;
} MIB_TCP6ROW, *PMIB_TCP6ROW;

typedef struct _MIB_TCP6TABLE {
  DWORD       dwNumEntries;
  MIB_TCP6ROW table[];
} MIB_TCP6TABLE, *PMIB_TCP6TABLE;

typedef struct _MIB_TCP6ROW2 {
  IN6_ADDR                     LocalAddr;
  DWORD                        dwLocalScopeId;
  DWORD                        dwLocalPort;
  IN6_ADDR                     RemoteAddr;
  DWORD                        dwRemoteScopeId;
  DWORD                        dwRemotePort;
  MIB_TCP_STATE                State;
  DWORD                        dwOwningPid;
  TCP_CONNECTION_OFFLOAD_STATE dwOffloadState;
} MIB_TCP6ROW2, *PMIB_TCP6ROW2;

typedef struct _MIB_TCP6TABLE2 {
  DWORD        dwNumEntries;
  MIB_TCP6ROW2 table[];
} MIB_TCP6TABLE2, *PMIB_TCP6TABLE2;

typedef struct _MIB_TCPROW2 {
  DWORD                        dwState;
  DWORD                        dwLocalAddr;
  DWORD                        dwLocalPort;
  DWORD                        dwRemoteAddr;
  DWORD                        dwRemotePort;
  TCP_CONNECTION_OFFLOAD_STATE dwOffloadState;
} MIB_TCPROW2, *PMIB_TCPROW2;

typedef struct _MIB_TCPTABLE2 {
  DWORD       dwNumEntries;
  MIB_TCPROW2 table[];
} MIB_TCPTABLE2, *PMIB_TCPTABLE2;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_TCPMIB*/
