/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _COR_H_
#define _COR_H_

#include <ole2.h>
#include "corerror.h"
#include <corhdr.h>

#ifdef __cplusplus
extern "C" {
#endif

  EXTERN_GUID (LIBID_ComPlusRuntime, 0xbed7f4ea, 0x1a96, 0x11d2, 0x8f, 0x8, 0x0, 0xa0, 0xc9, 0xa6, 0x18, 0x6d);
  EXTERN_GUID (GUID_ExportedFromComPlus, 0x90883f05, 0x3d28, 0x11d2, 0x8f, 0x17, 0x0, 0xa0, 0xc9, 0xa6, 0x18, 0x6d);
  EXTERN_GUID (GUID_ManagedName, 0xf21f359, 0xab84, 0x41e8, 0x9a, 0x78, 0x36, 0xd1, 0x10, 0xe6, 0xd2, 0xf9);
  EXTERN_GUID (GUID_Function2Getter, 0x54fc8f55, 0x38de, 0x4703, 0x9c, 0x4e, 0x25, 0x3, 0x51, 0x30, 0x2b, 0x1c);
  EXTERN_GUID (CLSID_CorMetaDataDispenserRuntime, 0x1ec2de53, 0x75cc, 0x11d2, 0x97, 0x75, 0x0, 0xa0, 0xc9, 0xb4, 0xd5, 0xc);
  EXTERN_GUID (GUID_DispIdOverride, 0xcd2bc5c9, 0xf452, 0x4326, 0xb7, 0x14, 0xf9, 0xc5, 0x39, 0xd4, 0xda, 0x58);
  EXTERN_GUID (GUID_ForceIEnumerable, 0xb64784eb, 0xd8d4, 0x4d9b, 0x9a, 0xcd, 0x0e, 0x30, 0x80, 0x64, 0x26, 0xf7);
  EXTERN_GUID (GUID_PropGetCA, 0x2941ff83, 0x88d8, 0x4f73, 0xb6, 0xa9, 0xbd, 0xf8, 0x71, 0x2d, 0x00, 0x0d);
  EXTERN_GUID (GUID_PropPutCA, 0x29533527, 0x3683, 0x4364, 0xab, 0xc0, 0xdb, 0x1a, 0xdd, 0x82, 0x2f, 0xa2);
  EXTERN_GUID (CLSID_CLR_v1_MetaData, 0x005023ca, 0x72b1, 0x11d3, 0x9f, 0xc4, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (CLSID_CLR_v2_MetaData, 0xefea471a, 0x44fd, 0x4862, 0x92, 0x92, 0xc, 0x58, 0xd4, 0x6e, 0x1f, 0x3a);
  EXTERN_GUID (MetaDataCheckDuplicatesFor, 0x30fe7be8, 0xd7d9, 0x11d2, 0x9f, 0x80, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (MetaDataRefToDefCheck, 0xde3856f8, 0xd7d9, 0x11d2, 0x9f, 0x80, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (MetaDataNotificationForTokenMovement, 0xe5d71a4c, 0xd7da, 0x11d2, 0x9f, 0x80, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (MetaDataSetUpdate, 0x2eee315c, 0xd7db, 0x11d2, 0x9f, 0x80, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (MetaDataImportOption, 0x79700f36, 0x4aac, 0x11d3, 0x84, 0xc3, 0x0, 0x90, 0x27, 0x86, 0x8c, 0xb1);
  EXTERN_GUID (MetaDataThreadSafetyOptions, 0xf7559806, 0xf266, 0x42ea, 0x8c, 0x63, 0xa, 0xdb, 0x45, 0xe8, 0xb2, 0x34);
  EXTERN_GUID (MetaDataErrorIfEmitOutOfOrder, 0x1547872d, 0xdc03, 0x11d2, 0x94, 0x20, 0x0, 0x0, 0xf8, 0x8, 0x34, 0x60);
  EXTERN_GUID (MetaDataGenerateTCEAdapters, 0xdcc9de90, 0x4151, 0x11d3, 0x88, 0xd6, 0x0, 0x90, 0x27, 0x54, 0xc4, 0x3a);
  EXTERN_GUID (MetaDataTypeLibImportNamespace, 0xf17ff889, 0x5a63, 0x11d3, 0x9f, 0xf2, 0x0, 0xc0, 0x4f, 0xf7, 0x43, 0x1a);
  EXTERN_GUID (MetaDataLinkerOptions, 0x47e099b6, 0xae7c, 0x4797, 0x83, 0x17, 0xb4, 0x8a, 0xa6, 0x45, 0xb8, 0xf9);
  EXTERN_GUID (MetaDataRuntimeVersion, 0x47e099b7, 0xae7c, 0x4797, 0x83, 0x17, 0xb4, 0x8a, 0xa6, 0x45, 0xb8, 0xf9);
  EXTERN_GUID (MetaDataMergerOptions, 0x132d3a6e, 0xb35d, 0x464e, 0x95, 0x1a, 0x42, 0xef, 0xb9, 0xfb, 0x66, 0x1);
  EXTERN_GUID (MetaDataPreserveLocalRefs, 0xa55c0354, 0xe91b, 0x468b, 0x86, 0x48, 0x7c, 0xc3, 0x10, 0x35, 0xd5, 0x33);
  EXTERN_GUID (CLSID_Cor, 0xbee00010, 0xee77, 0x11d0, 0xa0, 0x15, 0x00, 0xc0, 0x4f, 0xbb, 0xb8, 0x84);
  EXTERN_GUID (CLSID_CorMetaDataDispenser, 0xe5cb7a31, 0x7512, 0x11d2, 0x89, 0xce, 0x0, 0x80, 0xc7, 0x92, 0xe5, 0xd8);
  EXTERN_GUID (CLSID_CorMetaDataDispenserReg, 0x435755ff, 0x7397, 0x11d2, 0x97, 0x71, 0x0, 0xa0, 0xc9, 0xb4, 0xd5, 0xc);
  EXTERN_GUID (CLSID_CorMetaDataReg, 0x87f3a1f5, 0x7397, 0x11d2, 0x97, 0x71, 0x0, 0xa0, 0xc9, 0xb4, 0xd5, 0xc);
  EXTERN_GUID (IID_IMapToken, 0x6a3ea8b, 0x225, 0x11d1, 0xbf, 0x72, 0x0, 0xc0, 0x4f, 0xc3, 0x1e, 0x12);
  EXTERN_GUID (IID_IMetaDataError, 0xb81ff171, 0x20f3, 0x11d2, 0x8d, 0xcc, 0x0, 0xa0, 0xc9, 0xb0, 0x9c, 0x19);
  EXTERN_GUID (IID_IMetaDataDispenser, 0x809c652e, 0x7396, 0x11d2, 0x97, 0x71, 0x00, 0xa0, 0xc9, 0xb4, 0xd5, 0x0c);
  EXTERN_GUID (IID_IMetaDataImport, 0x7dac8207, 0xd3ae, 0x4c75, 0x9b, 0x67, 0x92, 0x80, 0x1a, 0x49, 0x7d, 0x44);
  EXTERN_GUID (IID_IMetaDataImport2, 0xfce5efa0, 0x8bba, 0x4f8e, 0xa0, 0x36, 0x8f, 0x20, 0x22, 0xb0, 0x84, 0x66);
  EXTERN_GUID (IID_IMetaDataFilter, 0xd0e80dd1, 0x12d4, 0x11d3, 0xb3, 0x9d, 0x0, 0xc0, 0x4f, 0xf8, 0x17, 0x95);
  EXTERN_GUID (IID_IHostFilter, 0xd0e80dd3, 0x12d4, 0x11d3, 0xb3, 0x9d, 0x0, 0xc0, 0x4f, 0xf8, 0x17, 0x95);
  EXTERN_GUID (IID_IMetaDataEmit, 0xba3fee4c, 0xecb9, 0x4e41, 0x83, 0xb7, 0x18, 0x3f, 0xa4, 0x1c, 0xd8, 0x59);
  EXTERN_GUID (IID_IMetaDataEmit2, 0xf5dd9950, 0xf693, 0x42e6, 0x83, 0xe, 0x7b, 0x83, 0x3e, 0x81, 0x46, 0xa9);
  EXTERN_GUID (IID_IMetaDataAssemblyEmit, 0x211ef15b, 0x5317, 0x4438, 0xb1, 0x96, 0xde, 0xc8, 0x7b, 0x88, 0x76, 0x93);
  EXTERN_GUID (IID_IMetaDataAssemblyImport, 0xee62470b, 0xe94b, 0x424e, 0x9b, 0x7c, 0x2f, 0x0, 0xc9, 0x24, 0x9f, 0x93);
  EXTERN_GUID (IID_IMetaDataValidate, 0x4709c9c6, 0x81ff, 0x11d3, 0x9f, 0xc7, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (IID_IMetaDataDispenserEx, 0x31bcfce2, 0xdafb, 0x11d2, 0x9f, 0x81, 0x0, 0xc0, 0x4f, 0x79, 0xa0, 0xa3);
  EXTERN_GUID (IID_ICeeGen, 0x7ed1bdff, 0x8e36, 0x11d2, 0x9c, 0x56, 0x0, 0xa0, 0xc9, 0xb7, 0xcc, 0x45);
  EXTERN_GUID (IID_IMetaDataTables, 0xd8f579ab, 0x402d, 0x4b8e, 0x82, 0xd9, 0x5d, 0x63, 0xb1, 0x6, 0x5c, 0x68);
  EXTERN_GUID (IID_IMetaDataTables2, 0xbadb5f70, 0x58da, 0x43a9, 0xa1, 0xc6, 0xd7, 0x48, 0x19, 0xf1, 0x9b, 0x15);
  EXTERN_GUID (IID_IMetaDataInfo, 0x7998ea64, 0x7f95, 0x48b8, 0x86, 0xfc, 0x17, 0xca, 0xf4, 0x8b, 0xf5, 0xcb);

#define CLSID_CorMetaDataRuntime CLSID_CLR_v2_MetaData
#define MetaDataSetENC MetaDataSetUpdate

#define MAIN_CLR_MODULE_NAME_W L"clr"
#define MAIN_CLR_MODULE_NAME_A "clr"

#define MSCOREE_SHIM_W L"mscoree.dll"
#define MSCOREE_SHIM_A "mscoree.dll"

#define COR_NATIVE_LINK_CUSTOM_VALUE L"COMPLUS_NativeLink"
#define COR_NATIVE_LINK_CUSTOM_VALUE_ANSI "COMPLUS_NativeLink"

#define COR_BASE_SECURITY_ATTRIBUTE_CLASS L"System.Security.Permissions.SecurityAttribute"
#define COR_BASE_SECURITY_ATTRIBUTE_CLASS_ANSI "System.Security.Permissions.SecurityAttribute"

#define COR_SUPPRESS_UNMANAGED_CODE_CHECK_ATTRIBUTE L"System.Security.SuppressUnmanagedCodeSecurityAttribute"
#define COR_SUPPRESS_UNMANAGED_CODE_CHECK_ATTRIBUTE_ANSI "System.Security.SuppressUnmanagedCodeSecurityAttribute"

#define COR_UNVER_CODE_ATTRIBUTE L"System.Security.UnverifiableCodeAttribute"
#define COR_UNVER_CODE_ATTRIBUTE_ANSI "System.Security.UnverifiableCodeAttribute"

#define COR_REQUIRES_SECOBJ_ATTRIBUTE L"System.Security.DynamicSecurityMethodAttribute"
#define COR_REQUIRES_SECOBJ_ATTRIBUTE_ANSI "System.Security.DynamicSecurityMethodAttribute"

#define COR_COMPILERSERVICE_DISCARDABLEATTRIBUTE L"System.Runtime.CompilerServices.DiscardableAttribute"
#define COR_COMPILERSERVICE_DISCARDABLEATTRIBUTE_ASNI "System.Runtime.CompilerServices.DiscardableAttribute"

#define MAIN_CLR_DLL_NAME_W MAKEDLLNAME_W (MAIN_CLR_MODULE_NAME_W)
#define MAIN_CLR_DLL_NAME_A MAKEDLLNAME_A (MAIN_CLR_MODULE_NAME_A)

#define INVALID_CONNECTION_ID 0x0
#define INVALID_TASK_ID 0x0
#define MAX_CONNECTION_NAME MAX_PATH

#define SWITCHOUT_HANDLE_VALUE ((HANDLE) (LONG_PTR)-2)

#define COR_NATIVE_LINK_CUSTOM_VALUE_CC 18

  interface IMetaDataImport;
  interface IMetaDataAssemblyEmit;
  interface IMetaDataAssemblyImport;
  interface IMetaDataEmit;
  interface ICeeGen;
  interface IMetaDataDispenser;

  typedef interface IMetaDataAssemblyEmit IMetaDataAssemblyEmit;
  typedef interface IMetaDataAssemblyImport IMetaDataAssemblyImport;
  typedef interface IMetaDataImport IMetaDataImport;

  typedef enum tagCOINITCOR {
    COINITCOR_DEFAULT = 0x0
  } COINITICOR;

  typedef enum tagCOINITEE {
    COINITEE_DEFAULT = 0x0,
    COINITEE_DLL = 0x1,
    COINITEE_MAIN = 0x2
  } COINITIEE;

  typedef enum tagCOUNINITEE {
    COUNINITEE_DEFAULT = 0x0,
    COUNINITEE_DLL = 0x1
  } COUNINITIEE;

  typedef enum {
    regNoCopy = 1,
    regConfig = 2,
    regHasRefs = 4
  } CorRegFlags;

  typedef enum {
    sdNone = 0,
    sdReadOnly = IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA,
    sdReadWrite = sdReadOnly | IMAGE_SCN_MEM_WRITE,
    sdExecute = IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE
  } CeeSectionAttr;

  typedef enum {
    srRelocAbsolute,
    srRelocHighLow = 3,
    srRelocHighAdj,
    srRelocMapToken,
    srRelocRelative,
    srRelocFilePos,
    srRelocCodeRelative,
    srRelocIA64Imm64,
    srRelocDir64,
    srRelocIA64PcRel25,
    srRelocIA64PcRel64,
    srRelocAbsoluteTagged,
    srRelocSentinel,
    srNoBaseReloc = 0x4000,
    srRelocPtr = 0x8000,
    srRelocAbsolutePtr = srRelocPtr + srRelocAbsolute,
    srRelocHighLowPtr = srRelocPtr + srRelocHighLow,
    srRelocRelativePtr = srRelocPtr + srRelocRelative,
    srRelocIA64Imm64Ptr = srRelocPtr + srRelocIA64Imm64,
    srRelocDir64Ptr = srRelocPtr + srRelocDir64
  } CeeSectionRelocType;

  typedef enum {
    nltNone = 1,
    nltAnsi = 2,
    nltUnicode = 3,
    nltAuto = 4,
    nltOle = 5,
    nltMaxValue = 7,
  } CorNativeLinkType;

  typedef enum {
    nlfNone = 0x0,
    nlfLastError = 0x1,
    nlfNoMangle = 0x2,
    nlfMaxValue = 0x3,
  } CorNativeLinkFlags;

  typedef void const *UVCP_CONSTANT;
  typedef void *HCEESECTION;
  typedef GUID CVID;

  typedef struct {
    DWORD dwOSPlatformId;
    DWORD dwOSMajorVersion;
    DWORD dwOSMinorVersion;
  } OSINFO;

  typedef struct {
    USHORT usMajorVersion;
    USHORT usMinorVersion;
    USHORT usBuildNumber;
    USHORT usRevisionNumber;
    LPWSTR szLocale;
    ULONG cbLocale;
    DWORD *rProcessor;
    ULONG ulProcessor;
    OSINFO *rOS;
    ULONG ulOS;
  } ASSEMBLYMETADATA;

  typedef union {
    USHORT highAdj;
  } CeeSectionRelocExtra;

  typedef struct {
    short Major;
    short Minor;
    short Sub;
    short Build;
  } CVStruct;

#include <pshpack1.h>
  typedef struct {
    BYTE m_linkType;
    BYTE m_flags;
    mdMemberRef m_entryPoint;
  } COR_NATIVE_LINK;
#include <poppack.h>

  WINBOOL STDMETHODCALLTYPE _CorDllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved);
  int STDMETHODCALLTYPE _CorExeMain ();
  int STDMETHODCALLTYPE _CorExeMainInternal ();
  int STDMETHODCALLTYPE _CorExeMain2 (PBYTE pUnmappedPE, DWORD cUnmappedPE, LPWSTR pImageNameIn, LPWSTR pLoadersFileName, LPWSTR pCmdLine);
  STDAPI CoInitializeEE (DWORD fFlags);
  STDAPI _CorValidateImage (PVOID *ImageBase, LPCWSTR FileName);
  STDAPI_ (VOID) _CorImageUnloading (PVOID ImageBase);
  STDAPI_ (void) CoUninitializeEE (WINBOOL fFlags);
  STDAPI_ (void) CoEEShutDownCOM (void);
  STDAPI CoInitializeCor (DWORD fFlags);
  STDAPI_ (void) CoUninitializeCor (void);

#undef INTERFACE
#define INTERFACE IMetaDataError
  DECLARE_INTERFACE_ (IMetaDataError, IUnknown) {
    STDMETHOD (OnError) (HRESULT hrError, mdToken token) PURE;
  };

#undef INTERFACE
#define INTERFACE IMapToken
  DECLARE_INTERFACE_ (IMapToken, IUnknown) {
    STDMETHOD (Map) (mdToken tkImp, mdToken tkEmit) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataDispenser
  DECLARE_INTERFACE_ (IMetaDataDispenser, IUnknown) {
    STDMETHOD (DefineScope) (REFCLSID rclsid, DWORD dwCreateFlags, REFIID riid, IUnknown **ppIUnk) PURE;
    STDMETHOD (OpenScope) (LPCWSTR szScope, DWORD dwOpenFlags, REFIID riid, IUnknown **ppIUnk) PURE;
    STDMETHOD (OpenScopeOnMemory) (LPCVOID pData, ULONG cbData, DWORD dwOpenFlags, REFIID riid, IUnknown **ppIUnk) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataEmit
  DECLARE_INTERFACE_ (IMetaDataEmit, IUnknown) {
    STDMETHOD (SetModuleProps) (LPCWSTR szName) PURE;
    STDMETHOD (Save) (LPCWSTR szFile, DWORD dwSaveFlags) PURE;
    STDMETHOD (SaveToStream) (IStream *pIStream, DWORD dwSaveFlags) PURE;
    STDMETHOD (GetSaveSize) (CorSaveSize fSave, DWORD *pdwSaveSize) PURE;
    STDMETHOD (DefineTypeDef) (LPCWSTR szTypeDef, DWORD dwTypeDefFlags, mdToken tkExtends, mdToken rtkImplements[], mdTypeDef *ptd) PURE;
    STDMETHOD (DefineNestedType) (LPCWSTR szTypeDef, DWORD dwTypeDefFlags, mdToken tkExtends, mdToken rtkImplements[], mdTypeDef tdEncloser, mdTypeDef *ptd) PURE;
    STDMETHOD (SetHandler) (IUnknown *pUnk) PURE;
    STDMETHOD (DefineMethod) (mdTypeDef td, LPCWSTR szName, DWORD dwMethodFlags, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, ULONG ulCodeRVA, DWORD dwImplFlags, mdMethodDef *pmd) PURE;
    STDMETHOD (DefineMethodImpl) (mdTypeDef td, mdToken tkBody, mdToken tkDecl) PURE;
    STDMETHOD (DefineTypeRefByName) (mdToken tkResolutionScope, LPCWSTR szName, mdTypeRef *ptr) PURE;
    STDMETHOD (DefineImportType) (IMetaDataAssemblyImport *pAssemImport, const void *pbHashValue, ULONG cbHashValue, IMetaDataImport *pImport, mdTypeDef tdImport, IMetaDataAssemblyEmit *pAssemEmit, mdTypeRef *ptr) PURE;
    STDMETHOD (DefineMemberRef) (mdToken tkImport, LPCWSTR szName, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdMemberRef *pmr) PURE;
    STDMETHOD (DefineImportMember) (IMetaDataAssemblyImport *pAssemImport, const void *pbHashValue, ULONG cbHashValue, IMetaDataImport *pImport, mdToken mbMember, IMetaDataAssemblyEmit *pAssemEmit, mdToken tkParent, mdMemberRef *pmr) PURE;
    STDMETHOD (DefineEvent) (mdTypeDef td, LPCWSTR szEvent, DWORD dwEventFlags, mdToken tkEventType, mdMethodDef mdAddOn, mdMethodDef mdRemoveOn, mdMethodDef mdFire, mdMethodDef rmdOtherMethods[], mdEvent *pmdEvent) PURE;
    STDMETHOD (SetClassLayout) (mdTypeDef td, DWORD dwPackSize, COR_FIELD_OFFSET rFieldOffsets[], ULONG ulClassSize) PURE;
    STDMETHOD (DeleteClassLayout) (mdTypeDef td) PURE;
    STDMETHOD (SetFieldMarshal) (mdToken tk, PCCOR_SIGNATURE pvNativeType, ULONG cbNativeType) PURE;
    STDMETHOD (DeleteFieldMarshal) (mdToken tk) PURE;
    STDMETHOD (DefinePermissionSet) (mdToken tk, DWORD dwAction, void const *pvPermission, ULONG cbPermission, mdPermission *ppm) PURE;
    STDMETHOD (SetRVA) (mdMethodDef md, ULONG ulRVA) PURE;
    STDMETHOD (GetTokenFromSig) (PCCOR_SIGNATURE pvSig, ULONG cbSig, mdSignature *pmsig) PURE;
    STDMETHOD (DefineModuleRef) (LPCWSTR szName, mdModuleRef *pmur) PURE;
    STDMETHOD (SetParent) (mdMemberRef mr, mdToken tk) PURE;
    STDMETHOD (GetTokenFromTypeSpec) (PCCOR_SIGNATURE pvSig, ULONG cbSig, mdTypeSpec *ptypespec) PURE;
    STDMETHOD (SaveToMemory) (void *pbData, ULONG cbData) PURE;
    STDMETHOD (DefineUserString) (LPCWSTR szString, ULONG cchString, mdString *pstk) PURE;
    STDMETHOD (DeleteToken) (mdToken tkObj) PURE;
    STDMETHOD (SetMethodProps) (mdMethodDef md, DWORD dwMethodFlags, ULONG ulCodeRVA, DWORD dwImplFlags) PURE;
    STDMETHOD (SetTypeDefProps) (mdTypeDef td, DWORD dwTypeDefFlags, mdToken tkExtends, mdToken rtkImplements[]) PURE;
    STDMETHOD (SetEventProps) (mdEvent ev, DWORD dwEventFlags, mdToken tkEventType, mdMethodDef mdAddOn, mdMethodDef mdRemoveOn, mdMethodDef mdFire, mdMethodDef rmdOtherMethods[]) PURE;
    STDMETHOD (SetPermissionSetProps) (mdToken tk, DWORD dwAction, void const *pvPermission, ULONG cbPermission, mdPermission *ppm) PURE;
    STDMETHOD (DefinePinvokeMap) (mdToken tk, DWORD dwMappingFlags, LPCWSTR szImportName, mdModuleRef mrImportDLL) PURE;
    STDMETHOD (SetPinvokeMap) (mdToken tk, DWORD dwMappingFlags, LPCWSTR szImportName, mdModuleRef mrImportDLL) PURE;
    STDMETHOD (DeletePinvokeMap) (mdToken tk) PURE;
    STDMETHOD (DefineCustomAttribute) (mdToken tkOwner, mdToken tkCtor, void const *pCustomAttribute, ULONG cbCustomAttribute, mdCustomAttribute *pcv) PURE;
    STDMETHOD (SetCustomAttributeValue) (mdCustomAttribute pcv, void const *pCustomAttribute, ULONG cbCustomAttribute) PURE;
    STDMETHOD (DefineField) (mdTypeDef td, LPCWSTR szName, DWORD dwFieldFlags, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue, mdFieldDef *pmd) PURE;
    STDMETHOD (DefineProperty) (mdTypeDef td, LPCWSTR szProperty, DWORD dwPropFlags, PCCOR_SIGNATURE pvSig, ULONG cbSig, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue, mdMethodDef mdSetter, mdMethodDef mdGetter, mdMethodDef rmdOtherMethods[], mdProperty *pmdProp) PURE;
    STDMETHOD (DefineParam) (mdMethodDef md, ULONG ulParamSeq, LPCWSTR szName, DWORD dwParamFlags, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue, mdParamDef *ppd) PURE;
    STDMETHOD (SetFieldProps) (mdFieldDef fd, DWORD dwFieldFlags, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue) PURE;
    STDMETHOD (SetPropertyProps) (mdProperty pr, DWORD dwPropFlags, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue, mdMethodDef mdSetter, mdMethodDef mdGetter, mdMethodDef rmdOtherMethods[]) PURE;
    STDMETHOD (SetParamProps) (mdParamDef pd, LPCWSTR szName, DWORD dwParamFlags, DWORD dwCPlusTypeFlag, void const *pValue, ULONG cchValue) PURE;
    STDMETHOD (DefineSecurityAttributeSet) (mdToken tkObj, COR_SECATTR rSecAttrs[], ULONG cSecAttrs, ULONG *pulErrorAttr) PURE;
    STDMETHOD (ApplyEditAndContinue) (IUnknown *pImport) PURE;
    STDMETHOD (TranslateSigWithScope) (IMetaDataAssemblyImport *pAssemImport, const void *pbHashValue, ULONG cbHashValue, IMetaDataImport *import, PCCOR_SIGNATURE pbSigBlob, ULONG cbSigBlob, IMetaDataAssemblyEmit *pAssemEmit, IMetaDataEmit *emit, PCOR_SIGNATURE pvTranslatedSig, ULONG cbTranslatedSigMax, ULONG *pcbTranslatedSig) PURE;
    STDMETHOD (SetMethodImplFlags) (mdMethodDef md, DWORD dwImplFlags) PURE;
    STDMETHOD (SetFieldRVA) (mdFieldDef fd, ULONG ulRVA) PURE;
    STDMETHOD (Merge) (IMetaDataImport *pImport, IMapToken *pHostMapToken, IUnknown *pHandler) PURE;
    STDMETHOD (MergeEnd) () PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataEmit2
  DECLARE_INTERFACE_ (IMetaDataEmit2, IMetaDataEmit) {
    STDMETHOD (DefineMethodSpec) (mdToken tkParent, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdMethodSpec *pmi) PURE;
    STDMETHOD (GetDeltaSaveSize) (CorSaveSize fSave, DWORD *pdwSaveSize) PURE;
    STDMETHOD (SaveDelta) (LPCWSTR szFile, DWORD dwSaveFlags) PURE;
    STDMETHOD (SaveDeltaToStream) (IStream *pIStream, DWORD dwSaveFlags) PURE;
    STDMETHOD (SaveDeltaToMemory) (void *pbData, ULONG cbData) PURE;
    STDMETHOD (DefineGenericParam) (mdToken tk, ULONG ulParamSeq, DWORD dwParamFlags, LPCWSTR szname, DWORD reserved, mdToken rtkConstraints[], mdGenericParam *pgp) PURE;
    STDMETHOD (SetGenericParamProps) (mdGenericParam gp, DWORD dwParamFlags, LPCWSTR szName, DWORD reserved, mdToken rtkConstraints[]) PURE;
    STDMETHOD (ResetENCLog) () PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataImport
  DECLARE_INTERFACE_ (IMetaDataImport, IUnknown) {
    STDMETHOD_ (void, CloseEnum) (HCORENUM hEnum) PURE;
    STDMETHOD (CountEnum) (HCORENUM hEnum, ULONG *pulCount) PURE;
    STDMETHOD (ResetEnum) (HCORENUM hEnum, ULONG ulPos) PURE;
    STDMETHOD (EnumTypeDefs) (HCORENUM *phEnum, mdTypeDef rTypeDefs[], ULONG cMax, ULONG *pcTypeDefs) PURE;
    STDMETHOD (EnumInterfaceImpls) (HCORENUM *phEnum, mdTypeDef td, mdInterfaceImpl rImpls[], ULONG cMax, ULONG *pcImpls) PURE;
    STDMETHOD (EnumTypeRefs) (HCORENUM *phEnum, mdTypeRef rTypeRefs[], ULONG cMax, ULONG *pcTypeRefs) PURE;
    STDMETHOD (FindTypeDefByName) (LPCWSTR szTypeDef, mdToken tkEnclosingClass, mdTypeDef *ptd) PURE;
    STDMETHOD (GetScopeProps) (LPWSTR szName, ULONG cchName, ULONG *pchName, GUID *pmvid) PURE;
    STDMETHOD (GetModuleFromScope) (mdModule *pmd) PURE;
    STDMETHOD (GetTypeDefProps) (mdTypeDef td, LPWSTR szTypeDef, ULONG cchTypeDef, ULONG *pchTypeDef, DWORD *pdwTypeDefFlags, mdToken *ptkExtends) PURE;
    STDMETHOD (GetInterfaceImplProps) (mdInterfaceImpl iiImpl, mdTypeDef *pClass, mdToken *ptkIface) PURE;
    STDMETHOD (GetTypeRefProps) (mdTypeRef tr, mdToken *ptkResolutionScope, LPWSTR szName, ULONG cchName, ULONG *pchName) PURE;
    STDMETHOD (ResolveTypeRef) (mdTypeRef tr, REFIID riid, IUnknown **ppIScope, mdTypeDef *ptd) PURE;
    STDMETHOD (EnumMembers) (HCORENUM *phEnum, mdTypeDef cl, mdToken rMembers[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumMembersWithName) (HCORENUM *phEnum, mdTypeDef cl, LPCWSTR szName, mdToken rMembers[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumMethods) (HCORENUM *phEnum, mdTypeDef cl, mdMethodDef rMethods[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumMethodsWithName) (HCORENUM *phEnum, mdTypeDef cl, LPCWSTR szName, mdMethodDef rMethods[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumFields) (HCORENUM *phEnum, mdTypeDef cl, mdFieldDef rFields[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumFieldsWithName) (HCORENUM *phEnum, mdTypeDef cl, LPCWSTR szName, mdFieldDef rFields[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumParams) (HCORENUM *phEnum, mdMethodDef mb, mdParamDef rParams[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumMemberRefs) (HCORENUM *phEnum, mdToken tkParent, mdMemberRef rMemberRefs[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumMethodImpls) (HCORENUM *phEnum, mdTypeDef td, mdToken rMethodBody[], mdToken rMethodDecl[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumPermissionSets) (HCORENUM *phEnum, mdToken tk, DWORD dwActions, mdPermission rPermission[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (FindMember) (mdTypeDef td, LPCWSTR szName, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdToken *pmb) PURE;
    STDMETHOD (FindMethod) (mdTypeDef td, LPCWSTR szName, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdMethodDef *pmb) PURE;
    STDMETHOD (FindField) (mdTypeDef td, LPCWSTR szName, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdFieldDef *pmb) PURE;
    STDMETHOD (FindMemberRef) (mdTypeRef td, LPCWSTR szName, PCCOR_SIGNATURE pvSigBlob, ULONG cbSigBlob, mdMemberRef *pmr) PURE;
    STDMETHOD (GetMethodProps) (mdMethodDef mb, mdTypeDef *pClass, LPWSTR szMethod, ULONG cchMethod, ULONG *pchMethod, DWORD *pdwAttr, PCCOR_SIGNATURE *ppvSigBlob, ULONG *pcbSigBlob, ULONG *pulCodeRVA, DWORD *pdwImplFlags) PURE;
    STDMETHOD (GetMemberRefProps) (mdMemberRef mr, mdToken *ptk, LPWSTR szMember, ULONG cchMember, ULONG *pchMember, PCCOR_SIGNATURE *ppvSigBlob, ULONG *pbSig) PURE;
    STDMETHOD (EnumProperties) (HCORENUM *phEnum, mdTypeDef td, mdProperty rProperties[], ULONG cMax, ULONG *pcProperties) PURE;
    STDMETHOD (EnumEvents) (HCORENUM *phEnum, mdTypeDef td, mdEvent rEvents[], ULONG cMax, ULONG *pcEvents) PURE;
    STDMETHOD (GetEventProps) (mdEvent ev, mdTypeDef *pClass, LPCWSTR szEvent, ULONG cchEvent, ULONG *pchEvent, DWORD *pdwEventFlags, mdToken *ptkEventType, mdMethodDef *pmdAddOn, mdMethodDef *pmdRemoveOn, mdMethodDef *pmdFire, mdMethodDef rmdOtherMethod[], ULONG cMax, ULONG *pcOtherMethod) PURE;
    STDMETHOD (EnumMethodSemantics) (HCORENUM *phEnum, mdMethodDef mb, mdToken rEventProp[], ULONG cMax, ULONG *pcEventProp) PURE;
    STDMETHOD (GetMethodSemantics) (mdMethodDef mb, mdToken tkEventProp, DWORD *pdwSemanticsFlags) PURE;
    STDMETHOD (GetClassLayout) (mdTypeDef td, DWORD *pdwPackSize, COR_FIELD_OFFSET rFieldOffset[], ULONG cMax, ULONG *pcFieldOffset, ULONG *pulClassSize) PURE;
    STDMETHOD (GetFieldMarshal) (mdToken tk, PCCOR_SIGNATURE *ppvNativeType, ULONG *pcbNativeType) PURE;
    STDMETHOD (GetRVA) (mdToken tk, ULONG *pulCodeRVA, DWORD *pdwImplFlags) PURE;
    STDMETHOD (GetPermissionSetProps) (mdPermission pm, DWORD *pdwAction, void const **ppvPermission, ULONG *pcbPermission) PURE;
    STDMETHOD (GetSigFromToken) (mdSignature mdSig, PCCOR_SIGNATURE *ppvSig, ULONG *pcbSig) PURE;
    STDMETHOD (GetModuleRefProps) (mdModuleRef mur, LPWSTR szName, ULONG cchName, ULONG *pchName) PURE;
    STDMETHOD (EnumModuleRefs) (HCORENUM *phEnum, mdModuleRef rModuleRefs[], ULONG cmax, ULONG *pcModuleRefs) PURE;
    STDMETHOD (GetTypeSpecFromToken) (mdTypeSpec typespec, PCCOR_SIGNATURE *ppvSig, ULONG *pcbSig) PURE;
    STDMETHOD (GetNameFromToken) (mdToken tk, MDUTF8CSTR *pszUtf8NamePtr) PURE;
    STDMETHOD (EnumUnresolvedMethods) (HCORENUM *phEnum, mdToken rMethods[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (GetUserString) (mdString stk, LPWSTR szString, ULONG cchString, ULONG *pchString) PURE;
    STDMETHOD (GetPinvokeMap) (mdToken tk, DWORD *pdwMappingFlags, LPWSTR szImportName, ULONG cchImportName, ULONG *pchImportName, mdModuleRef *pmrImportDLL) PURE;
    STDMETHOD (EnumSignatures) (HCORENUM *phEnum, mdSignature rSignatures[], ULONG cmax, ULONG *pcSignatures) PURE;
    STDMETHOD (EnumTypeSpecs) (HCORENUM *phEnum, mdTypeSpec rTypeSpecs[], ULONG cmax, ULONG *pcTypeSpecs) PURE;
    STDMETHOD (EnumUserStrings) (HCORENUM *phEnum, mdString rStrings[], ULONG cmax, ULONG *pcStrings) PURE;
    STDMETHOD (GetParamForMethodIndex) (mdMethodDef md, ULONG ulParamSeq, mdParamDef *ppd) PURE;
    STDMETHOD (EnumCustomAttributes) (HCORENUM *phEnum, mdToken tk, mdToken tkType, mdCustomAttribute rCustomAttributes[], ULONG cMax, ULONG *pcCustomAttributes) PURE;
    STDMETHOD (GetCustomAttributeProps) (mdCustomAttribute cv, mdToken *ptkObj, mdToken *ptkType, void const **ppBlob, ULONG *pcbSize) PURE;
    STDMETHOD (FindTypeRef) (mdToken tkResolutionScope, LPCWSTR szName, mdTypeRef *ptr) PURE;
    STDMETHOD (GetMemberProps) (mdToken mb, mdTypeDef *pClass, LPWSTR szMember, ULONG cchMember, ULONG *pchMember, DWORD *pdwAttr, PCCOR_SIGNATURE *ppvSigBlob, ULONG *pcbSigBlob, ULONG *pulCodeRVA, DWORD *pdwImplFlags, DWORD *pdwCPlusTypeFlag, UVCP_CONSTANT *ppValue, ULONG *pcchValue) PURE;
    STDMETHOD (GetFieldProps) (mdFieldDef mb, mdTypeDef *pClass, LPWSTR szField, ULONG cchField, ULONG *pchField, DWORD *pdwAttr, PCCOR_SIGNATURE *ppvSigBlob, ULONG *pcbSigBlob, DWORD *pdwCPlusTypeFlag, UVCP_CONSTANT *ppValue, ULONG *pcchValue) PURE;
    STDMETHOD (GetPropertyProps) (mdProperty prop, mdTypeDef *pClass, LPCWSTR szProperty, ULONG cchProperty, ULONG *pchProperty, DWORD *pdwPropFlags, PCCOR_SIGNATURE *ppvSig, ULONG *pbSig, DWORD *pdwCPlusTypeFlag, UVCP_CONSTANT *ppDefaultValue, ULONG *pcchDefaultValue, mdMethodDef *pmdSetter, mdMethodDef *pmdGetter, mdMethodDef rmdOtherMethod[], ULONG cMax, ULONG *pcOtherMethod) PURE;
    STDMETHOD (GetParamProps) (mdParamDef tk, mdMethodDef *pmd, ULONG *pulSequence, LPWSTR szName, ULONG cchName, ULONG *pchName, DWORD *pdwAttr, DWORD *pdwCPlusTypeFlag, UVCP_CONSTANT *ppValue, ULONG *pcchValue) PURE;
    STDMETHOD (GetCustomAttributeByName) (mdToken tkObj, LPCWSTR szName, const void **ppData, ULONG *pcbData) PURE;
    STDMETHOD_ (WINBOOL, IsValidToken) (mdToken tk) PURE;
    STDMETHOD (GetNestedClassProps) (mdTypeDef tdNestedClass, mdTypeDef *ptdEnclosingClass) PURE;
    STDMETHOD (GetNativeCallConvFromSig) (void const *pvSig, ULONG cbSig, ULONG *pCallConv) PURE;
    STDMETHOD (IsGlobal) (mdToken pd, int *pbGlobal) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataImport2
  DECLARE_INTERFACE_ (IMetaDataImport2, IMetaDataImport) {
    STDMETHOD (EnumGenericParams) (HCORENUM *phEnum, mdToken tk, mdGenericParam rGenericParams[], ULONG cMax, ULONG *pcGenericParams) PURE;
    STDMETHOD (GetGenericParamProps) (mdGenericParam gp, ULONG *pulParamSeq, DWORD *pdwParamFlags, mdToken *ptOwner, DWORD *reserved, LPWSTR wzname, ULONG cchName, ULONG *pchName) PURE;
    STDMETHOD (GetMethodSpecProps) (mdMethodSpec mi, mdToken *tkParent, PCCOR_SIGNATURE *ppvSigBlob, ULONG *pcbSigBlob) PURE;
    STDMETHOD (EnumGenericParamConstraints) (HCORENUM *phEnum, mdGenericParam tk, mdGenericParamConstraint rGenericParamConstraints[], ULONG cMax, ULONG *pcGenericParamConstraints) PURE;
    STDMETHOD (GetGenericParamConstraintProps) (mdGenericParamConstraint gpc, mdGenericParam *ptGenericParam, mdToken *ptkConstraintType) PURE;
    STDMETHOD (GetPEKind) (DWORD *pdwPEKind, DWORD *pdwMAchine) PURE;
    STDMETHOD (GetVersionString) (LPWSTR pwzBuf, DWORD ccBufSize, DWORD *pccBufSize) PURE;
    STDMETHOD (EnumMethodSpecs) (HCORENUM *phEnum, mdToken tk, mdMethodSpec rMethodSpecs[], ULONG cMax, ULONG *pcMethodSpecs) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataFilter
  DECLARE_INTERFACE_ (IMetaDataFilter, IUnknown) {
    STDMETHOD (UnmarkAll) () PURE;
    STDMETHOD (MarkToken) (mdToken tk) PURE;
    STDMETHOD (IsTokenMarked) (mdToken tk, WINBOOL *pIsMarked) PURE;
  };

#undef INTERFACE
#define INTERFACE IHostFilter
  DECLARE_INTERFACE_ (IHostFilter, IUnknown) {
    STDMETHOD (MarkToken) (mdToken tk) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataAssemblyEmit
  DECLARE_INTERFACE_ (IMetaDataAssemblyEmit, IUnknown) {
    STDMETHOD (DefineAssembly) (const void *pbPublicKey, ULONG cbPublicKey, ULONG ulHashAlgId, LPCWSTR szName, const ASSEMBLYMETADATA *pMetaData, DWORD dwAssemblyFlags, mdAssembly *pma) PURE;
    STDMETHOD (DefineAssemblyRef) (const void *pbPublicKeyOrToken, ULONG cbPublicKeyOrToken, LPCWSTR szName, const ASSEMBLYMETADATA *pMetaData, const void *pbHashValue, ULONG cbHashValue, DWORD dwAssemblyRefFlags, mdAssemblyRef *pmdar) PURE;
    STDMETHOD (DefineFile) (LPCWSTR szName, const void *pbHashValue, ULONG cbHashValue, DWORD dwFileFlags, mdFile *pmdf) PURE;
    STDMETHOD (DefineExportedType) (LPCWSTR szName, mdToken tkImplementation, mdTypeDef tkTypeDef, DWORD dwExportedTypeFlags, mdExportedType *pmdct) PURE;
    STDMETHOD (DefineManifestResource) (LPCWSTR szName, mdToken tkImplementation, DWORD dwOffset, DWORD dwResourceFlags, mdManifestResource *pmdmr) PURE;
    STDMETHOD (SetAssemblyProps) (mdAssembly pma, const void *pbPublicKey, ULONG cbPublicKey, ULONG ulHashAlgId, LPCWSTR szName, const ASSEMBLYMETADATA *pMetaData, DWORD dwAssemblyFlags) PURE;
    STDMETHOD (SetAssemblyRefProps) (mdAssemblyRef ar, const void *pbPublicKeyOrToken, ULONG cbPublicKeyOrToken, LPCWSTR szName, const ASSEMBLYMETADATA *pMetaData, const void *pbHashValue, ULONG cbHashValue, DWORD dwAssemblyRefFlags) PURE;
    STDMETHOD (SetFileProps) (mdFile file, const void *pbHashValue, ULONG cbHashValue, DWORD dwFileFlags) PURE;
    STDMETHOD (SetExportedTypeProps) (mdExportedType ct, mdToken tkImplementation, mdTypeDef tkTypeDef, DWORD dwExportedTypeFlags) PURE;
    STDMETHOD (SetManifestResourceProps) (mdManifestResource mr, mdToken tkImplementation, DWORD dwOffset, DWORD dwResourceFlags) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataAssemblyImport
  DECLARE_INTERFACE_ (IMetaDataAssemblyImport, IUnknown) {
    STDMETHOD (GetAssemblyProps) (mdAssembly mda, const void **ppbPublicKey, ULONG *pcbPublicKey, ULONG *pulHashAlgId, LPWSTR szName, ULONG cchName, ULONG *pchName, ASSEMBLYMETADATA *pMetaData, DWORD *pdwAssemblyFlags) PURE;
    STDMETHOD (GetAssemblyRefProps) (mdAssemblyRef mdar, const void **ppbPublicKeyOrToken, ULONG *pcbPublicKeyOrToken, LPWSTR szName, ULONG cchName, ULONG *pchName, ASSEMBLYMETADATA *pMetaData, const void **ppbHashValue, ULONG *pcbHashValue, DWORD *pdwAssemblyRefFlags) PURE;
    STDMETHOD (GetFileProps) (mdFile mdf, LPWSTR szName, ULONG cchName, ULONG *pchName, const void **ppbHashValue, ULONG *pcbHashValue, DWORD *pdwFileFlags) PURE;
    STDMETHOD (GetExportedTypeProps) (mdExportedType mdct, LPWSTR szName, ULONG cchName, ULONG *pchName, mdToken *ptkImplementation, mdTypeDef *ptkTypeDef, DWORD *pdwExportedTypeFlags) PURE;
    STDMETHOD (GetManifestResourceProps) (mdManifestResource mdmr, LPWSTR szName, ULONG cchName, ULONG *pchName, mdToken *ptkImplementation, DWORD *pdwOffset, DWORD *pdwResourceFlags) PURE;
    STDMETHOD (EnumAssemblyRefs) (HCORENUM *phEnum, mdAssemblyRef rAssemblyRefs[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumFiles) (HCORENUM *phEnum, mdFile rFiles[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumExportedTypes) (HCORENUM *phEnum, mdExportedType rExportedTypes[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (EnumManifestResources) (HCORENUM *phEnum, mdManifestResource rManifestResources[], ULONG cMax, ULONG *pcTokens) PURE;
    STDMETHOD (GetAssemblyFromScope) (mdAssembly *ptkAssembly) PURE;
    STDMETHOD (FindExportedTypeByName) (LPCWSTR szName, mdToken mdtExportedType, mdExportedType *ptkExportedType) PURE;
    STDMETHOD (FindManifestResourceByName) (LPCWSTR szName, mdManifestResource *ptkManifestResource) PURE;
    STDMETHOD_ (void, CloseEnum) (HCORENUM hEnum) PURE;
    STDMETHOD (FindAssembliesByName) (LPCWSTR szAppBase, LPCWSTR szPrivateBin, LPCWSTR szAssemblyName, IUnknown *ppIUnk[], ULONG cMax, ULONG *pcAssemblies) PURE;
  };
  typedef enum {
    ValidatorModuleTypeInvalid = 0x0,
    ValidatorModuleTypeMin = 0x00000001,
    ValidatorModuleTypePE = 0x00000001,
    ValidatorModuleTypeObj = 0x00000002,
    ValidatorModuleTypeEnc = 0x00000003,
    ValidatorModuleTypeIncr = 0x00000004,
    ValidatorModuleTypeMax = 0x00000004,
  } CorValidatorModuleType;

#undef INTERFACE
#define INTERFACE IMetaDataValidate
  DECLARE_INTERFACE_ (IMetaDataValidate, IUnknown) {
    STDMETHOD (ValidatorInit) (DWORD dwModuleType, IUnknown *pUnk) PURE;
    STDMETHOD (ValidateMetaData) () PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataDispenserEx
  DECLARE_INTERFACE_ (IMetaDataDispenserEx, IMetaDataDispenser) {
    STDMETHOD (SetOption) (REFGUID optionid, const VARIANT *value) PURE;
    STDMETHOD (GetOption) (REFGUID optionid, VARIANT *pvalue) PURE;
    STDMETHOD (OpenScopeOnITypeInfo) (ITypeInfo *pITI, DWORD dwOpenFlags, REFIID riid, IUnknown **ppIUnk) PURE;
    STDMETHOD (GetCORSystemDirectory) (LPWSTR szBuffer, DWORD cchBuffer, DWORD *pchBuffer) PURE;
    STDMETHOD (FindAssembly) (LPCWSTR szAppBase, LPCWSTR szPrivateBin, LPCWSTR szGlobalBin, LPCWSTR szAssemblyName, LPCWSTR szName, ULONG cchName, ULONG *pcName) PURE;
    STDMETHOD (FindAssemblyModule) (LPCWSTR szAppBase, LPCWSTR szPrivateBin, LPCWSTR szGlobalBin, LPCWSTR szAssemblyName, LPCWSTR szModuleName, LPWSTR szName, ULONG cchName, ULONG *pcName) PURE;
  };

#undef INTERFACE
#define INTERFACE ICeeGen
  DECLARE_INTERFACE_ (ICeeGen, IUnknown) {
    STDMETHOD (EmitString) (LPWSTR lpString, ULONG *RVA) PURE;
    STDMETHOD (GetString) (ULONG RVA, LPWSTR *lpString) PURE;
    STDMETHOD (AllocateMethodBuffer) (ULONG cchBuffer, UCHAR **lpBuffer, ULONG *RVA) PURE;
    STDMETHOD (GetMethodBuffer) (ULONG RVA, UCHAR **lpBuffer) PURE;
    STDMETHOD (GetIMapTokenIface) (IUnknown **pIMapToken) PURE;
    STDMETHOD (GenerateCeeFile) () PURE;
    STDMETHOD (GetIlSection) (HCEESECTION *section) PURE;
    STDMETHOD (GetStringSection) (HCEESECTION *section) PURE;
    STDMETHOD (AddSectionReloc) (HCEESECTION section, ULONG offset, HCEESECTION relativeTo, CeeSectionRelocType relocType) PURE;
    STDMETHOD (GetSectionCreate) (const char *name, DWORD flags, HCEESECTION *section) PURE;
    STDMETHOD (GetSectionDataLen) (HCEESECTION section, ULONG *dataLen) PURE;
    STDMETHOD (GetSectionBlock) (HCEESECTION section, ULONG len, ULONG align
#ifdef __cplusplus
	= 1
#endif
	, void **ppBytes
#ifdef __cplusplus
	= 0
#endif
	) PURE;
    STDMETHOD (TruncateSection) (HCEESECTION section, ULONG len) PURE;
    STDMETHOD (GenerateCeeMemoryImage) (void **ppImage) PURE;
    STDMETHOD (ComputePointer) (HCEESECTION section, ULONG RVA, UCHAR **lpBuffer) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataTables
  DECLARE_INTERFACE_ (IMetaDataTables, IUnknown) {
    STDMETHOD (GetStringHeapSize) (ULONG *pcbStrings) PURE;
    STDMETHOD (GetBlobHeapSize) (ULONG *pcbBlobs) PURE;
    STDMETHOD (GetGuidHeapSize) (ULONG *pcbGuids) PURE;
    STDMETHOD (GetUserStringHeapSize) (ULONG *pcbBlobs) PURE;
    STDMETHOD (GetNumTables) (ULONG *pcTables) PURE;
    STDMETHOD (GetTableIndex) (ULONG token, ULONG *pixTbl) PURE;
    STDMETHOD (GetTableInfo) (ULONG ixTbl, ULONG *pcbRow, ULONG *pcRows, ULONG *pcCols, ULONG *piKey, const char **ppName) PURE;
    STDMETHOD (GetColumnInfo) (ULONG ixTbl, ULONG ixCol, ULONG *poCol, ULONG *pcbCol, ULONG *pType, const char **ppName) PURE;
    STDMETHOD (GetCodedTokenInfo) (ULONG ixCdTkn, ULONG *pcTokens, ULONG **ppTokens, const char **ppName) PURE;
    STDMETHOD (GetRow) (ULONG ixTbl, ULONG rid, void **ppRow) PURE;
    STDMETHOD (GetColumn) (ULONG ixTbl, ULONG ixCol, ULONG rid, ULONG *pVal) PURE;
    STDMETHOD (GetString) (ULONG ixString, const char **ppString) PURE;
    STDMETHOD (GetBlob) (ULONG ixBlob, ULONG *pcbData, const void **ppData) PURE;
    STDMETHOD (GetGuid) (ULONG ixGuid, const GUID **ppGUID) PURE;
    STDMETHOD (GetUserString) (ULONG ixUserString, ULONG *pcbData, const void **ppData) PURE;
    STDMETHOD (GetNextString) (ULONG ixString, ULONG *pNext) PURE;
    STDMETHOD (GetNextBlob) (ULONG ixBlob, ULONG *pNext) PURE;
    STDMETHOD (GetNextGuid) (ULONG ixGuid, ULONG *pNext) PURE;
    STDMETHOD (GetNextUserString) (ULONG ixUserString, ULONG *pNext) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataTables2
  DECLARE_INTERFACE_ (IMetaDataTables2, IMetaDataTables) {
    STDMETHOD (GetMetaDataStorage) (const void **ppvMd, ULONG *pcbMd) PURE;
    STDMETHOD (GetMetaDataStreamInfo) (ULONG ix, const char **ppchName, const void **ppv, ULONG *pcb) PURE;
  };

#undef INTERFACE
#define INTERFACE IMetaDataInfo
  DECLARE_INTERFACE_ (IMetaDataInfo, IUnknown) {
    STDMETHOD (GetFileMapping) (const void **ppvData, ULONGLONG *pcbData, DWORD *pdwMappingType) PURE;
  };

#ifdef __cplusplus
}

enum {
  SIGN_MASK_ONEBYTE = 0xffffffc0,
  SIGN_MASK_TWOBYTE = 0xffffe000,
  SIGN_MASK_FOURBYTE = 0xf0000000,
};

extern const mdToken __declspec (selectany) g_tkCorEncodeToken[4] = { mdtTypeDef, mdtTypeRef, mdtTypeSpec, mdtBaseType };

FORCEINLINE int CorIsPrimitiveType (CorElementType et) {
  return (et < ELEMENT_TYPE_PTR || et == ELEMENT_TYPE_I || et == ELEMENT_TYPE_U);
}

FORCEINLINE int CorIsModifierElementType (CorElementType et) {
  return ((et == ELEMENT_TYPE_PTR || et == ELEMENT_TYPE_BYREF) ? 1 : (et & ELEMENT_TYPE_MODIFIER));
}

FORCEINLINE ULONG CorSigUncompressedDataSize (PCCOR_SIGNATURE d) {
  return ((d[0] & 0x80) == 0 ? 1 : ((d[0] & 0x40) == 0 ? 2 : 4));
}

inline ULONG CorSigUncompressBigData (PCCOR_SIGNATURE &d) {
  ULONG r;

  if ((d[0] & 0xc0) == 0x80) {
    r = (((ULONG) (d[0] & 0x3f)) << 8) | (ULONG) d[1];
    d += 2;
  }
  else {
    r = (((ULONG) (d[0] & 0x1f)) << 24) | (((ULONG) d[1]) << 16) | (((ULONG) d[2]) << 8) | ((ULONG) d[3]);
    d += 4;
  }
  return r;
}

FORCEINLINE ULONG CorSigUncompressData (PCCOR_SIGNATURE &d) {
  return (((d[0] & 0x80) == 0) ? *d++ : CorSigUncompressBigData (d));
}

FORCEINLINE ULONG CorSigUncompressCallingConv (PCCOR_SIGNATURE &d) { return *d++; }

FORCEINLINE HRESULT CorSigUncompressCallingConv (PCCOR_SIGNATURE d, DWORD len, ULONG *pu) {
  *pu = (len > 0 ? *d : 0);
  return (len > 0 ? S_OK : META_E_BAD_SIGNATURE);
}

FORCEINLINE CorElementType CorSigUncompressElementType (PCCOR_SIGNATURE &d) { return (CorElementType) *d++; }

inline HRESULT CorSigUncompressData (PCCOR_SIGNATURE d, DWORD len, ULONG *po, ULONG *plen) {
  const BYTE *pb = reinterpret_cast<BYTE const *> (d);

  if ((*pb & 0x80) == 0) {
    if (len < 1) { *po = 0; *plen = 0; return META_E_BAD_SIGNATURE; }
    *po = *pb;
    *plen = 1;
  } else if ((*pb & 0xc0) == 0x80) {
    if (len < 2) { *po = 0; *plen = 0; return META_E_BAD_SIGNATURE; }
    *po = (ULONG) (((pb[0] & 0x3f) << 8 | pb[1]));
    *plen = 2;
  } else if ((*pb & 0xe0) == 0xc0) {
    if (len < 4) { *po = 0; *plen = 0; return META_E_BAD_SIGNATURE; }
    *po = (ULONG) (((pb[0] & 0x1f) << 24 | pb[1] << 16 | pb[2] << 8 | pb[3]));
    *plen = 4;
  } else {
    *po = 0; *plen = 0; return META_E_BAD_SIGNATURE;
  }

  return S_OK;
}

inline ULONG CorSigUncompressData (PCCOR_SIGNATURE d, ULONG *po) {
  ULONG sz = 0;

  if (FAILED (CorSigUncompressData (d, 0xff, po, &sz))) {
    *po = 0;
    return (ULONG)-1;
  }

  return sz;
}

inline mdToken CorSigUncompressToken (PCCOR_SIGNATURE &d) {
  mdToken tk = CorSigUncompressData (d);

  return TokenFromRid (tk >> 2, g_tkCorEncodeToken[tk & 0x3]);
}

inline ULONG CorSigUncompressToken (PCCOR_SIGNATURE d, mdToken *ptok) {
  mdToken tk;
  ULONG sz;

  sz = CorSigUncompressData (d, (ULONG *) &tk);
  *ptok = TokenFromRid (tk >> 2, g_tkCorEncodeToken[tk & 0x3]);

  return sz;
}

inline HRESULT CorSigUncompressToken (PCCOR_SIGNATURE d, DWORD len, mdToken *t, DWORD *tlen) {
  mdToken tk;
  HRESULT hr = CorSigUncompressData (d, len, (ULONG *) &tk, tlen);

  if (SUCCEEDED (hr)) {
    tk = TokenFromRid (tk >> 2, g_tkCorEncodeToken[tk & 0x3]);
    *t = tk;
  }
  else
    *t = mdTokenNil;

  return hr;
}

inline ULONG CorSigUncompressSignedInt (PCCOR_SIGNATURE d, int *pi) {
  ULONG i, sz, iData;

  if ((sz = CorSigUncompressData (d, &i)) == (ULONG) -1)
    return sz;

  if ((i & 1) == 0) {
    *pi = (int) (i >> 1);
    return sz;
  }
  i = i >> 1;
  i |= (sz == 1 ? SIGN_MASK_ONEBYTE : (sz == 2 ? SIGN_MASK_TWOBYTE : SIGN_MASK_FOURBYTE));

  *pi = (int) i;

  return sz;
}

inline ULONG CorSigUncompressElementType (PCCOR_SIGNATURE d, CorElementType *et) {
  *et = (CorElementType) (*d & 0x7f);
  return 1;
}

inline ULONG CorSigCompressData (ULONG len, void *p) {
  BYTE *pb = reinterpret_cast<BYTE *> (p);

  if (len <= 0x7f) {
    *pb = BYTE (len);
    return 1;
  }
  if (len <= 0x3fff) {
    pb[0] = BYTE ((len >> 8) | 0x80);
    pb[1] = BYTE (len & 0xff);
    return 2;
  }
  if (len <= 0x1fffffff) {
    pb[0] = BYTE ((len >> 24) | 0xc0);
    pb[1] = BYTE ((len >> 16) & 0xff);
    pb[2] = BYTE ((len >> 8) & 0xff);
    pb[3] = BYTE (len & 0xff);
    return 4;
  }
  return (ULONG) -1;
}

inline ULONG CorSigCompressToken (mdToken tk, void *p) {
  RID rid = RidFromToken (tk);
  ULONG32 t = TypeFromToken (tk);

  if (rid > 0x3ffffff)
    return (ULONG) -1;
  rid = (rid << 2);
  if (t == g_tkCorEncodeToken[1])
    rid |= 0x1;
  else if (t == g_tkCorEncodeToken[2])
    rid |= 0x2;
  else if (t == g_tkCorEncodeToken[3])
    rid |= 0x3;
  return CorSigCompressData ((ULONG)rid, p);
}

inline ULONG CorSigCompressSignedInt (int i, void *p) {
  BYTE *pb = reinterpret_cast<BYTE *> (p);

  if ((i & SIGN_MASK_ONEBYTE) == 0 || (i & SIGN_MASK_ONEBYTE) == SIGN_MASK_ONEBYTE) {
    i = (int) ((i & ~SIGN_MASK_ONEBYTE) << 1 | (i < 0 ? 1 : 0));
    *pb = BYTE (i);
    return 1;
  }
  else if ((i & SIGN_MASK_TWOBYTE) == 0 || (i & SIGN_MASK_TWOBYTE) == SIGN_MASK_TWOBYTE) {
    i = (int) ((i & ~SIGN_MASK_TWOBYTE) << 1 | (i < 0 ? 1 : 0));
    pb[0] = BYTE ((i >> 8) | 0x80);
    pb[1] = BYTE (i & 0xff);
    return 2;
  } else if ((i & SIGN_MASK_FOURBYTE) == 0 || (i & SIGN_MASK_FOURBYTE) == SIGN_MASK_FOURBYTE) {
    i = (int) ((i & ~SIGN_MASK_FOURBYTE) << 1 | (i < 0 ? 1 : 0));
    pb[0] = BYTE ((i >> 24) | 0xc0);
    pb[1] = BYTE ((i >> 16) & 0xff);
    pb[2] = BYTE ((i >> 8) & 0xff);
    pb[3] = BYTE (i & 0xff);
    return 4;
  }

  return (ULONG)-1;
}

inline ULONG CorSigCompressElementType (CorElementType et, void *d) {
  *((BYTE *) d) = BYTE (et);
  return 1;
}

inline ULONG CorSigCompressPointer (void *p, void *d) {
  *((void **) d) = p;
  return (ULONG) sizeof (void *);
}

inline ULONG CorSigUncompressPointer (PCCOR_SIGNATURE d, void **pptr) {
  *pptr = *(void **) d;
  return sizeof (*pptr);
}
#endif

#endif
