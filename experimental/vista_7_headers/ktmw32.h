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

WINBOOL WINAPI GetCurrentClockTransactionManager(
  HANDLE TransactionManagerHandle,
  PLARGE_INTEGER TmVirtualClock
);

WINBOOL WINAPI GetEnlistmentId(
  HANDLE EnlistmentHandle,
  LPGUID EnlistmentId
);

WINBOOL WINAPI GetEnlistmentRecoveryInformation(
  HANDLE EnlistmentHandle,
  ULONG BufferSize,
  PVOID Buffer,
  PULONG BufferUsed
);

WINBOOL WINAPI GetNotificationResourceManager(
  HANDLE ResourceManagerHandle,
  PTRANSACTION_NOTIFICATION TransactionNotification,
  ULONG NotificationLength,
  DWORD dwMilliseconds,
  PULONG ReturnLength
);

WINBOOL WINAPI GetNotificationResourceManagerAsync(
  HANDLE ResourceManagerHandle,
  PTRANSACTION_NOTIFICATION TransactionNotification,
  ULONG TransactionNotificationLength,
  PULONG ReturnLength,
  LPOVERLAPPED pOverlapped
);

WINBOOL WINAPI SetResourceManagerCompletionPort(
  HANDLE ResourceManagerHandle,
  HANDLE IoCompletionPortHandle,
  ULONG_PTR CompletionKey
);

WINBOOL WINAPI GetTransactionId(
  HANDLE TransactionHandle,
  LPGUID TransactionId
);

WINBOOL WINAPI GetTransactionInformation(
  HANDLE TransactionHandle,
  PDWORD Outcome,
  PDWORD IsolationLevel,
  PDWORD IsolationFlags,
  PDWORD Timeout,
  DWORD BufferLength,
  LPWSTR Description
);

WINBOOL WINAPI GetTransactionManagerId(
  HANDLE TransactionManagerHandle,
  LPGUID TransactionManagerId
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_CLFSW32*/
