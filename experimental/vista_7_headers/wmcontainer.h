#ifndef _INC_WMCONTAINER
#define _INC_WMCONTAINER
#include <objbase.h>

#if (_WIN32_WINNT >= 0x0600)

#ifdef __IMFASFSplitter_FWD_DEFINED__
#define __IMFASFSplitter_FWD_DEFINED__
typedef struct IMFASFSplitter IMFASFSplitter;
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
