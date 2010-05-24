#ifndef _INC_MFREADWRITE
#define _INC_MFREADWRITE
#include <oaidl.h>

#if (_WIN32_WINNT >= 0x0601)

typedef enum MF_SOURCE_READER_FLAG {
  MF_SOURCE_READERF_ERROR                     = 0x00000001,
  MF_SOURCE_READERF_ENDOFSTREAM               = 0x00000002,
  MF_SOURCE_READERF_NEWSTREAM                 = 0x00000004,
  MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED    = 0x00000010,
  MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED   = 0x00000020,
  MF_SOURCE_READERF_STREAMTICK                = 0x00000100 
} MF_SOURCE_READER_FLAG;

typedef struct _MF_SINK_WRITER_STATISTICS {
  DWORD    cb;
  LONGLONG llLastTimestampReceived;
  LONGLONG llLastTimestampEncoded;
  LONGLONG llLastTimestampProcessed;
  LONGLONG llLastStreamTickReceived;
  LONGLONG llLastSinkSampleRequest;
  QWORD    qwNumSamplesReceived;
  QWORD    qwNumSamplesEncoded;
  QWORD    qwNumSamplesProcessed;
  QWORD    qwNumStreamTicksReceived;
  DWORD    dwByteCountQueued;
  QWORD    qwByteCountProcessed;
  DWORD    dwNumOutstandingSinkSampleRequests;
  DWORD    dwAverageSampleRateReceived;
  DWORD    dwAverageSampleRateEncoded;
  DWORD    dwAverageSampleRateProcessed;
} MF_SINK_WRITER_STATISTICS;

#endif /*(_WIN32_WINNT >= 0x0601)*/
#endif /*_INC_MFREADWRITE*/
