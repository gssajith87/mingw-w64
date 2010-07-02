#ifndef _INC_EVNTPROV
#define _INC_EVNTPROV
#if (_WIN32_WINNT >= 0x0600)

#ifndef EVNTAPI
#ifndef MIDL_PASS
#ifdef _EVNT_SOURCE_
#define EVNTAPI __stdcall
#else
#define EVNTAPI DECLSPEC_IMPORT __stdcall
#endif /* _EVNT_SOURCE_ */
#endif /* MIDL_PASS */
#endif /* EVNTAPI */

#ifndef FORCEINLINE
#ifdef __GNUC__
#define FORCEINLINE __attribute((always_inline))
#endif /*__GNUC__*/
#endif /*FORCEINLINE*/

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <guiddef.h>

typedef ULONGLONG REGHANDLE, *PREGHANDLE;

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

typedef struct _EVENT_FILTER_HEADER {
  USHORT    Id;
  UCHAR     Version;
  UCHAR     Reserved[5];
  ULONGLONG InstanceId;
  ULONG     Size;
  ULONG     NextOffset;
} EVENT_FILTER_HEADER, *PEVENT_FILTER_HEADER;


#define WINEVENT_LEVEL_CRITICAL	1
#define WINEVENT_LEVEL_ERROR	2
#define WINEVENT_LEVEL_WARNING	3
#define WINEVENT_LEVEL_INFO	4
#define WINEVENT_LEVEL_VERBOSE	5

#ifndef _ETW_KM_ /* for wdm.h */

typedef VOID
(NTAPI *PENABLECALLBACK)(
  LPCGUID SourceId,
  ULONG IsEnabled,
  UCHAR Level,
  ULONGLONG MatchAnyKeyword,
  ULONGLONG MatchAllKeyword,
  PEVENT_FILTER_DESCRIPTOR FilterData,
  PVOID CallbackContext);

#if (_WIN32_WINNT >= 0x0600)
ULONG EVNTAPI EventRegister(
  LPCGUID ProviderId,
  PENABLECALLBACK EnableCallback,
  PVOID CallbackContext,
  PREGHANDLE RegHandle
);

ULONG EVNTAPI EventUnregister(
  REGHANDLE RegHandle
);

BOOLEAN EVNTAPI EventEnabled(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor
);

BOOLEAN EVNTAPI EventProviderEnabled(
  REGHANDLE RegHandle,
  UCHAR Level,
  ULONGLONG Keyword
);

ULONG EVNTAPI EventWrite(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor,
  ULONG UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

ULONG EVNTAPI EventWriteTransfer(
  REGHANDLE RegHandle,
  PCEVENT_DESCRIPTOR EventDescriptor,
  LPCGUID ActivityId,
  LPCGUID RelatedActivityId,
  ULONG UserDataCount,
  PEVENT_DATA_DESCRIPTOR UserData
);

ULONG EVNTAPI EventWriteString(
  REGHANDLE RegHandle,
  UCHAR Level,
  ULONGLONG Keyword,
  PCWSTR String
);

ULONG EVNTAPI EventActivityIdControl(
  ULONG ControlCode,
  LPGUID ActivityId
);
#endif /*(_WIN32_WINNT >= 0x0600)*/

#if (_WIN32_WINNT >= 0x0601)
ULONG EVNTAPI EventWriteEx(
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

#endif /* _ETW_KM_ */

FORCEINLINE
VOID
EventDataDescCreate(
  OUT PEVENT_DATA_DESCRIPTOR EventDataDescriptor,
  IN const VOID* DataPtr,
  IN ULONG DataSize)
{
  EventDataDescriptor->Ptr = (ULONGLONG)(ULONG_PTR)DataPtr;
  EventDataDescriptor->Size = DataSize;
  EventDataDescriptor->Reserved = 0;
}

FORCEINLINE
VOID
EventDescCreate(
  OUT PEVENT_DESCRIPTOR EventDescriptor,
  IN USHORT Id,
  IN UCHAR Version,
  IN UCHAR Channel,
  IN UCHAR Level,
  IN USHORT Task,
  IN UCHAR Opcode,
  IN ULONGLONG Keyword)
{
  EventDescriptor->Id = Id;
  EventDescriptor->Version = Version;
  EventDescriptor->Channel = Channel;
  EventDescriptor->Level = Level;
  EventDescriptor->Task = Task;
  EventDescriptor->Opcode = Opcode;
  EventDescriptor->Keyword = Keyword;
}

FORCEINLINE
VOID
EventDescZero(
  OUT PEVENT_DESCRIPTOR EventDescriptor)
{
  memset(EventDescriptor, 0, sizeof(EVENT_DESCRIPTOR));
}

FORCEINLINE
USHORT
EventDescGetId(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Id);
}

FORCEINLINE
UCHAR
EventDescGetVersion(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Version);
}

FORCEINLINE
USHORT
EventDescGetTask(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Task);
}

FORCEINLINE
UCHAR
EventDescGetOpcode(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Opcode);
}

FORCEINLINE
UCHAR
EventDescGetChannel(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Channel);
}

FORCEINLINE
UCHAR
EventDescGetLevel(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Level);
}

FORCEINLINE
ULONGLONG
EventDescGetKeyword(
  IN PCEVENT_DESCRIPTOR EventDescriptor)
{
  return (EventDescriptor->Keyword);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetId(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN USHORT Id)
{
  EventDescriptor->Id = Id;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetVersion(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN UCHAR Version)
{
  EventDescriptor->Version = Version;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetTask(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN USHORT Task)
{
  EventDescriptor->Task = Task;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetOpcode(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN UCHAR Opcode)
{
  EventDescriptor->Opcode = Opcode;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetLevel(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN UCHAR  Level)
{
  EventDescriptor->Level = Level;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetChannel(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN UCHAR Channel)
{
  EventDescriptor->Channel = Channel;
  return (EventDescriptor);
}

FORCEINLINE
PEVENT_DESCRIPTOR
EventDescSetKeyword(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN ULONGLONG Keyword)
{
  EventDescriptor->Keyword = Keyword;
  return (EventDescriptor);
}


FORCEINLINE
PEVENT_DESCRIPTOR
EventDescOrKeyword(
  IN PEVENT_DESCRIPTOR EventDescriptor,
  IN ULONGLONG Keyword)
{
  EventDescriptor->Keyword |= Keyword;
  return (EventDescriptor);
}

#ifdef __cplusplus
}
#endif

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EVNTPROV*/
