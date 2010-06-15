#ifndef _INC_KTMW32
#define _INC_KTMW32
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

WINBOOL WINAPI CommitComplete(
  HANDLE EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
);

WINBOOL WINAPI CommitEnlistment(
  HANDLE EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
);

WINBOOL WINAPI CommitTransaction(
  HANDLE TransactionHandle
);

WINBOOL WINAPI CommitTransactionAsync(
  HANDLE TransactionHandle
);

HANDLE WINAPI CreateEnlistment(
  LPSECURITY_ATTRIBUTES lpEnlistmentrAttributes,
  HANDLE ResourceManagerHandle,
  HANDLE TransactionHandle,
  NOTIFICATION_MASK NotificationMask,
  DWORD CreateOptions,
  PVOID EnlistmentKey
);

WINBOOL WINAPI SinglePhaseReject(
  HANDLE EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
);

HANDLE WINAPI CreateResourceManager(
  LPSECURITY_ATTRIBUTES lpResourceManagerAttributes,
  LPGUID ResourceManagerID,
  DWORD CreateOptions,
  HANDLE TmHandle,
  LPWSTR Description
);

HANDLE WINAPI CreateTransactionManager(
  LPSECURITY_ATTRIBUTES lpTransactionAttributes,
  LPWSTR LogFileName,
  ULONG CreateOptions,
  ULONG CommitStrength
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_CLFSW32*/
