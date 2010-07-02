#ifndef _INC_WSDBASE
#define _INC_WSDBASE
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

#undef  INTERFACE
#define INTERFACE IWSDAddress
DECLARE_INTERFACE_(IWSDAddress,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IWSDAddress methods */
    STDMETHOD_(HRESULT,Serialize)(THIS_ LPWSTR pszBuffer,DWORD cchLength,WINBOOL fSafe) PURE;
    STDMETHOD_(HRESULT,Deserialize)(THIS_ LPCWSTR pszBuffer) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IWSDAddress_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IWSDAddress_AddRef(This) (This)->pVtbl->AddRef(This)
#define IWSDAddress_Release(This) (This)->pVtbl->Release(This)
#define IWSDAddress_Serialize(This,pszBuffer,cchLength,fSafe) (This)->lpVtbl->Serialize(This,pszBuffer,cchLength,fSafe)
#define IWSDAddress_Deserialize(This,pszBuffer) (This)->lpVtbl->Deserialize(This,pszBuffer)
#endif /*COBJMACROS*/

#undef  INTERFACE
#define INTERFACE IWSDMessageParameters
DECLARE_INTERFACE_(IWSDMessageParameters,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IWSDServiceMessaging methods */
    STDMETHOD_(HRESULT,GetLocalAddress)(THIS_ IWSDAddress **ppAddress) PURE;
    STDMETHOD_(HRESULT,SetLocalAddress)(THIS_ IWSDAddress *pAddress) PURE;
    STDMETHOD_(HRESULT,GetRemoteAddress)(THIS_ IWSDAddress **ppAddress) PURE;
    STDMETHOD_(HRESULT,SetRemoteAddress)(THIS_ IWSDAddress *pAddress) PURE;
    STDMETHOD_(HRESULT,GetLowerParameters)(THIS_ IWSDMessageParameters **ppTxParams) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IWSDMessageParameters_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IWSDMessageParameters_AddRef(This) (This)->pVtbl->AddRef(This)
#define IWSDMessageParameters_Release(This) (This)->pVtbl->Release(This)
#define IWSDMessageParameters_GetLocalAddress(This,ppAddress) (This)->lpVtbl->GetLocalAddress(This,ppAddress)
#define IWSDMessageParameters_SetLocalAddress(This,pAddress) (This)->lpVtbl->SetLocalAddress(This,pAddress)
#define IWSDMessageParameters_GetRemoteAddress(This,ppAddress) (This)->lpVtbl->GetRemoteAddress(This,ppAddress)
#define IWSDMessageParameters_SetRemoteAddress(This,pAddress) (This)->lpVtbl->SetRemoteAddress(This,pAddress)
#define IWSDMessageParameters_GetLowerParameters(This,ppTxParams) (This)->lpVtbl->GetLowerParameters(This,ppTxParams)
#endif /*COBJMACROS*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WSDBASE*/
