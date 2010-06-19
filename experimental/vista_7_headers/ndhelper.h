#ifndef _INC_NDHELPER
#define _INC_NDHELPER
#if (_WIN32_WINNT >= 0x0600)

typedef struct tagDiagnosticsInfo {
  long  cost;
  ULONG flags;
} DiagnosticsInfo, *PDiagnosticsInfo;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NDHELPER*/
