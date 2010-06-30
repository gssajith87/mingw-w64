#ifndef _INC_MSRDC
#define _INC_MSRDC
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)
typedef LPVOID SimilarityFileIndexT;

typedef enum _GeneratorParametersType {
  RDCGENTYPE_Unused      = 0,
  RDCGENTYPE_FilterMax   = 1 
} GeneratorParametersType;

typedef enum _RdcCreatedTables {
  RDCTABLE_InvalidOrUnknown   = 0,
  RDCTABLE_Existing           = 1,
  RDCTABLE_New                = 2 
} RdcCreatedTables;

typedef enum _RdcMappingAccessMode {
  RDCMAPPING_Undefined   = 0,
  RDCMAPPING_ReadOnly    = 1,
  RDCMAPPING_ReadWrite   = 2 
} RdcMappingAccessMode;

typedef enum _RDC_ErrorCode {
  RDC_NoError                  = 0,
  RDC_HeaderVersionNewer       = 1,
  RDC_HeaderVersionOlder       = 2,
  RDC_HeaderMissingOrCorrupt   = 3,
  RDC_HeaderWrongType          = 4,
  RDC_DataMissingOrCorrupt     = 5,
  RDC_DataTooManyRecords       = 6,
  RDC_FileChecksumMismatch     = 7,
  RDC_ApplicationError         = 8,
  RDC_Aborted                  = 9,
  RDC_Win32Error               = 10 
} RDC_ErrorCode;

typedef enum _RdcNeedType {
  RDCNEED_SOURCE     = 0,
  RDCNEED_TARGET     = 1,
  RDCNEED_SEED       = 2,
  RDCNEED_SEED_MAX   = 255 
} RdcNeedType;

typedef struct _FindSimilarFileIndexResults {
  SimilarityFileIndexT m_FileIndex;
  unsigned             m_MatchCount;
} FindSimilarFileIndexResults;

typedef struct _RdcBufferPointer {
  ULONG m_Size;
  ULONG m_Used;
  BYTE  *m_Data;
} RdcBufferPointer;

typedef struct _RdcNeed {
  RdcNeedType      m_BlockType;
  unsigned __int64 m_FileOffset;
  unsigned __int64 m_BlockLength;
} RdcNeed;

typedef struct _RdcNeedPointer {
  ULONG   m_Size;
  ULONG   m_Used;
  RdcNeed *m_Data;
} RdcNeedPointer;

typedef struct _RdcSignature {
  BYTE   m_Signature[MSRDC_SIGNATURE_HASHSIZE];
  USHORT m_BlockLength;
} RdcSignature;

typedef struct _RdcSignaturePointer {
  ULONG        m_Size;
  ULONG        m_Used;
  RdcSignature *m_Data;
} RdcSignaturePointer;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif _INC_MSRDC
