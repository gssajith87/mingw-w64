#ifndef _INC_WS2BTH
#define _INC_WS2BTH
#include <bthsdpdef.h>

typedef struct _BTH_QUERY_SERVICE {
  ULONG             type;
  ULONG             serviceHandle;
  SdpQueryUuid      uuids[MAX_UUIDS_IN_QUERY];
  ULONG             numRange;
  SdpAttributeRange pRange[1];
} BTH_QUERY_SERVICE, *PBTH_QUERY_SERVICE;

typedef struct _BTH_QUERY_DEVICE {
  ULONG LAP;
  UCHAR length;
} BTH_QUERY_DEVICE, *PBTH_QUERY_DEVICE;

typedef struct _BTH_RADIO_IN_RANGE {
  BTH_DEVICE_INFO deviceInfo;
  ULONG           previousDeviceFlags;
} BTH_RADIO_IN_RANGE, *PBTH_RADIO_IN_RANGE;

typedef struct _BTH_SET_SERVICE {
  PULONG pSdpVersion;
  HANDLE *pRecordHandle;
  ULONG  fCodService;
  ULONG  Reserved[5];
  ULONG  ulRecordLength;
  UCHAR  pRecord[1];
} BTH_SET_SERVICE, *PBTH_SET_SERVICE;

typedef struct _SOCKADDR_BTH {
  USHORT   addressFamily;
  BTH_ADDR btAddr;
  GUID     serviceClassId;
  ULONG    port;
} SOCKADDR_BTH, *PSOCKADDR_BTH;

#endif /*_INC_WS2BTH*/
