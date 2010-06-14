#ifndef _INC_BTHSDPDEF
#define _INC_BTHSDPDEF

typedef union SdpQueryUuidUnion {
  GUID   uuid128;
  ULONG  uuid32;
  USHORT uuid16;
} SdpQueryUuidUnion;

typedef struct _SdpAttributeRange {
  USHORT minAttribute;
  USHORT maxAttribute;
} SdpAttributeRange;

typedef struct _SdpQueryUuid {
  SdpQueryUuidUnion u;
  USHORT            uuidType;
} SdpQueryUuid;

typedef struct _BTH_L2CAP_EVENT_INFO {
  BTH_ADDR bthAddress;
  USHORT   psm;
  UCHAR    connected;
  UCHAR    initiated;
} BTH_L2CAP_EVENT_INFO, *PBTH_L2CAP_EVENT_INFO;

#endif /*_INC_BTHSDPDEF*/
