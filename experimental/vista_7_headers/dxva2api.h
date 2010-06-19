#ifndef _INC_DXVA2API
#define _INC_DXVA2API
#include <windows.h>
#include <dshow.h>
#include <d3d9.h>
#if (_WIN32_WINNT >= 0x0600)

typedef struct IDirect3DDeviceManager9 IDirect3DDeviceManager9;

typedef enum _DXVA2_SampleFormat {
  DXVA2_SampleFormatMask                  = 0x00FF,
  DXVA2_SampleUnknown                     = 0,
  DXVA2_SampleProgressiveFrame            = 2,
  DXVA2_SampleFieldInterleavedEvenFirst   = 3,
  DXVA2_SampleFieldInterleavedOddFirst    = 4,
  DXVA2_SampleFieldSingleEven             = 5,
  DXVA2_SampleFieldSingleOdd              = 6,
  DXVA2_SampleSubStream                   = 7 
} DXVA2_SampleFormat;

typedef enum _DXVA2_VideoChromaSubSampling {
  DXVA2_VideoChromaSubsamplingMask                              = 0x0F,
  DXVA2_VideoChromaSubsampling_Unknown                          = 0,
  DXVA2_VideoChromaSubsampling_ProgressiveChroma                = 0x8,
  DXVA2_VideoChromaSubsampling_Horizontally_Cosited             = 0x4,
  DXVA2_VideoChromaSubsampling_Vertically_Cosited               = 0x2,
  DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes   = 0x1,
  DXVA2_VideoChromaSubsampling_MPEG2                            = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited |
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  DXVA2_VideoChromaSubsampling_MPEG1                            = 
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
  DXVA2_VideoChromaSubsampling_DV_PAL                           = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_Cosited,
  DXVA2_VideoChromaSubsampling_Cosited                          = 
              DXVA2_VideoChromaSubsampling_Horizontally_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_Cosited | 
              DXVA2_VideoChromaSubsampling_Vertically_AlignedChromaPlanes 
} DXVA2_VideoChromaSubSampling;

typedef enum _DXVA2_NominalRange {
  DXVA2_NominalRangeMask       = 0x07,
  DXVA2_NominalRange_Unknown   = 0,
  DXVA2_NominalRange_Normal    = 1,
  DXVA2_NominalRange_Wide      = 2,
  DXVA2_NominalRange_0_255     = 1,
  DXVA2_NominalRange_16_235    = 2,
  DXVA2_NominalRange_48_208    = 3 
} DXVA2_NominalRange;

typedef enum _DXVA2_VideoLighting {
  DXVA2_VideoLightingMask       = 0x0F,
  DXVA2_VideoLighting_Unknown   = 0,
  DXVA2_VideoLighting_bright    = 1,
  DXVA2_VideoLighting_office    = 2,
  DXVA2_VideoLighting_dim       = 3,
  DXVA2_VideoLighting_dark      = 4 
} DXVA2_VideoLighting;

typedef enum _DXVA2_VideoPrimaries {
  DXVA2_VideoPrimariesMask             = 0x001f,
  DXVA2_VideoPrimaries_Unknown         = 0,
  DXVA2_VideoPrimaries_reserved        = 1,
  DXVA2_VideoPrimaries_BT709           = 2,
  DXVA2_VideoPrimaries_BT470_2_SysM    = 3,
  DXVA2_VideoPrimaries_BT470_2_SysBG   = 4,
  DXVA2_VideoPrimaries_SMPTE170M       = 5,
  DXVA2_VideoPrimaries_SMPTE240M       = 6,
  DXVA2_VideoPrimaries_EBU3213         = 7,
  DXVA2_VideoPrimaries_SMPTE_C         = 8 
} DXVA2_VideoPrimaries;

typedef enum _DXVA2_VideoTransferFunction {
  DXVA2_VideoTransFuncMask       = 0x001f,
  DXVA2_VideoTransFunc_Unknown   = 0,
  DXVA2_VideoTransFunc_10        = 1,
  DXVA2_VideoTransFunc_18        = 2,
  DXVA2_VideoTransFunc_20        = 3,
  DXVA2_VideoTransFunc_22        = 4,
  DXVA2_VideoTransFunc_709       = 5,
  DXVA2_VideoTransFunc_240M      = 6,
  DXVA2_VideoTransFunc_sRGB      = 7,
  DXVA2_VideoTransFunc_28        = 8 
} DXVA2_VideoTransferFunction;

typedef enum  {
  DXVA2_SurfaceType_DecoderRenderTarget      = 0,
  DXVA2_SurfaceType_ProcessorRenderTarget    = 1,
  DXVA2_SurfaceType_D3DRenderTargetTexture   = 2 
} DXVA2_SurfaceType;

typedef struct _DXVA2_AYUVSample16 {
  USHORT Cr;
  USHORT Cb;
  USHORT Y;
  USHORT Alpha;
} DXVA2_AYUVSample16;

typedef struct _DXVA2_AYUVSample8 {
  UCHAR Cr;
  UCHAR Cb;
  UCHAR Y;
  UCHAR Alpha;
} DXVA2_AYUVSample8;

typedef struct _DXVA2_ConfigPictureDecode {
  GUID   guidConfigBitstreamEncryption;
  GUID   guidConfigMBcontrolEncryption;
  GUID   guidConfigResidDiffEncryption;
  UINT   ConfigBitstreamRaw;
  UINT   ConfigMBcontrolRasterOrder;
  UINT   ConfigResidDiffHost;
  UINT   ConfigSpatialResid8;
  UINT   ConfigResid8Subtraction;
  UINT   ConfigSpatialHost8or9Clipping;
  UINT   ConfigSpatialResidInterleaved;
  UINT   ConfigIntraResidUnsigned;
  UINT   ConfigResidDiffAccelerator;
  UINT   ConfigHostInverseScan;
  UINT   ConfigSpecificIDCT;
  UINT   Config4GroupedCoefs;
  UINT   ConfigMinRenderTargetBuffCount;
  USHORT ConfigDecoderSpecific;
} DXVA2_ConfigPictureDecode;

/* CompressedBufferType
DXVA2_PictureParametersBufferType
DXVA2_MacroBlockControlBufferType
DXVA2_ResidualDifferenceBufferType
DXVA2_DeblockingControlBufferType
DXVA2_InverseQuantizationMatrixBufferType
DXVA2_SliceControlBufferType
DXVA2_BitStreamDateBufferType
DXVA2_MotionVectorBuffer
DXVA2_FilmGrainBuffer
*/
typedef struct _DXVA2_DecodeBufferDesc {
  DWORD CompressedBufferType;
  UINT  BufferIndex;
  UINT  DataOffset;
  UINT  DataSize;
  UINT  FirstMBaddress;
  UINT  NumMBsInBuffer;
  UINT  Width;
  UINT  Height;
  UINT  Stride;
  UINT  ReservedBits;
  PVOID pvPVPState;
} DXVA2_DecodeBufferDesc;

typedef struct _DXVA2_DecodeExtensionData {
  UINT  Function;
  PVOID pPrivateInputData;
  UINT  PrivateInputDataSize;
  PVOID pPrivateOutputData;
  UINT  PrivateOutputDataSize;
} DXVA2_DecodeExtensionData;

typedef struct _DXVA2_DecodeExecuteParams {
  UINT                      NumCompBuffers;
  DXVA2_DecodeBufferDesc    *pCompressedBuffers;
  DXVA2_DecodeExtensionData *pExtensionData;
} DXVA2_DecodeExecuteParams;

typedef struct _DXVA2_ExtendedFormat {
  __MINGW_EXTENSION union {
    __MINGW_EXTENSION struct {
      UINT SampleFormat  :8;
      UINT VideoChromaSubsampling  :4;
      UINT NominalRange  :3;
      UINT VideoTransferMatrix  :3;
      UINT VideoLighting  :4;
      UINT VideoPrimaries  :5;
      UINT VideoTransferFunction  :5;
    } DUMMYSTRUCTNAME;
    UINT   value;
  } DUMMYUNIONNAME;
} DXVA2_ExtendedFormat;

typedef struct _DXVA2_Fixed32 {
  __MINGW_EXTENSION union {
    __MINGW_EXTENSION struct {
      USHORT Fraction;
      SHORT  Value;
    } DUMMYSTRUCTNAME;
    LONG   ll;
  } DUMMYUNIONNAME;
} DXVA2_Fixed32;

typedef struct _DXVA2_FilterValues {
  DXVA2_Fixed32 Level;
  DXVA2_Fixed32 Threshold;
  DXVA2_Fixed32 Radius;
} DXVA2_FilterValues;

typedef struct _DXVA2_Frequency {
  UINT Numerator;
  UINT Denominator;
} DXVA2_Frequency;

typedef struct _DXVA2_ProcAmpValues {
  DXVA2_Fixed32 Brightness;
  DXVA2_Fixed32 Contrast;
  DXVA2_Fixed32 Hue;
  DXVA2_Fixed32 Saturation;
} DXVA2_ProcAmpValues;

typedef struct _DXVA2_ValueRange {
  DXVA2_Fixed32 MinValue;
  DXVA2_Fixed32 MaxValue;
  DXVA2_Fixed32 DefaultValue;
  DXVA2_Fixed32 StepSize;
} DXVA2_ValueRange;

typedef struct _DXVA2_VideoDesc {
  UINT                 SampleWidth;
  UINT                 SampleHeight;
  DXVA2_ExtendedFormat SampleFormat;
  D3DFORMAT            Format;
  DXVA2_Frequency      InputSampleFreq;
  DXVA2_Frequency      OutputFrameFreq;
  UINT                 UABProtectionLevel;
  UINT                 Reserved;
} DXVA2_VideoDesc;

/* DeviceCaps
DXVA2_VPDev_EmulatedDXVA1
DXVA2_VPDev_HardwareDevice
DXVA2_VPDev_SoftwareDevice
*/
/* DeinterlaceTechnology
DXVA2_DeinterlaceTech_Unknown
DXVA2_DeinterlaceTech_BOBLineReplicate
DXVA2_DeinterlaceTech_BOBVerticalStretch
DXVA2_DeinterlaceTech_BOBVerticalStretch4Tap
DXVA2_DeinterlaceTech_MedianFiltering
DXVA2_DeinterlaceTech_EdgeFiltering
DXVA2_DeinterlaceTech_FieldAdaptive
DXVA2_DeinterlaceTech_PixelAdaptive
DXVA2_DeinterlaceTech_MotionVectorSteered
DXVA2_DeinterlaceTech_InverseTelecine
*/

/* VideoProcessorOperations
DXVA2_VideoProcess_YUV2RGB
DXVA2_VideoProcess_StretchX
DXVA2_VideoProcess_StretchY
DXVA2_VideoProcess_AlphaBlend
DXVA2_VideoProcess_SubRects
DXVA2_VideoProcess_SubStreams
DXVA2_VideoProcess_SubStreamsExtended
DXVA2_VideoProcess_YUV2RGBExtended
DXVA2_VideoProcess_AlphaBlendExtended
DXVA2_VideoProcess_Constriction
DXVA2_VideoProcess_NoiseFilter
DXVA2_VideoProcess_DetailFilter
DXVA2_VideoProcess_PlanarAlpha
DXVA2_VideoProcess_LinearScaling
DXVA2_VideoProcess_GammaCompensated
DXVA2_VideoProcess_MaintainsOriginalFieldData
*/

/*NoiseFilterTechnology
DXVA2_NoiseFilterTech_Unsupported
DXVA2_NoiseFilterTech_Unknown
DXVA2_NoiseFilterTech_Median
DXVA2_NoiseFilterTech_Temporal
DXVA2_NoiseFilterTech_BlockNoise
DXVA2_NoiseFilterTech_MosquitoNoise
*/

/* DetailFilterTechnology
DXVA2_DetailFilterTech_Unsupported
DXVA2_DetailFilterTech_Unknown
DXVA2_DetailFilterTech_Edge
DXVA2_DetailFilterTech_Sharpening
*/
typedef struct _DXVA2_VideoProcessorCaps {
  UINT    DeviceCaps;
  D3DPOOL InputPool;
  UINT    NumForwardRefSamples;
  UINT    NumBackwardRefSamples;
  UINT    Reserved;
  UINT    DeinterlaceTechnology;
  UINT    ProcAmpControlCaps;
  UINT    VideoProcessorOperations;
  UINT    NoiseFilterTechnology;
  UINT    DetailFilterTechnology;
} DXVA2_VideoProcessorCaps;

/* SampleData
DXVA2_SampleData_RFF
DXVA2_SampleData_TFF
DXVA2_SampleData_RFF_TFF_Present
*/

typedef struct _DXVA2_VideoSample {
  REFERENCE_TIME       Start;
  REFERENCE_TIME       End;
  DXVA2_ExtendedFormat SampleFormat;
  IDirect3DSurface9*   SrcSurface;
  RECT                 SrcRect;
  RECT                 DstRect;
  DXVA2_AYUVSample8    Pal[16];
  DXVA2_Fixed32        PlanarAlpha;
  DWORD                SampleData;
} DXVA2_VideoSample;

/*inlines?*/
const DXVA2_Fixed32 DXVA2_Fixed32OpaqueAlpha(void);
const DXVA2_Fixed32 DXVA2_Fixed32TransparentAlpha(void);
float DXVA2FixedToFloat(const DXVA2_Fixed32 _fixed_);
DXVA2_Fixed32 DXVA2FloatToFixed(const float _float_);

HRESULT WINAPI DXVA2CreateDirect3DDeviceManager9(UINT *pResetToken,IDirect3DDeviceManager9 **ppDXVAManager);
HRESULT WINAPI DXVA2CreateVideoService(IDirect3DDevice9 *pDD,REFIID riid,void **ppService);

#undef  INTERFACE
#define INTERFACE IDirect3DDeviceManager9
DECLARE_INTERFACE_(IDirect3DDeviceManager9,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDirect3DDeviceManager9 methods */
    STDMETHOD_(HRESULT,CloseDeviceHandle)(THIS_ HANDLE hDevice) PURE;
    STDMETHOD_(HRESULT,GetVideoService)(THIS_ HANDLE hDevice,REFIID riid,void **ppService) PURE;
    STDMETHOD_(HRESULT,LockDevice)(THIS_ HANDLE hDevice,IDirect3DDevice9 **ppDevice,WINBOOL fBlock) PURE;
    STDMETHOD_(HRESULT,OpenDeviceHandle)(THIS_ HANDLE *phDevice) PURE;
    STDMETHOD_(HRESULT,ResetDevice)(THIS_ IDirect3DDevice9 *pDevice,UINT resetToken) PURE;
    STDMETHOD_(HRESULT,TestDevice)(THIS_ HANDLE hDevice) PURE;
    STDMETHOD_(HRESULT,UnlockDevice)(THIS_ HANDLE hDevice,BOOL fSaveState) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IDirect3DDeviceManager9_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IDirect3DDeviceManager9_AddRef(This) (This)->pVtbl->AddRef(This)
#define IDirect3DDeviceManager9_Release(This) (This)->pVtbl->Release(This)
#define IDirect3DDeviceManager9_CloseDeviceHandle(This,hDevice) (This)->lpVtbl->CloseDeviceHandle(This,hDevice)
#define IDirect3DDeviceManager9_GetVideoService(This,hDevice,riid,ppService) (This)->lpVtbl->GetVideoService(This,hDevice,riid,ppService)
#define IDirect3DDeviceManager9_LockDevice(This,hDevice,ppDevice,fBlock) (This)->lpVtbl->LockDevice(This,hDevice,ppDevice,fBlock)
#define IDirect3DDeviceManager9_OpenDeviceHandle(This,phDevice) (This)->lpVtbl->OpenDeviceHandle(This,phDevice)
#define IDirect3DDeviceManager9_ResetDevice(This,pDevice,resetToken) (This)->lpVtbl->ResetDevice(This,pDevice,resetToken)
#define IDirect3DDeviceManager9_TestDevice(This,hDevice) (This)->lpVtbl->TestDevice(This,hDevice)
#define IDirect3DDeviceManager9_UnlockDevice(This,hDevice,fSaveState) (This)->lpVtbl->UnlockDevice(This,hDevice,fSaveState)
#endif /*COBJMACROS*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_DXVA2API*/
