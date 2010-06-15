#ifndef _INC_CLFSW32
#define _INC_CLFSW32
#include <clfs.h>

#if (_WIN32_WINNT >= 0x0600)

typedef PVOID (* CLFS_BLOCK_ALLOCATION) (ULONG cbBufferSize, PVOID pvUserContext);
typedef void  (* CLFS_BLOCK_DEALLOCATION) (PVOID pvBuffer, PVOID pvUserContext);

WINBOOL WINAPI AlignReservedLog(PVOID pvMarshal,ULONG cReservedRecords,LONGLONG rgcbReservation,PLONGLONG pcbAlignReservation);
WINBOOL WINAPI AllocReservedLog(PVOID pvMarshal,ULONG cReservedRecords,PLONGLONG pcbAdjustment);

WINBOOL WINAPI AddLogContainer(HANDLE hLog,PULONGLONG pcbContainer,LPWSTR pwszContainerPath,LPVOID pReserved);
WINBOOL WINAPI AddLogContainerSet(HANDLE hLog,USHORT cContainers,PULONGLONG pcbContainer,LPWSTR *rgwszContainerPath,PVOID Reserved);
WINBOOL WINAPI CloseAndResetLogFile(HANDLE hLog);

WINBOOL WINAPI CreateLogContainerScanContext(
  HANDLE hLog,
  ULONG cFromContainer,
  ULONG cContainers,
  CLFS_SCAN_MODE eScanMode,
  PCLFS_SCAN_CONTEXT pcxScan,
  LPOVERLAPPED pOverlapped
);

HANDLE WINAPI CreateLogFile(
  LPCWSTR pszLogFileName,
  ACCESS_MASK fDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES psaLogFile,
  ULONG fCreateDisposition,
  ULONG fFlagsAndAttributes
);

WINBOOL WINAPI ScanLogContainers(
  PCLFS_SCAN_CONTEXT pcxScan,
  CLFS_SCAN_MODE eScanMode,
  LPVOID pReserved
);

WINBOOL WINAPI CreateLogMarshallingArea(
  HANDLE hLog,
  CLFS_BLOCK_ALLOCATION pfnAllocBuffer,
  CLFS_BLOCK_DEALLOCATION pfnFreeBuffer,
  PVOID   pvBlockAllocContext,
  ULONG cbMarshallingBuffer,
  ULONG  cMaxWriteBuffers,
  ULONG cMaxReadBuffers,
  PVOID *ppvMarshal
);

WINBOOL WINAPI DeleteLogMarshallingArea(
  PVOID pvMarshal
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_CLFSW32*/
