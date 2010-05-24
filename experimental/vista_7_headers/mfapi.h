#ifndef _INC_MFAPI
#define _INC_MFAPI
#include <mfidl.h>

#if (_WIN32_WINNT >= 0x0600)

typedef enum  {
  MF_TOPOSTATUS_INVALID           = 0,
  MF_TOPOSTATUS_READY             = 100,
  MF_TOPOSTATUS_STARTED_SOURCE    = 200,
  MF_TOPOSTATUS_DYNAMIC_CHANGED   = 210,
  MF_TOPOSTATUS_SINK_SWITCHED     = 300,
  MF_TOPOSTATUS_ENDED             = 400 
} MF_TOPOSTATUS;

typedef enum _MFVideoDRMFlags {
  MFVideoDRMFlag_None                 = 0,
  MFVideoDRMFlag_AnalogProtected      = 1,
  MFVideoDRMFlag_DigitallyProtected   = 2 
} MFVideoDRMFlags;


#if (_WIN32_WINNT >= 0x0601)
typedef enum  {
  MF_STANDARD_WORKQUEUE   = 0,
  MF_WINDOW_WORKQUEUE     = 1 
} MFASYNC_WORKQUEUE_TYPE;
#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum _MFVideoPadFlags {
  MFVideoPadFlag_PAD_TO_None   = 0,
  MFVideoPadFlag_PAD_TO_4x3    = 1,
  MFVideoPadFlag_PAD_TO_16x9   = 2 
} MFVideoPadFlags;

typedef enum _MFVideoSrcContentHintFlags {
  MFVideoSrcContentHintFlag_None    = 0,
  MFVideoSrcContentHintFlag_16x9    = 1,
  MFVideoSrcContentHintFlag_235_1   = 2 
} MFVideoSrcContentHintFlags;

typedef enum _MFWaveFormatExConvertFlags {
  MFWaveFormatExConvertFlag_Normal            = 0,
  MFWaveFormatExConvertFlag_ForceExtensible   = 1 
} MFWaveFormatExConvertFlags;

#undef  INTERFACE
#define INTERFACE IMFAsyncCallback
DECLARE_INTERFACE_(IMFAsyncCallback,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IMFAsyncCallback methods */
    STDMETHOD_(HRESULT,GetParameters)(THIS_ DWORD *pdwFlags,DWORD *pdwQueue) PURE;
    STDMETHOD_(HRESULT,MFInvokeCallback)(THIS_ IMFAsyncResult *pAsyncResult) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IMFAsyncCallback_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IMFAsyncCallback_AddRef(This) (This)->pVtbl->AddRef(This)
#define IMFAsyncCallback_Release(This) (This)->pVtbl->Release(This)
#define IMFAsyncCallback_GetParameters(This,pdwFlags,pdwQueue) (This)->lpVtbl->GetParameters(This,pdwFlags,pdwQueue)
#define IMFAsyncCallback_MFInvokeCallback(This,pAsyncResult) (This)->lpVtbl->MFInvokeCallback(This,pAsyncResult)
#endif /*COBJMACROS*/

typedef void (*MFPERIODICCALLBACK )(IUnknown *pContext);
HRESULT WINAPI MFAddPeriodicCallback(MFPERIODICCALLBACK Callback,IUnknown *pContext,DWORD *pdwKey);
HRESULT WINAPI MFRemovePeriodicCallback(DWORD dwKey);
HRESULT WINAPI MFAllocateWorkQueue(DWORD *pdwWorkQueue);
HRESULT WINAPI MFAllocateWorkQueueEx(MFASYNC_WORKQUEUE_TYPE WorkQueueType,DWORD *pdwWorkQueue);
HRESULT WINAPI MFAverageTimePerFrameToFrameRate(UINT64 unAverageTimePerFrame,UINT32 *punNumerator,UINT32 *punDenominator);
HRESULT WINAPI MFBeginCreateFile(MF_FILE_ACCESSMODE AccessMode,MF_FILE_OPENMODE OpenMode,MF_FILE_FLAGS fFlags,LPCWSTR pwszFilePath,IMFAsyncCallback *pCallback,IUnknown *pState,IUnknown **ppCancelCookie);
HRESULT WINAPI MFBeginUnregisterWorkQueueWithMMCSS(DWORD dwWorkQueueId,IMFAsyncCallback *pDoneCallback,IUnknown *pDoneState);
HRESULT WINAPI MFBeginRegisterWorkQueueWithMMCSS(DWORD dwWorkQueueId,LPCWSTR wszClass,DWORD dwTaskId,IMFAsyncCallback *pDoneCallback,IUnknown *pDoneState);
HRESULT WINAPI MFBeginCreateFile(MF_FILE_ACCESSMODE AccessMode,MF_FILE_OPENMODE OpenMode,MF_FILE_FLAGS fFlags,LPCWSTR pwszFilePath,IMFAsyncCallback *pCallback,IUnknown *pState,IUnknown **ppCancelCookie);
HRESULT WINAPI MFCalculateBitmapImageSize(const BITMAPINFOHEADER *pBMIH,UINT32 cbBufSize,UINT32 *pcbImageSize,WINBOOL *pbKnown);
HRESULT WINAPI MFCalculateImageSize(REFGUID guidSubtype,UINT32 unWidth,UINT32 unHeight,UINT32 *pcbImageSize);
HRESULT WINAPI MFCancelCreateFile(IUnknown *pCancelCookie);
HRESULT WINAPI MFCancelWorkItem(MFWORKITEM_KEY Key);
WINBOOL WINAPI MFCompareFullToPartialMediaType(IMFMediaType *pMFTypeFull,IMFMediaType *pMFTypePartial);
HRESULT WINAPI MFConvertColorInfoFromDXVA(MFVIDEOFORMAT *pToFormat,DWORD dwFromDXVA);
HRESULT WINAPI MFConvertColorInfoToDXVA(DWORD *pdwToDXVA,const MFVIDEOFORMAT *pFromFormat);
HRESULT WINAPI MFConvertFromFP16Array(float *pDest,const WORD *pSrc,DWORD dwCount);
HRESULT WINAPI MFConvertToFP16Array(WORD *pDest,const float *pSrc,DWORD dwCount);
HRESULT WINAPI MFCopyImage(BYTE *pDest,LONG lDestStride,const BYTE *pSrc,LONG lSrcStride,DWORD dwWidthInBytes,DWORD dwLines);
HRESULT WINAPI MFCreateSample(IMFSample **ppIMFSample);
HRESULT WINAPI MFCreateMemoryBuffer(DWORD cbMaxLength,IMFMediaBuffer **ppBuffer);
HRESULT WINAPI MFCreateMediaBufferWrapper(IMFMediaBuffer *pBuffer,DWORD cbOffset,DWORD dwLength,IMFMediaBuffer **ppBuffer);
HRESULT WINAPI MFCreateDXSurfaceBuffer(REFIID riid,IUnknown *punkSurface,BOOL fBottomUpWhenLinear,IMFMediaBuffer **ppBuffer);
HRESULT WINAPI MFCreateAsyncResult(IUnknown *punkObject,IMFAsyncCallback *pCallback,IUnknown *punkState,IMFAsyncResult **ppAsyncResult);
HRESULT WINAPI MFCreateFile(MF_FILE_ACCESSMODE AccessMode,MF_FILE_OPENMODE OpenMode,MF_FILE_FLAGS fFlags,LPCWSTR pwszFileURL,IMFByteStream **ppIByteStream);
HRESULT WINAPI MFCreateTempFile(MF_FILE_ACCESSMODE AccessMode,MF_FILE_OPENMODE OpenMode,MF_FILE_FLAGS fFlags,IMFByteStream **ppIByteStream);

HRESULT WINAPI MFShutdown(void);
#ifndef __cplusplus
HRESULT WINAPI MFStartup(ULONG Version,DWORD dwFlags);
#else
extern "C" HRESULT WINAPI MFStartup(ULONG Version,DWORD dwFlags = MFSTARTUP_FULL);
#endif

#endif  /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_MFAPI*/
