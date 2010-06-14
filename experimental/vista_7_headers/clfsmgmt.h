#ifndef _INC_CLFSMGMT
#define _INC_CLFSMGMT
#if (_WIN32_WINNT >= 0x0600)

#define ClfsMgmtAdvanceTailNotification 0
#define ClfsMgmtLogFullHandlerNotification 1
#define ClfsMgmtLogUnpinnedNotification 2
#define ClfsMgmtLogWriteNotification 3

typedef enum _CLFS_MGMT_POLICY_TYPE {
  ClfsMgmtPolicyMaximumSize             = 0x0,
  ClfsMgmtPolicyMinimumSize             = 0x1,
  ClfsMgmtPolicyNewContainerSize        = 0x2,
  ClfsMgmtPolicyGrowthRate              = 0x3,
  ClfsMgmtPolicyLogTail                 = 0x4,
  ClfsMgmtPolicyAutoShrink              = 0x5,
  ClfsMgmtPolicyAutoGrow                = 0x6,
  ClfsMgmtPolicyNewContainerPrefix      = 0x7,
  ClfsMgmtPolicyNewContainerSuffix      = 0x8,
  ClfsMgmtPolicyNewContainerExtension 
} CLFS_MGMT_POLICY_TYPE, *PCLFS_MGMT_POLICY_TYPE;

typedef struct _CLFS_NODE_ID {
  ULONG cType;
  ULONG cbNode;
} CLFS_NODE_ID, *PCLFS_NODE_ID;

typedef struct _CLFS_MGMT_NOTIFICATION {
  CLFS_MGMT_NOTIFICATION_TYPE Notification;
  CLFS_LSN                    Lsn;
  USHORT                      LogIsPinned;
} CLFS_MGMT_NOTIFICATION, *PCLFS_MGMT_NOTIFICATION;

typedef struct _CLFS_MGMT_POLICY {
  ULONG Version;
  ULONG LengthInBytes;
  ULONG PolicyFlags;
  CLFS_MGMT_POLICY_TYPE PolicyType;
  union DUMMYUNIONNAME {
    struct DUMMYSTRUCTNAME1 {
      ULONG Containers;
    } MaximumSize;
    struct DUMMYSTRUCTNAME2 {
      ULONG Containers;
    } MinimumSize;
    struct DUMMYSTRUCTNAME3 {
      ULONG SizeInBytes;
    } NewContainerSize;
    struct DUMMYSTRUCTNAME4 {
      ULONG AbsoluteGrowthInContainers;
      ULONG RelativeGrowthPercentage;
    } GrowthRate;
    struct DUMMYSTRUCTNAME5 {
      ULONG MinimumAvailablePercentage;
      ULONG MinimumAvailableContainers;
    } LogTail;
    struct DUMMYSTRUCTNAME6 {
      ULONG Percentage;
    } AutoShrink;
    struct DUMMYSTRUCTNAME7 {
      ULONG Enabled;
    } AutoGrow;
    struct DUMMYSTRUCTNAME8 {
      USHORT PrefixLengthInBytes;
      WCHAR PrefixString[1];
    } NewContainerPrefix;
    struct DUMMYSTRUCTNAME9 {
      ULONGLONG NextContainerSuffix;
    } NewContainerSuffix;
    struct DUMMYSTRUCTNAME {
      USHORT ExtensionLengthInBytes;
      WCHAR ExtensionString[1];
    } NewContainerExtension;
  } PolicyParameters;
} CLFS_MGMT_POLICY,  *PCLFS_MGMT_POLICY;


#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_CLFSMGMT*/
