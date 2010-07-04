#ifndef _INC_ISYSMON
#define _INC_ISYSMON
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef enum _SysmonDataType {
  sysmonDataAvg     = 1,
  sysmonDataMin     = 2,
  sysmonDataMax     = 3,
  sysmonDataTime    = 4,
  sysmonDataCount   = 5 
} SysmonDataType;

typedef enum _SysmonBatchReason {
  SysmonBatchNone          = 0,
  SysmonBatchAddFiles      = 1,
  SysmonBatchAddCounters   = 2 
} SysmonBatchReason;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_ISYSMON*/
