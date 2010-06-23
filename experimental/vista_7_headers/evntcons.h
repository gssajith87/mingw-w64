#ifndef _INC_EAPMETHODTYPES
#define _INC_EAPMETHODTYPES
#include <windows.h>
#include <evntrace.h>
#if (_WIN32_WINNT >= 0x0600)

typedef enum EVENTSECURITYOPERATION {
  EventSecuritySetDACL,
  EventSecuritySetSACL,
  EventSecurityAddDACL,
  EventSecurityAddSACL,
  EventSecurityMax 
} EVENTSECURITYOPERATION;

typedef struct _EVENT_EXTENDED_ITEM_INSTANCE {
  ULONG InstanceId;
  ULONG ParentInstanceId;
  GUID  ParentGuid;
} EVENT_EXTENDED_ITEM_INSTANCE, *PEVENT_EXTENDED_ITEM_INSTANCE;

typedef struct _EVENT_EXTENDED_ITEM_TS_ID {
  ULONG SessionId;
} EVENT_EXTENDED_ITEM_TS_ID, *PEVENT_EXTENDED_ITEM_TS_ID;

typedef struct _EVENT_EXTENDED_ITEM_RELATED_ACTIVITYID {
  GUID RelatedActivityId;
} EVENT_EXTENDED_ITEM_RELATED_ACTIVITYID, *PEVENT_EXTENDED_ITEM_RELATED_ACTIVITYID;

typedef struct _EVENT_HEADER_EXTENDED_DATA_ITEM {
  USHORT    Reserved1;
  USHORT    ExtType;
  struct DUMMYSTRUCTNAME1 {
    USHORT Linkage  :1;
    USHORT Reserved2  :15;
  } ;
  USHORT    DataSize;
  ULONGLONG DataPtr;
} EVENT_HEADER_EXTENDED_DATA_ITEM, *PEVENT_HEADER_EXTENDED_DATA_ITEM;

typedef struct _EVENT_HEADER {
  USHORT           Size;
  USHORT           HeaderType;
  USHORT           Flags;
  USHORT           EventProperty;
  ULONG            ThreadId;
  ULONG            ProcessId;
  LARGE_INTEGER    TimeStamp;
  GUID             ProviderId;
  EVENT_DESCRIPTOR EventDescriptor;
  union DUMMYUNIONNAME1 {
    struct DUMMYSTRUCTNAME1 {
      ULONG KernelTime;
      ULONG UserTime;
    } ;
    ULONG64 ProcessorTime;
  } ;
  GUID             ActivityId;
} EVENT_HEADER, *PEVENT_HEADER;

typedef struct _EVENT_RECORD {
  EVENT_HEADER                     EventHeader;
  ETW_BUFFER_CONTEXT               BufferContext;
  USHORT                           ExtendedDataCount;
  USHORT                           UserDataLength;
  PEVENT_HEADER_EXTENDED_DATA_ITEM ExtendedData;
  PVOID                            UserData;
  PVOID                            UserContext;
} EVENT_RECORD, *PEVENT_RECORD;

ULONG WINAPI EventAccessControl(
  LPGUID Guid,
  ULONG Operation,
  PSID Sid,
  ULONG Rights,
  BOOLEAN AllowOrDeny
);

ULONG WINAPI EventAccessQuery(
  LPGUID Guid,
  PSECURITY_DESCRIPTOR Buffer,
  PULONG BufferSize
);

ULONG WINAPI EventAccessRemove(
  LPGUID Guid
);

#if (_WIN32_WINNT >= 0x0601)

typedef struct _EVENT_EXTENDED_ITEM_STACK_TRACE32 {
  ULONG64 MatchId;
  ULONG   Address[];
} EVENT_EXTENDED_ITEM_STACK_TRACE32, *PEVENT_EXTENDED_ITEM_STACK_TRACE32;

typedef struct _EVENT_EXTENDED_ITEM_STACK_TRACE64 {
  ULONG64 MatchId;
  ULONG64 Address[];
} EVENT_EXTENDED_ITEM_STACK_TRACE64, *PEVENT_EXTENDED_ITEM_STACK_TRACE64;

#endif /*(_WIN32_WINNT >= 0x0601)*/
#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EAPMETHODTYPES*/
