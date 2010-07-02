#ifndef _INC_CLFSMGMTW32
#define _INC_CLFSMGMTW32
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef VOID (CALLBACK * PLOG_UNPINNED_CALLBACK )(
  HANDLE hLogFile,
  PVOID pvClientContext
);

typedef VOID (CALLBACK * PLOG_FULL_HANDLER_CALLBACK )(
  HANDLE  hLogFile,
  DWORD   dwError,
  WINBOOL fLogIsPinned,
  PVOID   pvClientContext
);

typedef VOID (CALLBACK * PLOG_TAIL_ADVANCE_CALLBACK )(
  HANDLE hLogFile,
  CLFS_LSN lsnTarget,
  PVOID pvClientContext
);

typedef struct _LOG_MANAGEMENT_CALLBACKS {
  PVOID                      CallbackContext;
  PLOG_TAIL_ADVANCE_CALLBACK AdvanceTailCallback;
  PLOG_FULL_HANDLER_CALLBACK LogFullHandlerCallback;
  PLOG_UNPINNED_CALLBACK     LogUnpinnedCallback;
} LOG_MANAGEMENT_CALLBACKS, *PLOG_MANAGEMENT_CALLBACKS;

WINBOOL WINAPI HandleLogFull(
  HANDLE hLog
);

WINBOOL WINAPI RegisterManageableLogClient(
  HANDLE hLog,
  PLOG_MANAGEMENT_CALLBACKS pCallbacks
);

WINBOOL WINAPI ReadLogNotification(
  HANDLE hLog,
  PCLFS_MGMT_NOTIFICATION pNotification,
  LPOVERLAPPED lpOverlapped
);

WINBOOL WINAPI LogTailAdvanceFailure(
  HANDLE hLog,
  DWORD dwReason
);

WINBOOL WINAPI RegisterForLogWriteNotification(
  HANDLE hLog,
  ULONG cbThreshold,
  WINBOOL fEnable
);

WINBOOL WINAPI RemoveLogPolicy(
  HANDLE hLog,
  CLFS_MANAGEMENT_POLICY_TYPE ePolicyType
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_CLFSMGMTW32*/
