#ifndef _INC_WCT
#define _INC_WCT

#if (_WIN32_WINNT >= 0x0600)

typedef LPVOID HWCT;

typedef struct _WAITCHAIN_NODE_INFO {
  WCT_OBJECT_TYPE   ObjectType;
  WCT_OBJECT_STATUS ObjectStatus;
  union DUMMYUNIONNAME {
    struct DUMMYSTRUCTNAME1 {
      WCHAR         ObjectName[WCT_OBJNAME_LENGTH];
      LARGE_INTEGER Timeout;
      WINBOOL       Alertable;
    } LockObject;
    struct DUMMYSTRUCTNAME2 {
      DWORD ProcessId;
      DWORD ThreadId;
      DWORD WaitTime;
      DWORD ContextSwitches;
    } ThreadObject;
  } ;
} WAITCHAIN_NODE_INFO, *PWAITCHAIN_NODE_INFO;

typedef VOID (CALLBACK *PWAITCHAINCALLBACK)(
    HWCT WctHandle,
    DWORD_PTR Context,
    DWORD CallbackStatus,
    LPDWORD NodeCount,
    PWAITCHAIN_NODE_INFO NodeInfoArray,
    LPBOOL IsCycle
);

HWCT WINAPI OpenThreadWaitChainSession(DWORD Flags,PWAITCHAINCALLBACK callback);
VOID WINAPI CloseThreadWaitChainSession(HWCT WctHandle);
WINBOOL WINAPI GetThreadWaitChain(
  HWCT WctHandle,
  DWORD_PTR Context,
  DWORD Flags,
  DWORD ThreadId,
  LPDWORD NodeCount,
  PWAITCHAIN_NODE_INFO NodeInfoArray,
  LPBOOL IsCycle
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_WCT*/
