#ifndef _INC_WSDHOST
#define _INC_WSDHOST
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

#include <wsdtypes.h>

#undef  INTERFACE
#define INTERFACE IWSDServiceMessaging
DECLARE_INTERFACE_(IWSDServiceMessaging,IUnknown)
{
    BEGIN_INTERFACE

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IWSDServiceMessaging methods */
    STDMETHOD_(HRESULT,FaultRequest)(THIS_ WSD_SOAP_HEADER *pRequestHeader,IWSDMessageParameters *pMessageParameters,WSD_SOAP_FAULT *pFault) PURE;
    STDMETHOD_(HRESULT,SendResponse)(THIS_ void *pBody,WSD_OPERATION *pOperation,IWSDMessageParameters *pMessageParameters) PURE;

    END_INTERFACE
};
#ifdef COBJMACROS
#define IWSDServiceMessaging_QueryInterface(This,riid,ppvObject) (This)->pVtbl->QueryInterface(This,riid,ppvObject)
#define IWSDServiceMessaging_AddRef(This) (This)->pVtbl->AddRef(This)
#define IWSDServiceMessaging_Release(This) (This)->pVtbl->Release(This)
#define IWSDServiceMessaging_FaultRequest(This,pRequestHeader,pMessageParameters,pFault) (This)->lpVtbl->FaultRequest(This,pRequestHeader,pMessageParameters,pFault)
#define IWSDServiceMessaging_SendResponse(This,pBody,pOperation,pMessageParameters) (This)->lpVtbl->SendResponse(This,pBody,pOperation,pMessageParameters)
#endif /*COBJMACROS*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WSDHOST*/
