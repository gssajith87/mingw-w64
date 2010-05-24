#ifndef _INC_MFIDL
#define _INC_MFIDL
#include <mfobjects.h>

#if (_WIN32_WINNT >= 0x0600)

#if (_WIN32_WINNT >= 0x0601)

typedef enum _MF_QUALITY_ADVISE_FLAGS {
  MF_QUALITY_CANNOT_KEEP_UP   = 0x1 
} MF_QUALITY_ADVISE_FLAGS;

#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum _MF_QUALITY_DROP_MODE {
  MF_DROP_MODE_NONE   = 0x0,
  MF_DROP_MODE_1      = 0x1,
  MF_DROP_MODE_2      = 0x2,
  MF_DROP_MODE_3      = 0x3,
  MF_DROP_MODE_4      = 0x4,
  MF_DROP_MODE_5      = 0x5,
  MF_NUM_DROP_MODES   = 0x6 
} MF_QUALITY_DROP_MODE;

typedef enum _MF_QUALITY_LEVEL {
  MF_QUALITY_NORMAL           = 0x0,
  MF_QUALITY_NORMAL_MINUS_1   = 0x1,
  MF_QUALITY_NORMAL_MINUS_2   = 0x2,
  MF_QUALITY_NORMAL_MINUS_3   = 0x3,
  MF_QUALITY_NORMAL_MINUS_4   = 0x4,
  MF_QUALITY_NORMAL_MINUS_5   = 0x5,
  MF_NUM_QUALITY_LEVELS       = 0x6 
} MF_QUALITY_LEVEL;

typedef enum MF_SOURCE_READER_CONTROL_FLAG {
  MF_SOURCE_READER_CONTROLF_DRAIN   = 0x00000001 
} MF_SOURCE_READER_CONTROL_FLAG;

typedef enum _MF_TOPOLOGY_RESOLUTION_STATUS_FLAGS {
  MF_TOPOLOGY_RESOLUTION_SUCCEEDED              = 0x00000000,
  MF_OPTIONAL_NODE_REJECTED_MEDIA_TYPE          = 0x00000001,
  MF_OPTIONAL_NODE_REJECTED_PROTECTED_PROCESS   = 0x00000002 
} MF_TOPOLOGY_RESOLUTION_STATUS_FLAGS

typedef enum MF_TOPOLOGY_TYPE {
  MF_TOPOLOGY_OUTPUT_NODE,
  MF_TOPOLOGY_SOURCESTREAM_NODE,
  MF_TOPOLOGY_TRANSFORM_NODE,
  MF_TOPOLOGY_TEE_NODE,
  MF_TOPOLOGY_MAX                 = 0xffffffff 
} MF_TOPOLOGY_TYPE;

typedef enum _MF_TOPONODE_DRAIN_MODE {
  MF_TOPONODE_DRAIN_DEFAULT,
  MF_TOPONODE_DRAIN_ALWAYS,
  MF_TOPONODE_DRAIN_NEVER 
} MF_TOPONODE_DRAIN_MODE;

typedef enum _MF_TOPONODE_FLUSH_MODE {
  MF_TOPONODE_FLUSH_ALWAYS,
  MF_TOPONODE_FLUSH_SEEK,
  MF_TOPONODE_FLUSH_NEVER 
} MF_TOPONODE_FLUSH_MODE;

#if (_WIN32_WINNT >= 0x0601)

typedef enum _MF_TRANSCODE_TOPOLOGY_MODE_FLAGS {
  MF_TRANSCODE_TOPOLOGYMODE_SOFTWARE_ONLY      = 0,
  MF_TRANSCODE_TOPOLOGYMODE_HARDWARE_ALLOWED   = 1 
} MF_TRANSCODE_TOPOLOGYMODE_FLAGS;

#endif

typedef enum  {
  MF_LICENSE_URL_UNTRUSTED,
  MF_LICENSE_URL_TRUSTED,
  MF_LICENSE_URL_TAMPERED 
} MF_URL_TRUST_STATUS;

typedef enum MFASF_INDEXERFLAGS {
  MFASF_INDEXER_WRITE_NEW_INDEX            = 0x00000001,
  MFASF_INDEXER_READ_FOR_REVERSEPLAYBACK   = 0x00000004,
  MFASF_INDEXER_WRITE_FOR_LIVEREAD         = 0x00000008 
} ;

typedef enum MFCLOCK_CHARACTERISTICS_FLAGS {
  MFCLOCK_CHARACTERISTICS_FLAG_FREQUENCY_10MHZ   = 0x2,
  MFCLOCK_CHARACTERISTICS_FLAG_ALWAYS_RUNNING    = 0x4,
  MFCLOCK_CHARACTERISTICS_FLAG_IS_SYSTEM_CLOCK   = 0x8 
} ;

typedef enum _MFCLOCK_RELATIONAL_FLAGS {
  MFCLOCK_RELATIONAL_FLAG_JITTER_NEVER_AHEAD   = 0x1 
} MFCLOCK_RELATIONAL_FLAGS;

typedef enum _MF_CLOCK_STATE {
  MFCLOCK_STATE_INVALID,
  MFCLOCK_STATE_RUNNING,
  MFCLOCK_STATE_STOPPED,
  MFCLOCK_STATE_PAUSED 
} MF_CLOCK_STATE;

typedef enum _MFMEDIASOURCE_CHARACTERISTICS {
  MFMEDIASOURCE_IS_LIVE                      = 0x1,
  MFMEDIASOURCE_CAN_SEEK                     = 0x2,
  MFMEDIASOURCE_CAN_PAUSE                    = 0x4,
  MFMEDIASOURCE_HAS_SLOW_SEEK                = 0x8,
  MFMEDIASOURCE_HAS_MULTIPLE_PRESENTATIONS   = 0x10,
  MFMEDIASOURCE_CAN_SKIPFORWARD              = 0x20,
  MFMEDIASOURCE_CAN_SKIPBACKWARD             = 0x40 
} MFMEDIASOURCE_CHARACTERISTICS;

typedef enum _MFNET_PROXYSETTINGS {
  MFNET_PROXYSETTING_NONE      = 0,
  MFNET_PROXYSETTING_MANUAL    = 1,
  MFNET_PROXYSETTING_AUTO      = 2,
  MFNET_PROXYSETTING_BROWSER   = 3 
} MFNET_PROXYSETTINGS;

typedef enum _MFNetAuthenticationFlags {
  MFNET_AUTHENTICATION_PROXY            = 0x00000001,
  MFNET_AUTHENTICATION_CLEAR_TEXT       = 0x00000002,
  MFNET_AUTHENTICATION_LOGGED_ON_USER 
} MFNetAuthenticationFlags;

typedef enum _MFNetCredentialOptions {
  MFNET_CREDENTIAL_SAVE               = 0x00000001,
  MFNET_CREDENTIAL_DONT_CACHE         = 0x00000002,
  MFNET_CREDENTIAL_ALLOW_CLEAR_TEXT   = 0x00000004 
} MFNetCredentialOptions;

typedef enum _MFNetCredentialRequirements {
  REQUIRE_PROMPT          = 0x00000001,
  REQUIRE_SAVE_SELECTED   = 0x00000002 
} MFNetCredentialRequirements;

typedef enum _MFNETSOURCE_CACHE_STATE {
  MFNETSOURCE_CACHE_UNAVAILABLE,
  MFNETSOURCE_CACHE_ACTIVE_WRITING,
  MFNETSOURCE_CACHE_ACTIVE_COMPLETE 
} MFNETSOURCE_CACHE_STATE;

typedef enum _MFNETSOURCE_PROTOCOL_TYPE {
  MFNETSOURCE_UNDEFINED   = 0x0,
  MFNETSOURCE_HTTP        = 0x1,
  MFNETSOURCE_RTSP        = 0x2,
  MFNETSOURCE_FILE        = 0x3,
  MFNETSOURCE_MULTICAST   = 0x4 
} MFNETSOURCE_PROTOCOL_TYPE;

typedef enum _MFNETSOURCE_STATISTICS_IDS {
  MFNETSOURCE_RECVPACKETS_ID                = 0,
  MFNETSOURCE_LOSTPACKETS_ID,
  MFNETSOURCE_RESENDSREQUESTED_ID,
  MFNETSOURCE_RESENDSRECEIVED_ID,
  MFNETSOURCE_RECOVEREDBYECCPACKETS_ID,
  MFNETSOURCE_RECOVEREDBYRTXPACKETS_ID,
  MFNETSOURCE_OUTPACKETS_ID,
  MFNETSOURCE_RECVRATE_ID,
  MFNETSOURCE_AVGBANDWIDTHBPS_ID,
  MFNETSOURCE_BYTESRECEIVED_ID,
  MFNETSOURCE_PROTOCOL_ID,
  MFNETSOURCE_TRANSPORT_ID,
  MFNETSOURCE_CACHE_STATE_ID,
  MFNETSOURCE_LINKBANDWIDTH_ID,
  MFNETSOURCE_CONTENTBITRATE_ID,
  MFNETSOURCE_SPEEDFACTOR_ID,
  MFNETSOURCE_BUFFERSIZE_ID,
  MFNETSOURCE_BUFFERPROGRESS_ID,
  MFNETSOURCE_LASTBWSWITCHTS_ID,
  MFNETSOURCE_SEEKRANGESTART_ID,
  MFNETSOURCE_SEEKRANGEEND_ID,
  MFNETSOURCE_BUFFERINGCOUNT_ID,
  MFNETSOURCE_INCORRECTLYSIGNEDPACKETS_ID,
  MFNETSOURCE_SIGNEDSESSION_ID,
  MFNETSOURCE_MAXBITRATE_ID,
  MFNETSOURCE_RECEPTION_QUALITY_ID,
  MFNETSOURCE_RECOVEREDPACKETS_ID,
  MFNETSOURCE_VBR_ID,
  MFNETSOURCE_DOWNLOADPROGRESS_ID 
} MFNETSOURCE_STATISTICS_IDS;

typedef enum _MFNETSOURCE_TRANSPORT_TYPE {
  MFNETSOURCE_UDP,
  MFNETSOURCE_TCP 
} MFNETSOURCE_TRANSPORT_TYPE;

typedef enum MFPMPSESSION_CREATION_FLAGS {
  MFPMPSESSION_UNPROTECTED_PROCESS   = 0x1 
} MFPMPSESSION_CREATION_FLAGS;

typedef enum _MFPOLICYMANAGER_ACTION {
  PEACTION_NO          = 0,
  PEACTION_PLAY        = 1,
  PEACTION_COPY        = 2,
  PEACTION_EXPORT      = 3,
  PEACTION_EXTRACT     = 4,
  PEACTION_RESERVED1   = 5,
  PEACTION_RESERVED2   = 6,
  PEACTION_RESERVED3   = 7,
  PEACTION_LAST        = 7 
} MFPOLICYMANAGER_ACTION;

typedef enum _MFRATE_DIRECTION {
  MFRATE_FORWARD,
  MFRATE_REVERSE 
} MFRATE_DIRECTION;

typedef enum _MFSequencerTopologyFlags {
  SequencerTopologyFlags_Last   = 0x00000001 
} MFSequencerTopologyFlags;

typedef enum MFSESSION_GETFULLTOPOLOGY_FLAGS {
  MFSESSION_GETFULLTOPOLOGY_CURRENT 
} MFSESSION_GETFULLTOPOLOGY_FLAGS;

typedef enum MFSESSION_SETTOPOLOGY_FLAGS {
  MFSESSION_SETTOPOLOGY_IMMEDIATE       = 0x1,
  MFSESSION_SETTOPOLOGY_NORESOLUTION    = 0x2,
  MFSESSION_SETTOPOLOGY_CLEAR_CURRENT   = 0x4 
} MFSESSION_SETTOPOLOGY_FLAGS;

typedef enum _MFSHUTDOWN_STATUS {
  MFSHUTDOWN_INITIATED,
  MFSHUTDOWN_COMPLETED 
} MFSHUTDOWN_STATUS;

typedef enum _MFSINK_WMDRMACTION {
  MFSINK_WMDRMACTION_UNDEFINED    = 0,
  MFSINK_WMDRMACTION_ENCODE       = 1,
  MFSINK_WMDRMACTION_TRANSCODE    = 2,
  MFSINK_WMDRMACTION_TRANSCRYPT   = 3,
  MFSINK_WMDRMACTION_LAST         = 3 
} MFSINK_WMDRMACTION;

typedef enum MFSTREAMSINK_MARKER_TYPE {
  MFSTREAMSINK_MARKER_DEFAULT,
  MFSTREAMSINK_MARKER_ENDOFSEGMENT,
  MFSTREAMSINK_MARKER_TICK,
  MFSTREAMSINK_MARKER_EVENT 
} ;

typedef enum MFTIMER_FLAGS {
  MFTIMER_RELATIVE   = 0x00000001 
} MFTIMER_FLAGS;

#if (_WIN32_WINNT >= 0x0601)

typedef enum MFTOPLOGY_DXVA_MODE {
  MFTOPOLOGY_DXVA_DEFAULT   = 0,
  MFTOPOLOGY_DXVA_NONE      = 1,
  MFTOPOLOGY_DXVA_FULL      = 2 
} MFTOPOLOGY_DXVA_MODE;

typedef enum MFTOPOLOGY_HARDWARE_MODE {
  MFTOPOLOGY_HWMODE_SOFTWARE_ONLY   = 0,
  MFTOPOLOGY_HWMODE_USE_HARDWARE    = 1 
} MFTOPOLOGY_HARDWARE_MODE;

#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef struct _ASFFlatPicture {
  BYTE  bPictureType;
  DWORD dwDataLen;
} ASF_FLAT_PICTURE;

typedef struct _ASFFlatSynchronisedLyrics {
  BYTE  bTimeStampFormat;
  BYTE  bContentType;
  DWORD dwLyricsLen;
} ASF_FLAT_SYNCHRONISED_LYRICS;

typedef struct _ASF_INDEX_DESCRIPTOR {
  ASF_INDEX_IDENTIFIER Identifier;
  WORD                 cPerEntryBytes;
  WCHAR                szDescription[32];
  DWORD                dwInterval;
} ASF_INDEX_DESCRIPTOR;

typedef struct _ASF_INDEX_IDENTIFIER {
  GUID guidIndexType;
  WORD wStreamNumber;
} ASF_INDEX_IDENTIFIER;

typedef struct ASF_MUX_STATISTICS {
  DWORD cFramesWritten;
  DWORD cFramesDropped;
} ASF_MUX_STATISTICS;

typedef enum SAMPLE_PROTECTION_VERSION {
  SAMPLE_PROTECTION_VERSION_NO           = 0,
  SAMPLE_PROTECTION_VERSION_BASIC_LOKI   = 1,
  SAMPLE_PROTECTION_VERSION_SCATTER      = 2,
  SAMPLE_PROTECTION_VERSION_RC4          = 3 
} SAMPLE_PROTECTION_VERSION;

typedef struct _ASFFlatSynchronisedLyrics {
  BYTE  bTimeStampFormat;
  BYTE  bContentType;
  DWORD dwLyricsLen;
} ASF_FLAT_SYNCHRONISED_LYRICS;

typedef struct _MF_TRANSCODE_SINK_INFO {
  DWORD        dwVideoStreamID;
  IMFMediaType *pVideoMediaType;
  DWORD        dwAudioStreamID;
  IMFMediaType *pAudioMediaType;
} MF_TRANSCODE_SINK_INFO;

typedef struct _MF_LEAKY_BUCKET_PAIR {
  DWORD dwBitrate;
  DWORD msBufferWindow;
} MF_LEAKY_BUCKET_PAIR;

typedef struct _MFBYTESTREAM_BUFFERING_PARAMS {
  QWORD                cbTotalFileSize;
  QWORD                cbPlayableDataSize;
  MF_LEAKY_BUCKET_PAIR *prgBuckets;
  DWORD                cBuckets;
  QWORD                qwNetBufferingTime;
  QWORD                qwExtraBufferingTimeDuringSeek;
  QWORD                qwPlayDuration;
  float                dRate;
} MFBYTESTREAM_BUFFERING_PARAMS;

#undef  INTERFACE
#define INTERFACE IMFByteStreamBuffering
DECLARE_INTERFACE_(IMFByteStreamBuffering,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IMFByteStreamBuffering methods */
    STDMETHOD_(HRESULT,EnableBuffering)(THIS_ WINBOOL fEnable) PURE;
    STDMETHOD_(HRESULT,SetBufferingParams)(THIS_ MFBYTESTREAM_BUFFERING_PARAMS *pParams) PURE;
    STDMETHOD_(HRESULT,StopBuffering)(THIS) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IMFByteStreamBuffering_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IMFByteStreamBuffering_AddRef(This) (This)->pVtbl->AddRef(This)
#define IMFByteStreamBuffering_Release(This) (This)->pVtbl->Release(This)
#define IMFByteStreamBuffering_EnableBuffering(This,fEnable) (This)->lpVtbl->EnableBuffering(This,fEnable)
#define IMFByteStreamBuffering_SetBufferingParams(This,pParams) (This)->lpVtbl->SetBufferingParams(This,pParams)
#define IMFByteStreamBuffering_StopBuffering() (This)->lpVtbl->StopBuffering(This)
#endif /*COBJMACROS*/

#undef  INTERFACE
#define INTERFACE IMFPresentationDescriptor
DECLARE_INTERFACE_(IMFPresentationDescriptor,IMFAttributes)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IMFPresentationDescriptor methods */
    STDMETHOD_(HRESULT,Compare)(THIS_ IMFAttributes *pTheirs,MF_ATTRIBUTES_MATCH_TYPE MatchType,BOOL *pbResult) PURE;
    STDMETHOD_(HRESULT,CompareItem)(THIS_ REFGUID guidKey,REFPROPVARIANT Value,BOOL *pbResult) PURE;
    STDMETHOD_(HRESULT,CopyAllItems)(THIS_ IMFAttributes *pDest) PURE;
    STDMETHOD_(HRESULT,DeleteAllItems)(THIS) PURE;
    STDMETHOD_(HRESULT,DeleteItem)(THIS_ REFGUID guidKey) PURE;
    STDMETHOD_(HRESULT,GetAllocatedBlob)(THIS_ REFGUID guidKey,UINT8 **ppBuf,UINT32 *pcbSize) PURE;
    STDMETHOD_(HRESULT,GetAllocatedString)(THIS_ REFGUID guidKey,LPWSTR *ppwszValue,UINT32 *pcchLength) PURE;
    STDMETHOD_(HRESULT,GetBlob)(THIS_ REFGUID guidKey,UINT8 *pBuf,UINT32 cbBufSize,UINT32 *pcbBlobSize) PURE;
    STDMETHOD_(HRESULT,GetBlobSize)(THIS_ REFGUID guidKey,UINT32 *pcbBlobSize) PURE;
    STDMETHOD_(HRESULT,GetCount)(THIS_ UINT32 *pcItems) PURE;
    STDMETHOD_(HRESULT,GetDouble)(THIS_ REFGUID guidKey,double *pfValue) PURE;
    STDMETHOD_(HRESULT,GetGUID)(THIS_ REFGUID guidKey,GUID *pguidValue) PURE;
    STDMETHOD_(HRESULT,GetItem)(THIS_ REFGUID guidKey,PROPVARIANT *pValue) PURE;
    STDMETHOD_(HRESULT,GetItemByIndex)(THIS_ UINT32 unIndex,GUID *pguidKey,PROPVARIANT *pValue) PURE;
    STDMETHOD_(HRESULT,GetItemType)(THIS_ REFGUID guidKey,MF_ATTRIBUTE_TYPE *pType) PURE;
    STDMETHOD_(HRESULT,GetString)(THIS_ REFGUID guidKey,LPWSTR pwszValue,UINT32 cchBufSize,UINT32 *pcchLength) PURE;
    STDMETHOD_(HRESULT,GetStringLength)(THIS_ REFGUID guidKey,UINT32 *pcchLength) PURE;
    STDMETHOD_(HRESULT,GetUINT32)(THIS_ REFGUID guidKey,UINT32 *punValue) PURE;
    STDMETHOD_(HRESULT,GetUINT64)(THIS_ REFGUID guidKey,UINT64 *punValue) PURE;
    STDMETHOD_(HRESULT,GetUnknown)(THIS_ REFGUID guidKey,REFIID riid,LPVOID *ppv) PURE;
    STDMETHOD_(HRESULT,LockStore)(THIS) PURE;
    STDMETHOD_(HRESULT,SetBlob)(THIS_ REFGUID guidKey,const UINT8 *pBuf,UINT32 cbBufSize) PURE;
    STDMETHOD_(HRESULT,SetDouble)(THIS_ REFGUID guidKey,double fValue) PURE;
    STDMETHOD_(HRESULT,SetGUID)(THIS_ REFGUID guidKey,REFGUID guidValue) PURE;
    STDMETHOD_(HRESULT,SetItem)(THIS_ REFGUID guidKey,REFPROPVARIANT Value) PURE;
    STDMETHOD_(HRESULT,SetString)(THIS_ REFGUID guidKey,LPCWSTR wszValue) PURE;
    STDMETHOD_(HRESULT,SetUINT32)(THIS_ REFGUID guidKey,UINT32 unValue) PURE;
    STDMETHOD_(HRESULT,SetUINT64)(THIS_ REFGUID guidKey,UINT64 unValue) PURE;
    STDMETHOD_(HRESULT,SetUnknown)(THIS_ REFGUID guidKey,IUnknown *pUnknown) PURE;
    STDMETHOD_(HRESULT,UnlockStore)(THIS) PURE;
    STDMETHOD_(HRESULT,Clone)(THIS_ IMFPresentationDescriptor **ppPresentationDescriptor) PURE;
    STDMETHOD_(HRESULT,DeselectStream)(THIS_ DWORD dwDescriptorIndex) PURE;
    STDMETHOD_(HRESULT,GetStreamDescriptorByIndex)(THIS_ DWORD dwIndex,BOOL *pfSelected,IMFStreamDescriptor **ppDescriptor) PURE;
    STDMETHOD_(HRESULT,GetStreamDescriptorCount)(THIS_ DWORD *pdwDescriptorCount) PURE;
    STDMETHOD_(HRESULT,SelectStream)(THIS_ DWORD dwDescriptorIndex) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IMFPresentationDescriptor_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IMFPresentationDescriptor_AddRef(This) (This)->pVtbl->AddRef(This)
#define IMFPresentationDescriptor_Release(This) (This)->pVtbl->Release(This)
#define IMFPresentationDescriptor_Compare(This,pTheirs,MatchType,pbResult) (This)->lpVtbl->Compare(This,pTheirs,MatchType,pbResult)
#define IMFPresentationDescriptor_CompareItem(This,guidKey,Value,pbResult) (This)->lpVtbl->CompareItem(This,guidKey,Value,pbResult)
#define IMFPresentationDescriptor_CopyAllItems(This,pDest) (This)->lpVtbl->CopyAllItems(This,pDest)
#define IMFPresentationDescriptor_DeleteAllItems() (This)->lpVtbl->DeleteAllItems(This)
#define IMFPresentationDescriptor_DeleteItem(This,guidKey) (This)->lpVtbl->DeleteItem(This,guidKey)
#define IMFPresentationDescriptor_GetAllocatedBlob(This,guidKey,ppBuf,pcbSize) (This)->lpVtbl->GetAllocatedBlob(This,guidKey,ppBuf,pcbSize)
#define IMFPresentationDescriptor_GetAllocatedString(This,guidKey,ppwszValue,pcchLength) (This)->lpVtbl->GetAllocatedString(This,guidKey,ppwszValue,pcchLength)
#define IMFPresentationDescriptor_GetBlob(This,guidKey,pBuf,cbBufSize,pcbBlobSize) (This)->lpVtbl->GetBlob(This,guidKey,pBuf,cbBufSize,pcbBlobSize)
#define IMFPresentationDescriptor_GetBlobSize(This,guidKey,pcbBlobSize) (This)->lpVtbl->GetBlobSize(This,guidKey,pcbBlobSize)
#define IMFPresentationDescriptor_GetCount(This,pcItems) (This)->lpVtbl->GetCount(This,pcItems)
#define IMFPresentationDescriptor_GetDouble(This,guidKey,pfValue) (This)->lpVtbl->GetDouble(This,guidKey,pfValue)
#define IMFPresentationDescriptor_GetGUID(This,guidKey,pguidValue) (This)->lpVtbl->GetGUID(This,guidKey,pguidValue)
#define IMFPresentationDescriptor_GetItem(This,guidKey,pValue) (This)->lpVtbl->GetItem(This,guidKey,pValue)
#define IMFPresentationDescriptor_GetItemByIndex(This,unIndex,pguidKey,pValue) (This)->lpVtbl->GetItemByIndex(This,unIndex,pguidKey,pValue)
#define IMFPresentationDescriptor_GetItemType(This,guidKey,pType) (This)->lpVtbl->GetItemType(This,guidKey,pType)
#define IMFPresentationDescriptor_GetString(This,guidKey,pwszValue,cchBufSize,pcchLength) (This)->lpVtbl->GetString(This,guidKey,pwszValue,cchBufSize,pcchLength)
#define IMFPresentationDescriptor_GetStringLength(This,guidKey,pcchLength) (This)->lpVtbl->GetStringLength(This,guidKey,pcchLength)
#define IMFPresentationDescriptor_GetUINT32(This,guidKey,punValue) (This)->lpVtbl->GetUINT32(This,guidKey,punValue)
#define IMFPresentationDescriptor_GetUINT64(This,guidKey,punValue) (This)->lpVtbl->GetUINT64(This,guidKey,punValue)
#define IMFPresentationDescriptor_GetUnknown(This,guidKey,riid,ppv) (This)->lpVtbl->GetUnknown(This,guidKey,riid,ppv)
#define IMFPresentationDescriptor_LockStore() (This)->lpVtbl->LockStore(This)
#define IMFPresentationDescriptor_SetBlob(This,guidKey,pBuf,cbBufSize) (This)->lpVtbl->SetBlob(This,guidKey,pBuf,cbBufSize)
#define IMFPresentationDescriptor_SetDouble(This,guidKey,fValue) (This)->lpVtbl->SetDouble(This,guidKey,fValue)
#define IMFPresentationDescriptor_SetGUID(This,guidKey,guidValue) (This)->lpVtbl->SetGUID(This,guidKey,guidValue)
#define IMFPresentationDescriptor_SetItem(This,guidKey,Value) (This)->lpVtbl->SetItem(This,guidKey,Value)
#define IMFPresentationDescriptor_SetString(This,guidKey,wszValue) (This)->lpVtbl->SetString(This,guidKey,wszValue)
#define IMFPresentationDescriptor_SetUINT32(This,guidKey,unValue) (This)->lpVtbl->SetUINT32(This,guidKey,unValue)
#define IMFPresentationDescriptor_SetUINT64(This,guidKey,unValue) (This)->lpVtbl->SetUINT64(This,guidKey,unValue)
#define IMFPresentationDescriptor_SetUnknown(This,guidKey,pUnknown) (This)->lpVtbl->SetUnknown(This,guidKey,pUnknown)
#define IMFPresentationDescriptor_UnlockStore() (This)->lpVtbl->UnlockStore(This)
#define IMFPresentationDescriptor_Clone(This,ppPresentationDescriptor) (This)->lpVtbl->Clone(This,ppPresentationDescriptor)
#define IMFPresentationDescriptor_DeselectStream(This,dwDescriptorIndex) (This)->lpVtbl->DeselectStream(This,dwDescriptorIndex)
#define IMFPresentationDescriptor_GetStreamDescriptorByIndex(This,dwIndex,pfSelected,ppDescriptor) (This)->lpVtbl->GetStreamDescriptorByIndex(This,dwIndex,pfSelected,ppDescriptor)
#define IMFPresentationDescriptor_GetStreamDescriptorCount(This,pdwDescriptorCount) (This)->lpVtbl->GetStreamDescriptorCount(This,pdwDescriptorCount)
#define IMFPresentationDescriptor_SelectStream(This,dwDescriptorIndex) (This)->lpVtbl->SelectStream(This,dwDescriptorIndex)
#endif /*COBJMACROS*/

#if (_WIN32_WINNT >= 0x0601)
#undef  INTERFACE
#define INTERFACE IMFByteStreamCacheControl
DECLARE_INTERFACE_(IMFByteStreamCacheControl,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IMFByteStreamCacheControl methods */
    STDMETHOD_(HRESULT,StopBackgroundTransfer)(THIS) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IMFByteStreamCacheControl_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IMFByteStreamCacheControl_AddRef(This) (This)->pVtbl->AddRef(This)
#define IMFByteStreamCacheControl_Release(This) (This)->pVtbl->Release(This)
#define IMFByteStreamCacheControl_StopBackgroundTransfer() (This)->lpVtbl->StopBackgroundTransfer(This)
#endif /*COBJMACROS*/
#endif /*(_WIN32_WINNT >= 0x0601)*/

HRESULT WINAPI CreateNamedPropertyStore(INamedPropertyStore **ppStore);
HRESULT WINAPI CreatePropertyStore(IPropertyStore **ppStore);

#if (_WIN32_WINNT >= 0x0601)
HRESULT MFCreate3GPMediaSink(IMFByteStream *pIByteStream,IMFMediaType *pVideoMediaType,IMFMediaType *pAudioMediaType,IMFMediaSink **ppIMediaSink);
HRESULT MFCreateAggregateSource(IMFCollection *pSourceCollection,IMFMediaSource **ppAggSource);
#endif /*(_WIN32_WINNT >= 0x0601)*/

#define MF_1_BYTE_ALIGNMENT     0x00000000
#define MF_2_BYTE_ALIGNMENT     0x00000001
#define MF_4_BYTE_ALIGNMENT     0x00000003
#define MF_8_BYTE_ALIGNMENT     0x00000007
#define MF_16_BYTE_ALIGNMENT    0x0000000F
#define MF_32_BYTE_ALIGNMENT    0x0000001F
#define MF_64_BYTE_ALIGNMENT    0x0000003F
#define MF_128_BYTE_ALIGNMENT   0x0000007F
#define MF_256_BYTE_ALIGNMENT   0x000000FF
#define MF_512_BYTE_ALIGNMENT   0x000001FF

HRESULT WINAPI MFCreateAlignedMemoryBuffer(DWORD cbMaxLength,DWORD fAlignmentFlags,IMFMediaBuffer **ppBuffer);
HRESULT WINAPI MFCreateASFContentInfo(IMFASFContentInfo **ppIContentInfo);
HRESULT WINAPI MFCreateASFIndexer(IMFASFIndexer **ppIIndexer);
HRESULT WINAPI MFCreateASFIndexerByteStream(IMFByteStream *pIContentByteStream,QWORD cbIndexStartOffset,IMFByteStream **pIIndexByteStream);
HRESULT WINAPI MFCreateASFMediaSink(IMFByteStream *pIByteStream,IMFMediaSink **ppIMediaSink);
HRESULT WINAPI MFCreateASFMediaSinkActivate(LPCWSTR pwszFileName,IMFASFContentInfo *pContentInfo,IMFActivate **ppIActivate);
HRESULT WINAPI MFCreateASFMultiplexer(IMFASFMultiplexer **ppIMultiplexer);
HRESULT WINAPI MFCreateASFProfile(IMFASFProfile **ppIProfile);
HRESULT WINAPI MFCreateASFProfileFromPresentationDescriptor(IMFPresentationDescriptor *pIPD,IMFASFProfile **ppIProfile);
HRESULT WINAPI MFCreateASFSplitter(IMFASFSplitter **ppISplitter);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_MFIDL*/
