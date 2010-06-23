#ifndef _INC_PLA
#define _INC_PLA
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef enum _AutoPathFormat {
  plaNone                 = 0x0000,
  plaPattern              = 0x0001,
  plaComputer             = 0x0002,
  plaMonthDayHour         = 0x0100,
  plaSerialNumber         = 0x0200,
  plaYearDayOfYear        = 0x0400,
  plaYearMonth            = 0x0800,
  plaYearMonthDay         = 0x1000,
  plaYearMonthDayHour     = 0x2000,
  plaMonthDayHourMinute   = 0x4000 
} AutoPathFormat;

typedef enum _ClockType {
  plaTimeStamp     = 0,
  plaPerformance   = 1,
  plaSystem        = 2,
  plaCycle         = 3 
} ClockType;

typedef enum _CommitMode {
  plaCreateNew               = 0x0001,
  plaModify                  = 0x0002,
  plaCreateOrModify          = 0x0003,
  plaUpdateRunningInstance   = 0x0010,
  plaFlushTrace              = 0x0020,
  plaValidateOnly            = 0x1000 
} CommitMode;

typedef enum _FileFormat {
  plaCommaSeparated   = 0,
  plaTabSeparated     = 1,
  plaSql              = 2,
  plaBinary           = 3 
} FileFormat;

typedef enum _FolderActionSteps {
  plaCreateCab      = 0x01,
  plaDeleteData     = 0x02,
  plaSendCab        = 0x04,
  plaDeleteCab      = 0x08,
  plaDeleteReport   = 0x10 
} FolderActionSteps;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_PLA*/
