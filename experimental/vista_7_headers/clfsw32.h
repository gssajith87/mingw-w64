#ifndef _INC_CLFSW32
#define _INC_CLFSW32
#include <windows.h>
#include <clfs.h>

#if (_WIN32_WINNT >= 0x0600)

typedef PVOID (* CLFS_BLOCK_ALLOCATION) (ULONG cbBufferSize, PVOID pvUserContext);
typedef void  (* CLFS_BLOCK_DEALLOCATION) (PVOID pvBuffer, PVOID pvUserContext);
typedef LPVOID PFILE;
typedef LPVOID CLFS_PRINT_RECORD_ROUTINE; /*Unknown Callback*/

WINBOOL WINAPI AdvanceLogBase(PVOID pvMarshal,PCLFS_LSN plsnBase,ULONG fFlags,LPOVERLAPPED pOverlapped);

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

WINBOOL WINAPI DeleteLogByHandle(
  HANDLE hLog
);

WINBOOL WINAPI DeleteLogFile(
  LPCWSTR pszLogFileName,
  PVOID pvReserved
);

WINBOOL WINAPI DeregisterManageableLogClient(
  HANDLE hLog
);

WINBOOL WINAPI DumpLogRecords(
  PWSTR pwszLogFileName,
  CLFS_RECORD_TYPE fRecordType,
  PCLFS_LSN plsnStart,
  PCLFS_LSN plsnEnd,
  PFILE pstrmOut,
  CLFS_PRINT_RECORD_ROUTINE pfnPrintRecord,
  CLFS_BLOCK_ALLOCATION pfnAllocBlock,
  CLFS_BLOCK_DEALLOCATION pfnFreeBlock,
  PVOID   pvBlockAllocContext,
  ULONG cbBlock,
  ULONG cMaxBlocks
);

WINBOOL WINAPI ReadLogRecord(
  PVOID pvMarshal,
  PCLFS_LSN plsnFirst,
  CLFS_CONTEXT_MODE eContextMode,
  PVOID *ppvReadBuffer,
  PULONG pcbReadBuffer,
  PCLFS_RECORD_TYPE peRecordType,
  PCLFS_LSN plsnUndoNext,
  PCLFS_LSN plsnPrevious,
  PVOID *ppvReadContext,
  LPOVERLAPPED pOverlapped
);

WINBOOL WINAPI ReadNextLogRecord(
  PVOID pvReadContext,
  PVOID *ppvBuffer,
  PULONG pcbBuffer,
  PCLFS_RECORD_TYPE peRecordType,
  PCLFS_LSN plsnUser,
  PCLFS_LSN plsnUndoNext,
  PCLFS_LSN plsnPrevious,
  PCLFS_LSN plsnRecord,
  LPOVERLAPPED pOverlapped
);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_CLFSW32*/
