#ifndef _INC_CREDSSP
#define _INC_CREDSSP
#if (_WIN32_WINNT >= 0x0600)

typedef enum _CREDSSP_SUBMIT_TYPE {
  CredsspPasswordCreds         = 2,
  CredsspSchannelCreds         = 4,
  CredsspCertificateCreds      = 13,
  CredsspSubmitBufferBoth      = 50,
  CredsspSubmitBufferBothOld   = 51 
}   CREDSPP_SUBMIT_TYPE;

typedef struct _CREDSSP_CRED {
  CREDSPP_SUBMIT_TYPE Type;
  PVOID               pSchannelCred;
  PVOID               pSpnegoCred;
} CREDSSP_CRED, *PCREDSSP_CRED;

typedef struct _SecPkgContext_ClientCreds {
  ULONG  AuthBufferLen;
  PUCHAR AuthBuffer;
} SecPkgContext_ClientCreds, *PSecPkgContext_ClientCreds;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_CREDSSP*/