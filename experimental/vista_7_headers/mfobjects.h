#ifndef _INC_EVR
#define _INC_EVR

#if (_WIN32_WINNT >= 0x0600)

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


#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EVR*/
