#ifndef _INC_TDH
#define _INC_TDH
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef enum _EVENT_FIELD_TYPE {
  EventKeywordInformation   = 0,
  EventLevelInformation     = 1,
  EventChannelInformation   = 2,
  EventTaskInformation      = 3,
  EventOpcodeInformation    = 4,
  EventInformationMax       = 5 
} EVENT_FIELD_TYPE;

typedef struct _EVENT_MAP_ENTRY {
  ULONG OutputOffset;
  union DUMMYUNIONNAME {
    ULONG Value;
    ULONG InputOffset;
  } ;
} EVENT_MAP_ENTRY, *PEVENT_MAP_ENTRY;

typedef enum _MAP_VALUETYPE
{
  EVENTMAP_ENTRY_VALUETYPE_ULONG  = 0,
  EVENTMAP_ENTRY_VALUETYPE_STRING = 1 
} MAP_VALUETYPE;

typedef enum _MAP_FLAGS {
  EVENTMAP_INFO_FLAG_MANIFEST_VALUEMAP     = 1,
  EVENTMAP_INFO_FLAG_MANIFEST_BITMAP       = 2,
  EVENTMAP_INFO_FLAG_MANIFEST_PATTERNMAP   = 4,
  EVENTMAP_INFO_FLAG_WBEM_VALUEMAP         = 8,
  EVENTMAP_INFO_FLAG_WBEM_BITMAP           = 16,
  EVENTMAP_INFO_FLAG_WBEM_FLAG             = 32,
  EVENTMAP_INFO_FLAG_WBEM_NO_MAP           = 64 
} MAP_FLAGS;

typedef struct _EVENT_MAP_INFO {
  ULONG NameOffset;
  MAP_FLAGS Flag;
  ULONG EntryCount;
  union DUMMYUNIONNAME {
    MAP_VALUETYPE MapEntryValueType;
    ULONG FormatStringOffset;
  };
  EVENT_MAP_ENTRY MapEntryArray[];
} EVENT_MAP_INFO;

typedef enum _PROPERTY_FLAGS {
  PropertyStruct             = 0x1,
  PropertyParamLength        = 0x2,
  PropertyParamCount         = 0x4,
  PropertyWBEMXmlFragment    = 0x8,
  PropertyParamFixedLength   = 0x10 
} PROPERTY_FLAGS;

typedef enum _MAP_VALUETYPE {
  EVENTMAP_ENTRY_VALUETYPE_ULONG    = 0,
  EVENTMAP_ENTRY_VALUETYPE_STRING   = 1 
} MAP_VALUETYPE;

typedef struct _EVENT_PROPERTY_INFO {
  PROPERTY_FLAGS Flags;
  ULONG          NameOffset;
  union DUMMYUNIONNAME1 {
    struct DUMMYSTRUCTNAME1 {
      USHORT InType;
      USHORT OutType;
      ULONG  MapNameOffset;
    } nonStructType;
    struct DUMMYSTRUCTNAME2 {
      USHORT StructStartIndex;
      USHORT NumOfStructMembers;
      ULONG  padding;
    } structType;
  } ;
  union DUMMYUNIONNAME2 {
    USHORT count;
    USHORT countPropertyIndex;
  } ;
  union DUMMYUNIONNAME3 {
    USHORT length;
    USHORT lengthPropertyIndex;
  } ;
  ULONG          Reserved;
} EVENT_PROPERTY_INFO;

typedef enum _DECODING_SOURCE {
  DecodingSourceXMLFile   = 0,
  DecodingSourceWbem      = 1,
  DecodingSourceWPP       = 2 
} DECODING_SOURCE;

typedef enum _PROPERTY_FLAGS {
  PropertyStruct             = 0x1,
  PropertyParamLength        = 0x2,
  PropertyParamCount         = 0x4,
  PropertyWBEMXmlFragment    = 0x8,
  PropertyParamFixedLength   = 0x10 
} PROPERTY_FLAGS;

typedef struct _TRACE_EVENT_INFO {
  GUID                ProviderGuid;
  GUID                EventGuid;
  EVENT_DESCRIPTOR    EventDescriptor;
  DECODING_SOURCE     DecodingSource;
  ULONG               ProviderNameOffset;
  ULONG               LevelNameOffset;
  ULONG               ChannelNameOffset;
  ULONG               KeywordsNameOffset;
  ULONG               TaskNameOffset;
  ULONG               OpcodeNameOffset;
  ULONG               EventMessageOffset;
  ULONG               ProviderMessageOffset;
  ULONG               BinaryXMLOffset;
  ULONG               BinaryXMLSize;
  ULONG               ActivityIDNameOffset;
  ULONG               RelatedActivityIDNameOffset;
  ULONG               PropertyCount;
  ULONG               TopLevelPropertyCount;
  TEMPLATE_FLAGS      Flags;
  EVENT_PROPERTY_INFO EventPropertyInfoArray[];
} TRACE_EVENT_INFO;

typedef struct _PROPERTY_DATA_DESCRIPTOR {
  ULONGLONG PropertyName;
  ULONG     ArrayIndex;
  ULONG     Reserved;
} PROPERTY_DATA_DESCRIPTOR;

typedef struct _TRACE_PROVIDER_INFO {
  GUID  ProviderGuid;
  ULONG SchemaSource;
  ULONG ProviderNameOffset;
} TRACE_PROVIDER_INFO;

typedef struct _PROVIDER_ENUMERATION_INFO {
  ULONG               NumberOfProviders;
  ULONG               Padding;
  TRACE_PROVIDER_INFO TraceProviderInfoArray[];
} PROVIDER_ENUMERATION_INFO;

typedef struct _PROVIDER_FIELD_INFO {
  ULONG     NameOffset;
  ULONG     DescriptionOffset;
  ULONGLONG Value;
} PROVIDER_FIELD_INFO;

typedef struct _PROVIDER_FIELD_INFOARRAY {
  ULONG               NumberOfElements;
  EVENT_FIELD_TYPE    FieldType;
  PROVIDER_FIELD_INFO FieldInfoArray[];
} PROVIDER_FIELD_INFOARRAY;

#if (_WIN32_WINNT >= 0x0601)
typedef struct _PROVIDER_FILTER_INFO {
  UCHAR               Id;
  UCHAR               Version;
  ULONG               MessageOffset;
  ULONG               Reserved;
  ULONG               PropertyCount;
  EVENT_PROPERTY_INFO EventPropertyInfoArray[ANYSIZE_ARRAY];
} PROVIDER_FILTER_INFO, *PPROVIDER_FILTER_INFO;
#endif /*(_WIN32_WINNT >= 0x0601)*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_TDH*/
