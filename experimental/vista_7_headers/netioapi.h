#ifndef _INC_NETIOAPI
#define _INC_NETIOAPI
#include <_mingw.h>
#include <iprtrmib.h>
#include <ifdef.h>
#if (_WIN32_WINNT >= 0x0600)

#ifdef __IPHLPAPI_H__
#define NETIO_STATUS DWORD
#define NETIOAPI_API_ WINAPI
#else
#define NETIO_STATUS NTSTATUS
#define NETIOAPI_API_ NTAPI
#endif

#define NETIOAPI_API NETIO_STATUS NETIOAPI_API_
#define ConvertInterfaceLuidToName __MINGW_NAME_AW(ConvertInterfaceLuidToName)
#define ConvertInterfaceNameToLuid __MINGW_NAME_AW(ConvertInterfaceNameToLuid)

typedef struct _MIB_ANYCASTIPADDRESS_ROW {
  SOCKADDR_INET Address;
  NET_LUID      InterfaceLuid;
  NET_IFINDEX   InterfaceIndex;
  SCOPE_ID      ScopeId;
} MIB_ANYCASTIPADDRESS_ROW, *PMIB_ANYCASTIPADDRESS_ROW;

typedef struct _MIB_IPFORWARD_ROW2 {
  NET_LUID          InterfaceLuid;
  NET_IFINDEX       InterfaceIndex;
  IP_ADDRESS_PREFIX DestinationPrefix;
  SOCKADDR_INET      NextHop;
  UCHAR             SitePrefixLength;
  ULONG             ValidLifetime;
  ULONG             PreferredLifetime;
  ULONG             Metric;
  NL_ROUTE_PROTOCOL Protocol;
  BOOLEAN           Loopback;
  BOOLEAN           AutoconfigureAddress;
  BOOLEAN           Publish;
  BOOLEAN           Immortal;
  ULONG             Age;
  NL_ROUTE_ORIGIN   Origin;
} MIB_IPFORWARD_ROW2, *PMIB_IPFORWARD_ROW2;

typedef struct _MIB_IPNET_ROW2 {
  SOCKADDR_INET     Address;
  NET_IFINDEX       InterfaceIndex;
  NET_LUID          InterfaceLuid;
  UCHAR             PhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
  ULONG             PhysicalAddressLength;
  NL_NEIGHBOR_STATE State;
  union DUMMYUNIONNAME1 {
    struct DUMMYSTRUCTNAME1 {
      BOOLEAN IsRouter  :1;
      BOOLEAN IsUnreachable  :1;
    } ;
    UCHAR  Flags;
  } ;
  union DUMMYUNIONNAME2 {
    ULONG LastReachable;
    ULONG LastUnreachable;
  } ReachabilityTime;
} MIB_IPNET_ROW2, *PMIB_IPNET_ROW2;

typedef struct _MIB_IPNET_ROW2 {
  SOCKADDR_INET     Address;
  NET_IFINDEX       InterfaceIndex;
  NET_LUID          InterfaceLuid;
  UCHAR             PhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
  ULONG             PhysicalAddressLength;
  NL_NEIGHBOR_STATE State;
  union DUMMYUNIONNAME1 {
    struct DUMMYSTRUCTNAME1 {
      BOOLEAN IsRouter  :1;
      BOOLEAN IsUnreachable  :1;
    } ;
    UCHAR  Flags;
  } ;
  union DUMMYUNIONNAME2 {
    ULONG LastReachable;
    ULONG LastUnreachable;
  } ReachabilityTime;
} MIB_IPNET_ROW2, *PMIB_IPNET_ROW2;

typedef struct _MIB_IPNET_TABLE2 {
  ULONG          NumEntries;
  MIB_IPNET_ROW2 Table[];
} MIB_IPNET_TABLE2, *PMIB_IPNET_TABLE2;

typedef struct _MIB_IPFORWARD_TABLE2 {
  ULONG              NumEntries;
  MIB_IPFORWARD_ROW2 Table[];
} MIB_IPFORWARD_TABLE2, *PMIB_IPFORWARD_TABLE2;

typedef struct _IP_ADDRESS_PREFIX {
  SOCKADDR_INET Prefix;
  UINT8         PrefixLength;
} IP_ADDRESS_PREFIX, *PIP_ADDRESS_PREFIX;

typedef struct _MIB_IPINTERFACE_ROW {
  ADDRESS_FAMILY                 Family;
  NET_LUID                       InterfaceLuid;
  NET_IFINDEX                    InterfaceIndex;
  ULONG                          MaxReassemblySize;
  ULONG64                        InterfaceIdentifier;
  ULONG                          MinRouterAdvertisementInterval;
  ULONG                          MaxRouterAdvertisementInterval;
  BOOLEAN                        AdvertisingEnabled;
  BOOLEAN                        ForwardingEnabled;
  BOOLEAN                        WeakHostSend;
  BOOLEAN                        WeakHostReceive;
  BOOLEAN                        UseAutomaticMetric;
  BOOLEAN                        UseNeighborUnreachabilityDetection;
  BOOLEAN                        ManagedAddressConfigurationSupported;
  BOOLEAN                        OtherStatefulConfigurationSupported;
  BOOLEAN                        AdvertiseDefaultRoute;
  NL_ROUTER_DISCOVERY_BEHAVIOR   RouterDiscoveryBehavior;
  ULONG                          DadTransmits;
  ULONG                          BaseReachableTime;
  ULONG                          RetransmitTime;
  ULONG                          PathMtuDiscoveryTimeout;
  NL_LINK_LOCAL_ADDRESS_BEHAVIOR LinkLocalAddressBehavior;
  ULONG                          LinkLocalAddressTimeout;
  ULONG                          ZoneIndices[ScopeLevelCount];
  ULONG                          SitePrefixLength;
  ULONG                          Metric;
  ULONG                          NlMtu;
  BOOLEAN                        Connected;
  BOOLEAN                        SupportsWakeUpPatterns;
  BOOLEAN                        SupportsNeighborDiscovery;
  BOOLEAN                        SupportsRouterDiscovery;
  ULONG                          ReachableTime;
  NL_INTERFACE_OFFLOAD_ROD       TransmitOffload;
  NL_INTERFACE_OFFLOAD_ROD       ReceiveOffload;
  BOOLEAN                        DisableDefaultRoutes;
} MIB_IPINTERFACE_ROW, *PMIB_IPINTERFACE_ROW;

typedef struct _MIB_IPINTERFACE_TABLE {
  ULONG               NumEntries;
  MIB_IPINTERFACE_ROW Table[];
} MIB_IPINTERFACE_TABLE, *PMIB_IPINTERFACE_TABLE;

typedef struct _MIB_UNICASTIPADDRESS_ROW {
  SOCKADDR_INET    Address;
  NET_LUID         InterfaceLuid;
  NET_IFINDEX      InterfaceIndex;
  NL_PREFIX_ORIGIN PrefixOrigin;
  NL_SUFFIX_ORIGIN SuffixOrigin;
  ULONG            ValidLifetime;
  ULONG            PreferredLifetime;
  UINT8            OnLinkPrefixLength;
  BOOLEAN          SkipAsSource;
  NL_DAD_STATE     DadState;
  SCOPE_ID         ScopeId;
  LARGE_INTEGER    CreationTimeStamp;
} MIB_UNICASTIPADDRESS_ROW, *PMIB_UNICASTIPADDRESS_ROW;

typedef struct _MIB_UNICASTIPADDRESS_TABLE {
  ULONG                    NumEntries;
  MIB_UNICASTIPADDRESS_ROW Table[];
} MIB_UNICASTIPADDRESS_TABLE, *PMIB_UNICASTIPADDRESS_TABLE;

NETIOAPI_API CancelMibChangeNotify2(
  HANDLE NotificationHandle
);

NETIO_STATUS WINAPI ConvertInterfaceAliasToLuid(
  const WCHAR *InterfaceAlias,
  PNET_LUID InterfaceLuid
);

NETIO_STATUS WINAPI ConvertInterfaceLuidToNameA(
  const NET_LUID *InterfaceLuid,
  PSTR InterfaceName,
  SIZE_T Length
);

NETIO_STATUS WINAPI ConvertInterfaceLuidToNameW(
  const NET_LUID *InterfaceLuid,
  PWSTR InterfaceName,
  SIZE_T Length
);

NETIO_STATUS WINAPI ConvertInterfaceNameToLuidA(
  const CHAR *InterfaceName,
  PNET_LUID InterfaceLuid
);

NETIO_STATUS WINAPI ConvertInterfaceNameToLuidW(
  const WCHAR *InterfaceName,
  PNET_LUID InterfaceLuid
);

PCHAR WINAPI if_indextoname(
  NET_IFINDEX InterfaceIndex,
  PCHAR InterfaceName
);

NET_IFINDEX WINAPI if_nametoindex(
  PCSTR InterfaceName
);

NETIO_STATUS WINAPI ConvertInterfaceGuidToLuid(
  const GUID *InterfaceGuid,
  PNET_LUID InterfaceLuid
);

NETIO_STATUS WINAPI ConvertInterfaceIndexToLuid(
  NET_IFINDEX InterfaceIndex,
  PNET_LUID InterfaceLuid
);

NETIO_STATUS WINAPI ConvertInterfaceLuidToAlias(
  const NET_LUID *InterfaceLuid,
  PWSTR InterfaceAlias,
  SIZE_T Length
);

NETIO_STATUS WINAPI ConvertInterfaceLuidToGuid(
  const NET_LUID *InterfaceLuid,
  GUID *InterfaceGuid
);

NETIO_STATUS WINAPI ConvertInterfaceLuidToIndex(
  const NET_LUID *InterfaceLuid,
  PNET_IFINDEX InterfaceIndex
);

NETIO_STATUS WINAPI ConvertIpv4MaskToLength(
  ULONG Mask,
  PUINT8 MaskLength
);

NETIO_STATUS WINAPI ConvertLengthToIpv4Mask(
  ULONG MaskLength,
  PULONG Mask
);

NETIOAPI_API CreateAnycastIpAddressEntry(
  const MIB_ANYCASTIPADDRESS_ROW *Row
);

NETIOAPI_API CreateIpForwardEntry2(
  const MIB_IPFORWARD_ROW2 *Row
);

NETIOAPI_API GetIpNetTable2(
  ADDRESS_FAMILY Family,
  PMIB_IPNET_TABLE2 *Table
);

NETIOAPI_API GetIpNetEntry2(
  PMIB_IPNET_ROW2 Row
);

NETIOAPI_API CreateIpNetEntry2(
  const MIB_IPNET_ROW2 *Row
);

NETIOAPI_API CreateSortedAddressPairs(
  const PSOCKADDR_IN6 SourceAddressList,
  ULONG SourceAddressCount,
  const PSOCKADDR_IN6 DestinationAddressList,
  ULONG DestinationAddressCount,
  ULONG AddressSortOptions,
  PSOCKADDR_IN6_PAIR *SortedAddressPairList,
  ULONG *SortedAddressPairCount
);

NETIOAPI_API CreateIpNetEntry2(
  const MIB_IPNET_ROW2 *Row
);

NETIOAPI_API CreateUnicastIpAddressEntry(
  __in  const MIB_UNICASTIPADDRESS_ROW *Row
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NETIOAPI*/
