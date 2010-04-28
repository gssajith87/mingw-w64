#ifndef _INC_WMCONTAINER
#define _INC_WMCONTAINER
#include <objbase.h>

#if (_WIN32_WINNT >= 0x0600)

#ifdef __IMFASFSplitter_FWD_DEFINED__
#define __IMFASFSplitter_FWD_DEFINED__
typedef struct IMFASFSplitter IMFASFSplitter;
#endif

#ifdef __IMFASFSplitter_FWD_DEFINED__
#define __IMFASFSplitter_FWD_DEFINED__
typedef struct IMFMediaBuffer IMFMediaBuffer;
#endif

#ifdef __IMFAttributes_FWD_DEFINED__
#define __IMFAttributes_FWD_DEFINED__
typedef struct IMFAttributes IMFAttributes;
#endif

typedef enum ASF_SELECTION_STATUS {
  ASF_STATUS_NOTSELECTED       = 0,
  ASF_STATUS_CLEANPOINTSONLY   = 1,
  ASF_STATUS_ALLDATAUNITS      = 2 
} ASF_SELECTION_STATUS;

typedef enum ASF_STATUSFLAGS {
  ASF_STATUSFLAGS_INCOMPLETE       = 0x00000001,
  ASF_STATUSFLAGS_NONFATAL_ERROR   = 0x00000002 
} ASF_STATUSFLAGS;

typedef enum MFASF_MULTIPLEXERFLAGS {
  MFASF_MULTIPLEXER_AUTOADJUST_BITRATE   = 0x00000001 
} ;

typedef enum MFASF_SPLITTERFLAGS {
  MFASF_SPLITTER_REVERSE   = 0x00000001,
  MFASF_SPLITTER_WMDRM     = 0x00000002 
} ;

typedef enum MFASF_STREAMSELECTORFLAGS {
  MFASF_STREAMSELECTOR_DISABLE_THINNING      = 0x00000001,
  MFASF_STREAMSELECTOR_USE_AVERAGE_BITRATE   = 0x00000002 
} ;

#ifdef __IMFAttributes_INTERFACE_DEFINED__
#define __IMFAttributes_INTERFACE_DEFINED__
typedef IMFAttributes *LPIMFATTRIBUTES;
#if defined(__cplusplus) && !defined(CINTERFACE)
DECLARE_INTERFACE_(IMFAttributes,IUnknown) {
public:
  virtual HRESULT WINAPI Compare(IMFAttributes *pTheirs,MF_ATTRIBUTES_MATCH_TYPE MatchType,WINBOOL *pbResult) PURE;
  virtual HRESULT WINAPI CompareItem(REFGUID guidKey,REFPROPVARIANT Value,WINBOOL *pbResult) PURE;
  virtual HRESULT WINAPI CopyAllItems(IMFAttributes *pDest) PURE;
  virtual HRESULT WINAPI DeleteAllItems() PURE;
  virtual HRESULT WINAPI DeleteItem(REFGUID guidKey) PURE;
  virtual HRESULT WINAPI GetAllocatedBlob(REFGUID guidKey,UINT8 **ppBuf,UINT32 *pcbSize) PURE;
  virtual HRESULT WINAPI GetAllocatedString(REFGUID guidKey,LPWSTR *ppwszValue,UINT32 *pcchLength) PURE;
  virtual HRESULT WINAPI GetBlob(REFGUID guidKey,UINT8 *pBuf,UINT32 cbBufSize,UINT32 *pcbBlobSize) PURE;
  virtual HRESULT WINAPI GetBlobSize(REFGUID guidKey,UINT32 *pcbBlobSize) PURE;
  virtual HRESULT WINAPI GetCount(UINT32 *pcItems) PURE;
  virtual HRESULT WINAPI GetDouble(REFGUID guidKey,double *pfValue) PURE;
  virtual HRESULT WINAPI GetGUID(REFGUID guidKey,GUID *pguidValue) PURE;
  virtual HRESULT WINAPI GetItem(REFGUID guidKey,PROPVARIANT *pValue) PURE;
  virtual HRESULT WINAPI GetItemByIndex(UINT32 unIndex,GUID *pguidKey,PROPVARIANT *pValue) PURE;
  virtual HRESULT WINAPI GetItemType(REFGUID guidKey,MF_ATTRIBUTE_TYPE *pType) PURE;
  virtual HRESULT WINAPI GetString(REFGUID guidKey,LPWSTR pwszValue,UINT32 cchBufSize,UINT32 *pcchLength) PURE;
  virtual HRESULT WINAPI GetStringLength(REFGUID guidKey,UINT32 *pcchLength) PURE;
  virtual HRESULT WINAPI GetUINT32(REFGUID guidKey,UINT32 *punValue) PURE;
  virtual HRESULT WINAPI GetUINT64(REFGUID guidKey,UINT64 *punValue) PURE;
  virtual HRESULT WINAPI GetUnknown(REFGUID guidKey,REFIID riid,LPVOID *ppv) PURE;
  virtual HRESULT WINAPI LockStore() PURE;
  virtual HRESULT WINAPI SetBlob(REFGUID guidKey,const UINT8 *pBuf,UINT32 cbBufSize) PURE;
  virtual HRESULT WINAPI SetDouble(REFGUID guidKey,double fValue) PURE;
  virtual HRESULT WINAPI SetGUID(REFGUID guidKey,REFGUID guidValue) PURE;
  virtual HRESULT WINAPI SetItem(REFGUID guidKey,REFPROPVARIANT Value) PURE;
  virtual HRESULT WINAPI SetString(REFGUID guidKey,LPCWSTR wszValue) PURE;
  virtual HRESULT WINAPI SetUINT32(REFGUID guidKey,UINT32 unValue) PURE;
  virtual HRESULT WINAPI SetUINT64(REFGUID guidKey,UINT64 unValue) PURE;
  virtual HRESULT WINAPI SetUnknown(REFGUID guidKey,IUnknown *pUnknown) PURE;
  virtual HRESULT WINAPI UnlockStore() PURE;
};
#else /*defined(__cplusplus) && !defined(CINTERFACE)*/
typedef struct IMFAttributesVtbl {
  BEGIN_INTERFACE
    HRESULT (WINAPI *Compare)(IMFAttributes *This,IMFAttributes *pTheirs,MF_ATTRIBUTES_MATCH_TYPE MatchType,WINBOOL *pbResult);
    HRESULT (WINAPI *CompareItem)(IMFAttributes *This,REFGUID guidKey,REFPROPVARIANT Value,WINBOOL *pbResult);
    HRESULT (WINAPI *CopyAllItems)(IMFAttributes *This,IMFAttributes *pDest);
    HRESULT (WINAPI *DeleteAllItems)(IMFAttributes *This);
    HRESULT (WINAPI *DeleteItem)(IMFAttributes *This,REFGUID guidKey);
    HRESULT (WINAPI *GetAllocatedBlob)(IMFAttributes *This,REFGUID guidKey,UINT8 **ppBuf,UINT32 *pcbSize);
    HRESULT (WINAPI *GetAllocatedString)(IMFAttributes *This,REFGUID guidKey,LPWSTR *ppwszValue,UINT32 *pcchLength);
    HRESULT (WINAPI *GetBlob)(IMFAttributes *This,REFGUID guidKey,UINT8 *pBuf,UINT32 cbBufSize,UINT32 *pcbBlobSize);
    HRESULT (WINAPI *GetBlobSize)(IMFAttributes *This,REFGUID guidKey,UINT32 *pcbBlobSize);
    HRESULT (WINAPI *GetCount)(IMFAttributes *This,UINT32 *pcItems);
    HRESULT (WINAPI *GetDouble)(IMFAttributes *This,REFGUID guidKey,double *pfValue);
    HRESULT (WINAPI *GetGUID)(IMFAttributes *This,REFGUID guidKey,GUID *pguidValue);
    HRESULT (WINAPI *GetItem)(IMFAttributes *This,REFGUID guidKey,PROPVARIANT *pValue);
    HRESULT (WINAPI *GetItemByIndex)(IMFAttributes *This,UINT32 unIndex,GUID *pguidKey,PROPVARIANT *pValue);
    HRESULT (WINAPI *GetItemType)(IMFAttributes *This,REFGUID guidKey,MF_ATTRIBUTE_TYPE *pType);
    HRESULT (WINAPI *GetString)(IMFAttributes *This,REFGUID guidKey,LPWSTR pwszValue,UINT32 cchBufSize,UINT32 *pcchLength);
    HRESULT (WINAPI *GetStringLength)(IMFAttributes *This,REFGUID guidKey,UINT32 *pcchLength);
    HRESULT (WINAPI *GetUINT32)(IMFAttributes *This,REFGUID guidKey,UINT32 *punValue);
    HRESULT (WINAPI *GetUINT64)(IMFAttributes *This,REFGUID guidKey,UINT64 *punValue);
    HRESULT (WINAPI *GetUnknown)(IMFAttributes *This,REFGUID guidKey,REFIID riid,LPVOID *ppv);
    HRESULT (WINAPI *LockStore)(IMFAttributes *This);
    HRESULT (WINAPI *SetBlob)(IMFAttributes *This,REFGUID guidKey,const UINT8 *pBuf,UINT32 cbBufSize);
    HRESULT (WINAPI *SetDouble)(IMFAttributes *This,REFGUID guidKey,double fValue);
    HRESULT (WINAPI *SetGUID)(IMFAttributes *This,REFGUID guidKey,REFGUID guidValue);
    HRESULT (WINAPI *SetItem)(IMFAttributes *This,REFGUID guidKey,REFPROPVARIANT Value);
    HRESULT (WINAPI *SetString)(IMFAttributes *This,REFGUID guidKey,LPCWSTR wszValue);
    HRESULT (WINAPI *SetUINT32)(IMFAttributes *This,REFGUID guidKey,UINT32 unValue);
    HRESULT (WINAPI *SetUINT64)(IMFAttributes *This,REFGUID guidKey,UINT64 unValue);
    HRESULT (WINAPI *SetUnknown)(IMFAttributes *This,REFGUID guidKey,IUnknown *pUnknown);
    HRESULT (WINAPI *UnlockStore)(IMFAttributes *This);
  END_INTERFACE
} IMFAttributesVtbl;
struct IMFAttributes {
  CONST_VTBL struct IMFAttributesVtbl *lpVtbl;
};
#ifdef COBJMACROS
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
#endif /*COBJMACROS*/
#endif /*defined(__cplusplus) && !defined(CINTERFACE)*/
#endif /*__IMFAttributes_INTERFACE_DEFINED__*/
#ifdef __IMFMediaBuffer_INTERFACE_DEFINED__
#define __IMFMediaBuffer_INTERFACE_DEFINED__
typedef IMFMediaBuffer *LPIMFMEDIABUFFER;
#if defined(__cplusplus) && !defined(CINTERFACE)
DECLARE_INTERFACE_(IMFMediaBuffer,IUnknown) {
public:
  virtual HRESULT WINAPI GetCurrentLength(DWORD *pcbCurrentLength) PURE;
  virtual HRESULT WINAPI GetMaxLength(DWORD *pcbMaxLength) PURE;
  virtual HRESULT WINAPI Lock(BYTE **ppbBuffer,DWORD *pcbMaxLength,DWORD *pcbCurrentLength) PURE;
  virtual HRESULT WINAPI SetCurrentLength(DWORD cbCurrentLength) PURE;
  virtual HRESULT WINAPI Unlock() PURE;
};
#else /*defined(__cplusplus) && !defined(CINTERFACE)*/
typedef struct IMFMediaBufferVtbl {
  BEGIN_INTERFACE
    HRESULT (WINAPI *GetCurrentLength)(IMFMediaBuffer *This,DWORD *pcbCurrentLength);
    HRESULT (WINAPI *GetMaxLength)(IMFMediaBuffer *This,DWORD *pcbMaxLength);
    HRESULT (WINAPI *Lock)(IMFMediaBuffer *This,BYTE **ppbBuffer,DWORD *pcbMaxLength,DWORD *pcbCurrentLength);
    HRESULT (WINAPI *SetCurrentLength)(IMFMediaBuffer *This,DWORD cbCurrentLength);
    HRESULT (WINAPI *Unlock())(IMFMediaBuffer *This);
  END_INTERFACE
} IMFMediaBufferVtbl;
struct IMFMediaBuffer {
  CONST_VTBL struct IMFMediaBufferVtbl *lpVtbl;
};
#ifdef COBJMACROS
#define IMFMediaBuffer_GetCurrentLength(This,pcbCurrentLength) (This)->lpVtbl->GetCurrentLength(This,pcbCurrentLength)
#define IMFMediaBuffer_GetMaxLength(This,pcbMaxLength) (This)->lpVtbl->GetMaxLength(This,pcbMaxLength)
#define IMFMediaBuffer_Lock(This,ppbBuffer,pcbMaxLength,pcbCurrentLength) (This)->lpVtbl->Lock(This,ppbBuffer,pcbMaxLength,pcbCurrentLength)
#define IMFMediaBuffer_SetCurrentLength(This,cbCurrentLength) (This)->lpVtbl->SetCurrentLength(This,cbCurrentLength)
#define IMFMediaBuffer_Unlock(This) (This)->lpVtbl->Unlock(This)
#endif /*COBJMACROS*/
#endif /*defined(__cplusplus) && !defined(CINTERFACE)*/
#endif /*__IMFMediaBuffer_INTERFACE_DEFINED__*/

#ifndef __IMFASFSplitter_INTERFACE_DEFINED__
#define __IMFASFSplitter_INTERFACE_DEFINED__
typedef IMFASFSplitter *LPIMFASFSPLITTER;
#if defined(__cplusplus) && !defined(CINTERFACE)
DECLARE_INTERFACE_(IMFASFSplitter,IUnknown) {
public:
  virtual HRESULT WINAPI Flush() PURE;
  virtual HRESULT WINAPI GetFlags(DWORD *pdwFlags) PURE;
  virtual HRESULT WINAPI GetLastSendTime(DWORD *pdwLastSendTime) PURE;
  virtual HRESULT WINAPI GetNextSample(DWORD *pdwStatusFlags,WORD *pwStreamNumber,IMFSample **ppISample) PURE;
  virtual HRESULT WINAPI GetSelectedStreams(WORD *pwStreamNumbers,WORD *pwNumStreams) PURE;
  virtual HRESULT WINAPI Initialize(IMFASFContentInfo *pIContentInfo) PURE;
  virtual HRESULT WINAPI ParseData(IMFMediaBuffer *pIBuffer,DWORD cbBufferOffset,DWORD cbLength) PURE;
  virtual HRESULT WINAPI SelectStreams(WORD *pwStreamNumbers,WORD wNumStreams) PURE;
  virtual HRESULT WINAPI SetFlags(DWORD dwFlags) PURE;
};
#else
typedef struct IMFASFSplitterVtbl {
  BEGIN_INTERFACE
    HRESULT (WINAPI *Flush)(IMFASFSplitter* This);
    HRESULT (WINAPI *GetLastSendTime)(IMFASFSplitter* This,DWORD *pdwLastSendTime);
    HRESULT (WINAPI *GetNextSample)(IMFASFSplitter* This,DWORD *pdwStatusFlags,WORD *pwStreamNumber,IMFSample **ppISample);
    HRESULT (WINAPI *GetSelectedStreams)(IMFASFSplitter* This,WORD *pwStreamNumbers,WORD *pwNumStreams);
    HRESULT (WINAPI *Initialize)(IMFASFSplitter* This,IMFASFContentInfo *pIContentInfo);
    HRESULT (WINAPI *ParseData)(IMFASFSplitter* This,MFMediaBuffer *pIBuffer,DWORD cbBufferOffset,DWORD cbLength);
    HRESULT (WINAPI *SelectStreams)(IMFASFSplitter* This,WORD *pwStreamNumbers,WORD wNumStreams);
    HRESULT (WINAPI *SetFlags)(IMFASFSplitter* This,DWORD dwFlags);
  END_INTERFACE
} IMFASFSplitterVtbl;
struct IMFASFSplitter {
  CONST_VTBL struct IMFASFSplitterVtbl *lpVtbl;
};
#ifdef COBJMACROS
#define IMFASFSplitter_Flush(This) (This)->lpVtbl->Flush(This)
#define IMFASFSplitter_GetLastSendTime(This,pdwLastSendTime) (This)->lpVtbl->GetLastSendTime(This,pdwLastSendTime)
#define IMFASFSplitter_GetNextSample(This,pdwStatusFlags,pwStreamNumber,ppISample) (This)->lpVtbl->GetNextSample(This,pdwStatusFlags,pwStreamNumber,ppISample)
#define IMFASFSplitter_GetSelectedStreams(This,pwStreamNumbers,pwNumStreams) (This)->lpVtbl->GetSelectedStreams(This,pwStreamNumbers,pwNumStreams)
#define IMFASFSplitter_Initialize(This,pIContentInfo) (This)->lpVtbl->Initialize(This,pIContentInfo)
#define IMFASFSplitter_ParseData(This,pIBuffer,cbBufferOffset,cbLength) (This)->lpVtbl->ParseData(This,pIBuffer,cbBufferOffset,cbLength)
#define IMFASFSplitter_SelectStreams(This,pwStreamNumbers,wNumStreams) (This)->lpVtbl->SelectStreams(This,pwStreamNumbers,wNumStreams)
#define IMFASFSplitter_SetFlags(This,dwFlags) (This)->lpVtbl->SetFlags(This,dwFlags)
#endif /*COBJMACROS*/
#endif /*defined(__cplusplus) && !defined(CINTERFACE)*/
#endif /*__IMFASFSplitter_INTERFACE_DEFINED__*/

HRESULT WINAPI MFCreateASFSplitter(IMFASFSplitter **ppISplitter);
HRESULT WINAPI MFCreateAttributes(IMFAttributes **ppMFAttributes,UINT32 cInitialSize);

#endif /* (_WIN32_WINNT >= 0x0600) */
#endif /*_INC_WMCONTAINER*/
