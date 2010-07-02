#ifndef _INC_WSDXMLDOM
#define _INC_WSDXMLDOM
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef struct _WSDXML_NAME WSDXML_NAME;
typedef struct _WSDXML_ELEMENT WSDXML_ELEMENT;
typedef struct _WSDXML_NODE WSDXML_NODE;
typedef struct _WSDXML_ATTRIBUTE WSDXML_ATTRIBUTE;
typedef struct _WSDXML_PREFIX_MAPPING WSDXML_PREFIX_MAPPING;

typedef struct _WSDXML_TYPE {
  WCHAR *Uri;
  BYTE  *Table;
} WSDXML_TYPE;

typedef struct _WSDXML_NAMESPACE {
  const WCHAR *Uri;
  const WCHAR *PreferredPrefix;
  WSDXML_NAME *Names;
  WORD        NamesCount;
  WORD        Encoding;
} WSDXML_NAMESPACE;

typedef struct _WSDXML_NAME {
  WSDXML_NAMESPACE *Space;
  WCHAR            *LocalName;
} WSDXML_NAME;

typedef struct _WSDXML_NODE {
  enum DUMMYUNIONNAME {
     ElementType,
     TextType
  }           Type;
  WSDXML_ELEMENT *Parent;
  WSDXML_NODE    *Next;
} WSDXML_NODE;

typedef struct _WSDXML_TEXT {
  WSDXML_NODE Node;
  WCHAR       *Text;
} WSDXML_TEXT;

typedef struct _WSDXML_ATTRIBUTE {
  WSDXML_ELEMENT   *Element;
  WSDXML_ATTRIBUTE *Next;
  WSDXML_NAME      *Name;
  WCHAR            *Value;
} WSDXML_ATTRIBUTE;

typedef struct _WSDXML_PREFIX_MAPPING {
  DWORD                 Refs;
  WSDXML_PREFIX_MAPPING *Next;
  WSDXML_NAMESPACE      *Space;
  WCHAR                 *Prefix;
} WSDXML_PREFIX_MAPPING;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WSDXMLDOM*/
