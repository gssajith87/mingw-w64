#ifndef _INC_WSDUTIL
#define _INC_WSDUTIL
#if (_WIN32_WINNT >= 0x0600)

void* WINAPI WSDAllocateLinkedMemory(
  void *pParent,
  size_t cbSize
);

void WINAPI WSDAttachLinkedMemory(
  void *pParent,
  void *pChild
);

void WINAPI WSDDetachLinkedMemory(
  void *pVoid
);

void WINAPI WSDFreeLinkedMemory(
  void *pVoid
);

HRESULT WINAPI WSDGenerateFault(
  const LPCWSTR *pszCode,
  const LPCWSTR *pszSubCode,
  const LPCWSTR *pszReason,
  const LPCWSTR *pszDetail,
  IWSDXMLContext *pContext,
  WSD_SOAP_FAULT **ppFault
);

#define WSDAPI_OPTION_MAX_INBOUND_MESSAGE_SIZE 0x0001

HRESULT WINAPI WSDGenerateFaultEx(
  WSDXML_NAME *pCode,
  WSDXML_NAME *pSubCode,
  WSD_LOCALIZED_STRING_LIST *pReasons,
  const LPCWSTR *pszDetail,
  WSD_SOAP_FAULT **ppFault
);

HRESULT WINAPI WSDGetConfigurationOption(
  DWORD dwOption,
  LPVOID pVoid,
  DWORD cbOutBuffer
);

HRESULT WINAPI WSDSetConfigurationOption(
  DWORD dwOption,
  LPVOID pVoid,
  DWORD cbInBuffer
);

STDAPI WSDXMLAddChild(
  WSDXML_ELEMENT *pParent,
  WSDXML_ELEMENT *pChild
);

STDAPI WSDXMLAddSibling(
  WSDXML_ELEMENT *pFirst,
  WSDXML_ELEMENT *pSecond
);

STDAPI WSDXMLBuildAnyForSingleElement(
  WSDXML_NAME *pElementName,
  const LPCWSTR *pszText,
  WSDXML_ELEMENT **ppAny
);

HRESULT WINAPI WSDXMLCleanupElement(
  WSDXML_ELEMENT *pAny
);

STDAPI WSDXMLGetValueFromAny(
  const WCHAR *pszNamespace,
  const WCHAR *pszName,
  WSDXML_ELEMENT *pAny,
  const LPCWSTR *ppszValue
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WSDUTIL*/
