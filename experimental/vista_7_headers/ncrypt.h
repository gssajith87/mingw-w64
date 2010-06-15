#ifndef _INC_NCRYPT
#define _INC_NCRYPT
#if (_WIN32_WINNT >= 0x0600)

#define NCRYPTBUFFER_SSL_CLIENT_RANDOM 20
#define NCRYPTBUFFER_SSL_SERVER_RANDOM 21
#define NCRYPTBUFFER_SSL_HIGHEST_VERSION 22
#define NCRYPTBUFFER_SSL_CLEAR_KEY 23
#define NCRYPTBUFFER_SSL_KEY_ARG_DATA 24
#define NCRYPTBUFFER_PKCS_OID 40
#define NCRYPTBUFFER_PKCS_ALG_OID 41
#define NCRYPTBUFFER_PKCS_ALG_PARAM 42
#define NCRYPTBUFFER_PKCS_ALG_ID 43
#define NCRYPTBUFFER_PKCS_ATTRS 44
#define NCRYPTBUFFER_PKCS_KEY_NAME 45
#define NCRYPTBUFFER_PKCS_SECRET 46
#define NCRYPTBUFFER_CERT_BLOB 47

typedef struct _NCRYPT_KEY_HANDLE NCRYPT_KEY_HANDLE;

typedef struct _NCryptBufferDesc {
  ULONG         ulVersion;
  ULONG         cBuffers;
  PNCryptBuffer pBuffers;
} NCryptBufferDesc, *PNCryptBufferDesc;

typedef struct _NCryptBuffer {
  ULONG cbBuffer;
  ULONG BufferType;
  PVOID pvBuffer;
} NCryptBuffer, *PNCryptBuffer;

SECURITY_STATUS WINAPI NCryptExportKey(
  NCRYPT_KEY_HANDLE hKey,
  NCRYPT_KEY_HANDLE hExportKey,
  LPCWSTR pszBlobType,
  NCryptBufferDesc *pParameterList,
  PBYTE pbOutput,
  DWORD cbOutput,
  DWORD *pcbResult,
  DWORD dwFlags
);

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NCRYPT*/
