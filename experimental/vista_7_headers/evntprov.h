#ifndef _INC_EVNTPROV
#define _INC_EVNTPROV
#if (_WIN32_WINNT >= 0x0600)
#include <windows.h>
#include <guiddef.h>

#define EVENT_CONTROL_CODE_DISABLE_PROVIDER 0
#define EVENT_CONTROL_CODE_ENABLE_PROVIDER 1
#define EVENT_CONTROL_CODE_CAPTURE_STATE 2

typedef LPVOID PREGHANDLE;
typedef LPVOID PENABLECALLBACK;

typedef struct _EVENT_DESCRIPTOR {
  USHORT    Id;
  UCHAR     Version;
  UCHAR     Channel;
  UCHAR     Level;
  UCHAR     Opcode;
  USHORT    Task;
  ULONGLONG Keyword;
} EVENT_DESCRIPTOR, *PEVENT_DESCRIPTOR;
typedef const EVENT_DESCRIPTOR *PCEVENT_DESCRIPTOR;

typedef struct _EVENT_DATA_DESCRIPTOR {
  ULONGLONG Ptr;
  ULONG     Size;
  ULONG     Reserved;
} EVENT_DATA_DESCRIPTOR, *PEVENT_DATA_DESCRIPTOR;

typedef struct _EVENT_FILTER_DESCRIPTOR {
  ULONGLONG Ptr;
  ULONG     Size;
  ULONG     Type;
} EVENT_FILTER_DESCRIPTOR, *PEVENT_FILTER_DESCRIPTOR;

#if (_WIN32_WINNT >= 0x0601)
typedef struct _EVENT_FILTER_HEADER {
  USHORT    Id;
  UCHAR     Version;
  UCHAR     Reserved[5];
  ULONGLONG InstanceId;
  ULONG     Size;
  ULONG     NextOffset;
} EVENT_FILTER_HEADER, *PEVENT_FILTER_HEADER;

ULONG EventWriteEx(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor,
  ULONG64 Filter,
  ULONG Flags,
  LPCGUID ActivityId,
  LPCGUID RelatedActivityId,
  ULONG UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

#endif /*(_WIN32_WINNT >= 0x0601)*/

void NTAPI EnableCallback(
  LPCGUID SourceId,
  ULONG IsEnabled,
  UCHAR Level,
  ULONGLONG MatchAnyKeyword,
  ULONGLONG MatchAllKeywords,
  PEVENT_FILTER_DESCRIPTOR FilterData,
  PVOID CallbackContext
);

ULONG NTAPI EventRegister(
  LPCGUID ProviderId,
  PENABLECALLBACK EnableCallback,
  PVOID CallbackContext,
  PREGHANDLE RegHandle
);

ULONG NTAPI EventWrite(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor,
  ULONG UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

ULONG NTAPI EventUnregister(
  REGHANDLE RegHandle
);

ULONG NTAPI EventActivityIdControl(
  ULONG ControlCode,
  LPGUID ActivityId
);

ULONG NTAPI EventWriteTransfer(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor,
  LPCGUID ActivityId,
  LPCGUID RelatedActivityId,
  ULONG UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

Boolean NTAPI EventEnabled(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor
);

#define WINEVENT_LEVEL_CRITICAL 1
#define WINEVENT_LEVEL_ERROR 2
#define WINEVENT_LEVEL_WARNING 3
#define WINEVENT_LEVEL_INFO 4
#define WINEVENT_LEVEL_VERBOSE 5

Boolean NTAPI EventProviderEnabled(
  REGHANDLE RegHandle,
  UCHAR Level,
  ULONGLONG Keyword
);

ULONG NTAPI EventWriteString(
  REGHANDLE RegHandle,
  UCHAR Level,
  ULONGLONG Keyword,
  PCWSTR String
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EVNTPROV*/
