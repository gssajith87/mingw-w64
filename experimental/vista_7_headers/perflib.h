#ifndef _INC_PERFLIB
#define _INC_PERFLIB

#if (_WIN32_WINNT >= 0x0600)
typedef LPVOID CALLBACK (*PERF_MEM_ALLOC)(SIZE_T AllocSize,LPVOID pContext);
typedef ULONG (WINAPI *PERFLIBREQUEST)(ULONG RequestCode,PVOID Buffer,ULONG BufferSize);
typedef void CALLBACK (*PERF_MEM_FREE)(LPVOID pBuffer,LPVOID pContext);


typedef struct _PERF_PROVIDER_CONTEXT {
  DWORD          ContextSize;
  DWORD          Reserved;
  PERFLIBREQUEST ControlCallback;
  PERF_MEM_ALLOC MemAllocRoutine;
  PERF_MEM_FREE  MemFreeRoutine;
  LPVOID         pMemContext;
} PERF_PROVIDER_CONTEXT, *PPERF_PROVIDER_CONTEXT;

#endif /*(_WIN32_WINNT >= 0x0600)*/

#endif /*_INC_PERFLIB*/