#ifndef _INC_WSDTYPES
#define _INC_WSDTYPES
#include <windows.h>
#include <wsdxmldom.h>
#if (_WIN32_WINNT >= 0x0600)

typedef struct IWSDMessageParameters IWSDMessageParameters;

typedef struct _WSD_EVENT WSD_EVENT;
typedef struct IWSDServiceMessaging IWSDServiceMessaging;
typedef struct _WSD_SOAP_FAULT_SUBCODE WSD_SOAP_FAULT_SUBCODE;
typedef struct _WSD_LOCALIZED_STRING_LIST WSD_LOCALIZED_STRING_LIST;

typedef HRESULT ( *PWSD_SOAP_MESSAGE_HANDLER )(
    IUnknown *thisUnknown,
    WSD_EVENT *event
);

typedef HRESULT ( *WSD_STUB_FUNCTION )(
    IUnknown *server,
    IWSDServiceMessaging *session,
    WSD_EVENT *event
);

typedef struct _WSD_HANDLER_CONTEXT {
  PWSD_SOAP_MESSAGE_HANDLER Handler;
  void                      *PVoid;
  IUnknown                  *Unknown;
} WSD_HANDLER_CONTEXT;

typedef struct _WSDXML_ELEMENT {
  WSDXML_NODE           Node;
  WSDXML_NAME           *Name;
  WSDXML_ATTRIBUTE      *FirstAttribute;
  WSDXML_NODE           *FirstChild;
  WSDXML_PREFIX_MAPPING *PrefixMappings;
} WSDXML_ELEMENT;

typedef struct _WSD_REFERENCE_PROPERTIES {
  WSDXML_ELEMENT *Any;
} WSD_REFERENCE_PROPERTIES;

typedef struct _WSD_REFERENCE_PARAMETERS {
  WSDXML_ELEMENT *Any;
} WSD_REFERENCE_PARAMETERS;

typedef struct _WSD_ENDPOINT_REFERENCE {
  const WCHAR              *Address;
  WSD_REFERENCE_PROPERTIES ReferenceProperties;
  WSD_REFERENCE_PARAMETERS ReferenceParameters;
  WSDXML_NAME              *PortType;
  WSDXML_NAME              *ServiceName;
  WSDXML_ELEMENT           *Any;
} WSD_ENDPOINT_REFERENCE;

typedef struct _WSD_APP_SEQUENCE {
  ULONGLONG   InstanceId;
  const WCHAR *SequenceId;
  ULONGLONG   MessageNumber;
} WSD_APP_SEQUENCE;

typedef struct _WSD_HEADER_RELATESTO {
  WSDXML_NAME *RelationshipType;
  const WCHAR *MessageID;
} WSD_HEADER_RELATESTO;

typedef struct _WSD_SOAP_HEADER {
  const WCHAR            *To;
  const WCHAR            *Action;
  const WCHAR            *MessageID;
  WSD_HEADER_RELATESTO   RelatesTo;
  WSD_ENDPOINT_REFERENCE *ReplyTo;
  WSD_ENDPOINT_REFERENCE *From;
  WSD_ENDPOINT_REFERENCE *FaultTo;
  WSD_APP_SEQUENCE       *AppSequence;
  WSDXML_ELEMENT         *AnyHeaders;
} WSD_SOAP_HEADER;

typedef struct _WSD_SOAP_MESSAGE {
  WSD_SOAP_HEADER Header;
  void            *Body;
  WSDXML_TYPE     *BodyType;
} WSD_SOAP_MESSAGE;

typedef struct _WSD_OPERATION {
  WSDXML_TYPE       *RequestType;
  WSDXML_TYPE       *ResponseType;
  WSD_STUB_FUNCTION RequestStubFunction;
} WSD_OPERATION;

typedef struct _WSD_EVENT {
  HRESULT               Hr;
  DWORD                 EventType;
  WCHAR                 *DispatchTag;
  WSD_HANDLER_CONTEXT   HandlerContext;
  WSD_SOAP_MESSAGE      *Soap;
  WSD_OPERATION         *Operation;
  IWSDMessageParameters *MessageParameters;
} WSD_EVENT;

typedef struct _WSD_SOAP_FAULT_SUBCODE {
  WSDXML_NAME            *Value;
  WSD_SOAP_FAULT_SUBCODE *Subcode;
} WSD_SOAP_FAULT_SUBCODE;

typedef struct _WSD_SOAP_FAULT_CODE {
  WSDXML_NAME            *Value;
  WSD_SOAP_FAULT_SUBCODE *Subcode;
} WSD_SOAP_FAULT_CODE;

typedef struct _WSD_LOCALIZED_STRING {
  const WCHAR *lang;
  const WCHAR *String;
} WSD_LOCALIZED_STRING;

typedef struct _WSD_LOCALIZED_STRING_LIST {
  WSD_LOCALIZED_STRING_LIST *Next;
  WSD_LOCALIZED_STRING      *Element;
} WSD_LOCALIZED_STRING_LIST;

typedef struct _WSD_SOAP_FAULT_REASON {
  WSD_LOCALIZED_STRING_LIST *Text;
} WSD_SOAP_FAULT_REASON;

typedef struct _WSD_SOAP_FAULT {
  WSD_SOAP_FAULT_CODE   *Code;
  WSD_SOAP_FAULT_REASON *Reason;
  const WCHAR           *Node;
  const WCHAR           *Role;
  WSDXML_ELEMENT        *Detail;
} WSD_SOAP_FAULT;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WSDTYPES*/
