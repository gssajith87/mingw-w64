#ifndef _INC_PLA
#define _INC_PLA

#if (_WIN32_WINNT >= 0x0600)

typedef enum  {
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

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_PLA*/
