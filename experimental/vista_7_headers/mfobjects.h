#ifndef _INC_EVR
#define _INC_EVR

#if (_WIN32_WINNT >= 0x0600)

#ifdef __IMFAttributes_FWD_DEFINED__
#define __IMFAttributes_FWD_DEFINED__
typedef struct IMFAttributes IMFAttributes;
#endif

#ifdef __IMFASFSplitter_FWD_DEFINED__
#define __IMFASFSplitter_FWD_DEFINED__
typedef struct IMFMediaBuffer IMFMediaBuffer;
#endif

enum MF_ATTRIBUTE_SERIALIZE_OPTIONS {
  MF_ATTRIBUTE_SERIALIZE_UNKNOWN_BYREF   = 0x00000001 
};

typedef enum _MF_ATTRIBUTE_TYPE {
  MF_ATTRIBUTE_UINT32     = VT_UI4,
  MF_ATTRIBUTE_UINT64     = VT_UI8,
  MF_ATTRIBUTE_DOUBLE     = VT_R8,
  MF_ATTRIBUTE_GUID       = VT_CLSID,
  MF_ATTRIBUTE_STRING     = VT_LPWSTR,
  MF_ATTRIBUTE_BLOB       = VT_VECTOR | VT_UI1,
  MF_ATTRIBUTE_IUNKNOWN   = VT_UNKNOWN 
} MF_ATTRIBUTE_TYPE;

typedef enum _MF_ATTRIBUTES_MATCH_TYPE {
  MF_ATTRIBUTES_MATCH_OUR_ITEMS      = 0,
  MF_ATTRIBUTES_MATCH_THEIR_ITEMS    = 1,
  MF_ATTRIBUTES_MATCH_ALL_ITEMS      = 2,
  MF_ATTRIBUTES_MATCH_INTERSECTION   = 3,
  MF_ATTRIBUTES_MATCH_SMALLER        = 4 
} MF_ATTRIBUTES_MATCH_TYPE;

typedef enum _MF_CONNECT_METHOD {
  MF_CONNECT_DIRECT                            = 0x00000000,
  MF_CONNECT_ALLOW_CONVERTER                   = 0x00000001,
  MF_CONNECT_ALLOW_DECODER                     = 0x00000003,
  MF_CONNECT_RESOLVE_INDEPENDENT_OUTPUTTYPES   = 0x00000004,
  MF_CONNECT_AS_OPTIONAL                       = 0x00010000,
  MF_CONNECT_AS_OPTIONAL_BRANCH                = 0x00020000 
} MF_CONNECT_METHOD;

typedef enum MF_FILE_ACCESSMODE {
  MF_ACCESSMODE_READ        = 1,
  MF_ACCESSMODE_WRITE       = 2,
  MF_ACCESSMODE_READWRITE   = 3 
} ;

typedef enum  {
  MF_FILEFLAGS_NONE                  = 0x00000000,
  MF_FILEFLAGS_NOBUFFERING           = 0x00000001,
  MF_FILEFLAGS_ALLOW_WRITE_SHARING   = 0x00000002 
} MF_FILE_FLAGS;

typedef enum  {
  MF_OPENMODE_FAIL_IF_NOT_EXIST   = 0,
  MF_OPENMODE_FAIL_IF_EXIST       = 1,
  MF_OPENMODE_RESET_IF_EXIST      = 2,
  MF_OPENMODE_APPEND_IF_EXIST     = 3,
  MF_OPENMODE_DELETE_IF_EXIST     = 4 
} MF_FILE_OPENMODE;

typedef enum MF_OBJECT_TYPE {
  MF_OBJECT_MEDIASOURCE,
  MF_OBJECT_BYTESTREAM,
  MF_OBJECT_INVALID 
} MF_OBJECT_TYPE;

#if (_WIN32_WINNT >= 0x0601)

typedef enum _MF_Plugin_Type {
  MF_Plugin_Type_MFT           = 0,
  MF_Plugin_Type_MediaSource   = 1 
} MF_Plugin_Type;

#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum _MFBYTESTREAM_SEEK_ORIGIN {
  msoBegin,
  msoCurrent 
} MFBYTESTREAM_SEEK_ORIGIN;

typedef enum _MFNominalRange {
  MFNominalRange_Unknown   = 0,
  MFNominalRange_Normal    = 1,
  MFNominalRange_Wide      = 2,
  MFNominalRange_0_255     = 1,
  MFNominalRange_16_235    = 2,
  MFNominalRange_48_208    = 3,
  MFNominalRange_64_127    = 4 
} MFNominalRange;

typedef enum _MFStandardVideoFormat {
  MFStdVideoFormat_reserved       = 0,
  MFStdVideoFormat_NTSC,
  MFStdVideoFormat_PAL,
  MFStdVideoFormat_DVD_NTSC,
  MFStdVideoFormat_DVD_PAL,
  MFStdVideoFormat_DV_PAL,
  MFStdVideoFormat_DV_NTSC,
  MFStdVideoFormat_ATSC_SD480i,
  MFStdVideoFormat_ATSC_HD1080i,
  MFStdVideoFormat_ATSC_HD720p 
} MFStandardVideoFormat;

typedef enum _MFVideoChromaSubsampling {
  MFVideoChromaSubsampling_Unknown                          = 0,
  MFVideoChromaSubsampling_ProgressiveChroma                = 0x8,
  MFVideoChromaSubsampling_Horizontally_Cosited             = 0x4,
  MFVideoChromaSubsampling_Vertically_Cosited               = 0x2,
  MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes   = 0x1,
  MFVideoChromaSubsampling_MPEG2                            = 
    MFVideoChromaSubsampling_Horizontally_Cosited | 
    MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  MFVideoChromaSubsampling_MPEG1                            = 
    MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  MFVideoChromaSubsampling_DV_PAL                           = 
    MFVideoChromaSubsampling_Horizontally_Cosited | 
    MFVideoChromaSubsampling_Vertically_Cosited,
  MFVideoChromaSubsampling_Cosited                          = 
    MFVideoChromaSubsampling_Horizontally_Cosited | 
    MFVideoChromaSubsampling_Vertically_Cosited | 
    MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  MFVideoChromaSubsampling_Last                             = MFVideoChromaSubsampling_Cosited + 1,
  MFVideoChromaSubsampling_ForceDWORD                       = 0x7FFFFFFF 
} MFVideoChromaSubsampling;

typedef enum _MFVideoInterlaceMode {
  MFVideoInterlace_Unknown                       = 0,
  MFVideoInterlace_Progressive                   = 2,
  MFVideoInterlace_FieldInterleavedUpperFirst    = 3,
  MFVideoInterlace_FieldInterleavedLowerFirst    = 4,
  MFVideoInterlace_FieldSingleUpper              = 5,
  MFVideoInterlace_FieldSingleLower              = 6,
  MFVideoInterlace_MixedInterlaceOrProgressive   = 7,
  MFVideoInterlace_Last,
  MFVideoInterlace_ForceDWORD                    = 0x7FFFFFFF 
} MFVideoInterlaceMode;

typedef enum _MFVideoLighting {
  MFVideoLighting_Unknown      = 0,
  MFVideoLighting_bright       = 1,
  MFVideoLighting_office       = 2,
  MFVideoLighting_dim          = 3,
  MFVideoLighting_dark         = 4,
  MFVideoLighting_Last,
  MFVideoLighting_ForceDWORD   = 0x7FFFFFFF 
} MFVideoLighting;

typedef enum _MFVideoPrimaries {
  MFVideoPrimaries_Unknown         = 0,
  MFVideoPrimaries_reserved        = 1,
  MFVideoPrimaries_BT709           = 2,
  MFVideoPrimaries_BT470_2_SysM    = 3,
  MFVideoPrimaries_BT470_2_SysBG   = 4,
  MFVideoPrimaries_SMPTE170M       = 5,
  MFVideoPrimaries_SMPTE240M       = 6,
  MFVideoPrimaries_EBU3213         = 7,
  MFVideoPrimaries_SMPTE_C         = 8,
  MFVideoPrimaries_Last,
  MFVideoPrimaries_ForceDWORD      = 0x7FFFFFFF 
} MFVideoPrimaries;

typedef enum _MFVideoTransferMatrix {
  MFVideoTransferMatrix_Unknown      = 0,
  MFVideoTransferMatrix_BT709        = 1,
  MFVideoTransferMatrix_BT601        = 2,
  MFVideoTransferMatrix_SMPTE240M    = 3,
  MFVideoTransferMatrix_Last,
  MFVideoTransferMatrix_ForceDWORD   = 0x7FFFFFFF 
} MFVideoTransferMatrix;

typedef struct _MFRatio {
  DWORD Numerator;
  DWORD Denominator;
} MFRatio;

typedef struct _MFOffset {
  WORD  fract;
  short value;
} MFOffset;

typedef struct _MFVideoArea {
  MFOffset OffsetX;
  MFOffset OffsetY;
  SIZE     Area;
} MFVideoArea;

typedef enum _MFVideoFlags {
  MFVideoFlag_PAD_TO_Mask             = 0x0001 | 0x0002,
  MFVideoFlag_PAD_TO_None             = 0 * 0x0001,
  MFVideoFlag_PAD_TO_4x3              = 1 * 0x0001,
  MFVideoFlag_PAD_TO_16x9             = 2 * 0x0001,
  MFVideoFlag_SrcContentHintMask      = 0x0004 | 0x0008 | 0x0010,
  MFVideoFlag_SrcContentHintNone      = 0 * 0x0004,
  MFVideoFlag_SrcContentHint16x9      = 1 * 0x0004,
  MFVideoFlag_SrcContentHint235_1     = 2 * 0x0004,
  MFVideoFlag_AnalogProtected         = 0x0020,
  MFVideoFlag_DigitallyProtected      = 0x0040,
  MFVideoFlag_ProgressiveContent      = 0x0080,
  MFVideoFlag_FieldRepeatCountMask    = 0x0100 | 0x0200 | 0x0400,
  MFVideoFlag_FieldRepeatCountShift   = 8,
  MFVideoFlag_ProgressiveSeqReset     = 0x0800,
  MFVideoFlag_PanScanEnabled          = 0x20000,
  MFVideoFlag_LowerFieldFirst         = 0x40000,
  MFVideoFlag_BottomUpLinearRep       = 0x80000,
  MFVideoFlags_DXVASurface            = 0x100000,
  MFVideoFlags_RenderTargetSurface    = 0x400000,
  MFVideoFlags_ForceQWORD             = 0x7FFFFFFF 
} MFVideoFlags;

typedef struct _MFVideoCompressedInfo {
  LONGLONG AvgBitrate;
  LONGLONG AvgBitErrorRate;
  DWORD    MaxKeyFrameSpacing;
} MFVideoCompressedInfo;

typedef struct _MFVideoInfo {
  DWORD                    dwWidth;
  DWORD                    dwHeight;
  MFRatio                  PixelAspectRatio;
  MFVideoChromaSubsampling SourceChromaSubsampling;
  MFVideoInterlaceMode     InterlaceMode;
  MFVideoTransferFunction  TransferFunction;
  MFVideoPrimaries         ColorPrimaries;
  MFVideoTransferMatrix    TransferMatrix;
  MFVideoLighting          SourceLighting;
  MFRatio                  FramesPerSecond;
  MFNominalRange           NominalRange;
  MFVideoArea              GeometricAperture;
  MFVideoArea              MinimumDisplayAperture;
  MFVideoArea              PanScanAperture;
  unsigned __int64         VideoFlags;
} MFVideoInfo;

typedef struct _MFVideoSurfaceInfo {
  DWORD          Format;
  DWORD          PaletteEntries;
  MFPaletteEntry Palette[];
} MFVideoSurfaceInfo;

typedef struct _MFVIDEOFORMAT {
  DWORD                 dwSize;
  MFVideoInfo           videoInfo;
  GUID                  guidFormat;
  MFVideoCompressedInfo compressedInfo;
  MFVideoSurfaceInfo    surfaceInfo;
} MFVIDEOFORMAT;

/* 
   IMFAttributes interface

#define IMFAttributes_Compare(This,pTheirs,MatchType,pbResult) (This)->lpVtbl->Compare(This,pTheirs,MatchType,pbResult)
#define IMFAttributes_CompareItem(This,guidKey,Value,pbResult) (This)->lpVtbl->CompareItem(This,guidKey,Value,pbResult)
#define IMFAttributes_CopyAllItems(This,pDest) (This)->lpVtbl->CopyAllItems(This,pDest)
#define IMFAttributes_DeleteAllItems(This) (This)->lpVtbl->DeleteAllItems(This)
#define IMFAttributes_DeleteItem(This,guidKey) (This)->lpVtbl->DeleteItem(This,guidKey)
#define IMFAttributes_GetAllocatedBlob(This,guidKey,ppBuf,pcbSize) (This)->lpVtbl->GetAllocatedBlob(This,guidKey,ppBuf,pcbSize)
#define IMFAttributes_GetAllocatedString(This,guidKey,ppwszValue,pcchLength) (This)->lpVtbl->GetAllocatedString(This,guidKey,ppwszValue,pcchLength)
#define IMFAttributes_GetBlob(This,guidKey,pBuf,cbBufSize,pcbBlobSize) (This)->lpVtbl->GetBlob(This,guidKey,pBuf,cbBufSize,pcbBlobSize)
#define IMFAttributes_GetBlobSize(This,guidKey,pcbBlobSize) (This)->lpVtbl->GetBlobSize(This,guidKey,pcbBlobSize)
#define IMFAttributes_GetCount(This,pcItems) (This)->lpVtbl->GetCount(This,pcItems)
#define IMFAttributes_GetDouble(This,guidKey,pfValue) (This)->lpVtbl->GetDouble(This,guidKey,pfValue)
#define IMFAttributes_GetGUID(This,guidKey,pguidValue) (This)->lpVtbl->GetGUID(This,guidKey,pguidValue)
#define IMFAttributes_GetItem(This,guidKey,pValue) (This)->lpVtbl->GetItem(This,guidKey,pValue)
#define IMFAttributes_GetItemByIndex(This,unIndex,pguidKey,pValue) (This)->lpVtbl->GetItemByIndex(This,unIndex,pguidKey,pValue)
#define IMFAttributes_GetItemType(This,guidKey,pType) (This)->lpVtbl->GetItemType(This,guidKey,pType)
#define IMFAttributes_GetString(This,guidKey,pwszValue,cchBufSize,pcchLength) (This)->lpVtbl->GetString(This,guidKey,pwszValue,cchBufSize,pcchLength)
#define IMFAttributes_GetStringLength(This,guidKey,pcchLength) (This)->lpVtbl->GetStringLength(This,guidKey,pcchLength)
#define IMFAttributes_GetUINT32(This,guidKey,punValue) (This)->lpVtbl->GetUINT32(This,guidKey,punValue)
#define IMFAttributes_GetUINT64(This,guidKey,punValue) (This)->lpVtbl->GetUINT64(This,guidKey,punValue)
#define IMFAttributes_GetUnknown(This,guidKey,riid,ppv) (This)->lpVtbl->GetUnknown(This,guidKey,riid,ppv)
#define IMFAttributes_LockStore(This) (This)->lpVtbl->LockStore(This)
#define IMFAttributes_SetBlob(This,guidKey,pBuf,cbBufSize) (This)->lpVtbl->SetBlob(This,guidKey,pBuf,cbBufSize)
#define IMFAttributes_SetDouble(This,guidKey,fValue) (This)->lpVtbl->SetDouble(This,guidKey,fValue)
#define IMFAttributes_SetGUID(This,guidKey,guidValue) (This)->lpVtbl->SetGUID(This,guidKey,guidValue)
#define IMFAttributes_SetItem(This,guidKey,Value) (This)->lpVtbl->SetItem(This,guidKey,Value)
#define IMFAttributes_SetString(This,guidKey,wszValue) (This)->lpVtbl->SetString(This,guidKey,wszValue)
#define IMFAttributes_SetUINT32(This,guidKey,unValue) (This)->lpVtbl->SetUINT32(This,guidKey,unValue)
#define IMFAttributes_SetUINT64(This,guidKey,unValue) (This)->lpVtbl->SetUINT64(This,guidKey,unValue)
#define IMFAttributes_SetUnknown(This,guidKey,pUnknown) (This)->lpVtbl->(This,guidKey,pUnknown)
#define IMFAttributes_UnlockStore(This) (This)->lpVtbl->UnlockStore(This)


   IMFMediaBuffer interface

#define IMFMediaBuffer_GetCurrentLength(This,pcbCurrentLength) (This)->lpVtbl->GetCurrentLength(This,pcbCurrentLength)
#define IMFMediaBuffer_GetMaxLength(This,pcbMaxLength) (This)->lpVtbl->GetMaxLength(This,pcbMaxLength)
#define IMFMediaBuffer_Lock(This,ppbBuffer,pcbMaxLength,pcbCurrentLength) (This)->lpVtbl->Lock(This,ppbBuffer,pcbMaxLength,pcbCurrentLength)
#define IMFMediaBuffer_SetCurrentLength(This,cbCurrentLength) (This)->lpVtbl->SetCurrentLength(This,cbCurrentLength)
#define IMFMediaBuffer_Unlock(This) (This)->lpVtbl->Unlock(This)


*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EVR*/
