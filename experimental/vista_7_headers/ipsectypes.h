#ifndef _INC_IPSECTYPES
#define _INC_IPSECTYPES
#include <windows.h>
#include <iketypes.h>

#if (_WIN32_WINNT >= 0x0600)

typedef UINT8 IPSEC_AUTH_CONFIG;
typedef UINT8 IPSEC_CIPHER_CONFIG;

typedef struct IPSEC_SA_TRANSFORM0_ IPSEC_SA_TRANSFORM0;

typedef enum IPSEC_FAILURE_POINT_ {
  IPSEC_FAILURE_NONE,
  IPSEC_FAILURE_ME,
  IPSEC_FAILURE_PEER,
  IPSEC_FAILURE_POINT_MAX 
} IPSEC_FAILURE_POINT;

typedef enum IPSEC_TRAFFIC_TYPE_ {
  IPSEC_TRAFFIC_TYPE_TRANSPORT,
  IPSEC_TRAFFIC_TYPE_TUNNEL,
  IPSEC_TRAFFIC_TYPE_MAX 
} IPSEC_TRAFFIC_TYPE;

typedef enum IPSEC_PFS_GROUP_ {
  IPSEC_PFS_NONE,
  IPSEC_PFS_1,
  IPSEC_PFS_2,
  IPSEC_PFS_2048,
  IPSEC_PFS_ECP_256,
  IPSEC_PFS_ECP_384,
  IPSEC_PFS_MM,
  IPSEC_PFS_MAX 
} IPSEC_PFS_GROUP;

typedef enum IPSEC_TRANSFORM_TYPE_ {
  IPSEC_TRANSFORM_AH,
  IPSEC_TRANSFORM_ESP_AUTH,
  IPSEC_TRANSFORM_ESP_CIPHER,
  IPSEC_TRANSFORM_ESP_AUTH_AND_CIPHER,
  IPSEC_TRANSFORM_ESP_AUTH_FW,
  IPSEC_TRANSFORM_TYPE_MAX 
} IPSEC_TRANSFORM_TYPE;

typedef enum IPSEC_AUTH_TYPE_ {
  IPSEC_AUTH_MD5,
  IPSEC_AUTH_SHA_1,
  IPSEC_AUTH_SHA_256,
  IPSEC_AUTH_AES_128,
  IPSEC_AUTH_AES_192,
  IPSEC_AUTH_AES_256,
  IPSEC_AUTH_MAX 
} IPSEC_AUTH_TYPE;

typedef enum IPSEC_CIPHER_TYPE_ {
  IPSEC_CIPHER_TYPE_DES,
  IPSEC_CIPHER_TYPE_3DES,
  IPSEC_CIPHER_TYPE_AES_128,
  IPSEC_CIPHER_TYPE_AES_192,
  IPSEC_CIPHER_TYPE_AES_256,
  IPSEC_CIPHER_TYPE_MAX 
} IPSEC_CIPHER_TYPE;

typedef enum IPSEC_CIPHER_TYPE_ {
  IPSEC_CIPHER_TYPE_DES,
  IPSEC_CIPHER_TYPE_3DES,
  IPSEC_CIPHER_TYPE_AES_128,
  IPSEC_CIPHER_TYPE_AES_192,
  IPSEC_CIPHER_TYPE_AES_256,
  IPSEC_CIPHER_TYPE_MAX 
} IPSEC_CIPHER_TYPE;

typedef enum IPSEC_TOKEN_MODE_ {
  IPSEC_TOKEN_MODE_MAIN,
  IPSEC_TOKEN_MODE_EXTENDED,
  IPSEC_TOKEN_MODE_MAX 
} IPSEC_TOKEN_MODE;

typedef enum IPSEC_TOKEN_PRINCIPAL_ {
  IPSEC_TOKEN_PRINCIPAL_LOCAL,
  IPSEC_TOKEN_PRINCIPAL_PEER,
  IPSEC_TOKEN_PRINCIPAL_MAX 
} IPSEC_TOKEN_PRINCIPAL;

typedef enum IPSEC_TOKEN_TYPE_ {
  IPSEC_TOKEN_TYPE_MACHINE,
  IPSEC_TOKEN_TYPE_IMPERSONATION,
  IPSEC_TOKEN_TYPE_MAX 
} IPSEC_TOKEN_TYPE;

typedef struct IPSEC_SA_LIFETIME0_ {
  UINT32 lifetimeSeconds;
  UINT32 lifetimeKilobytes;
  UINT32 lifetimePackets;
} IPSEC_SA_LIFETIME0;

typedef struct IPSEC_KEYING_POLICY0_ {
  UINT32 numKeyMods;
  GUID   *keyModKeys;
} IPSEC_KEYING_POLICY0;

typedef struct IPSEC_SA_IDLE_TIMEOUT0_ {
  UINT32 idleTimeoutSeconds;
  UINT32 idleTimeoutSecondsFailOver;
} IPSEC_SA_IDLE_TIMEOUT0;

typedef struct IPSEC_PROPOSAL0_ {
  IPSEC_SA_LIFETIME0  lifetime;
  UINT32              numSaTransforms;
  IPSEC_SA_TRANSFORM0 *saTransforms;
  IPSEC_PFS_GROUP     pfsGroup;
} IPSEC_PROPOSAL0;

typedef struct IPSEC_TRANSPORT_POLICY0_ {
  UINT32                 numIpsecProposals;
  IPSEC_PROPOSAL0        *ipsecProposals;
  UINT32                 flags;
  UINT32                 ndAllowClearTimeoutSeconds;
  IPSEC_SA_IDLE_TIMEOUT0 saIdleTimeout;
  IKEEXT_EM_POLICY0      *emPolicy;
} IPSEC_TRANSPORT_POLICY0;

typedef struct IPSEC_AUTH_TRANSFORM_ID0_ {
  IPSEC_AUTH_TYPE   authType;
  IPSEC_AUTH_CONFIG authConfig;
} IPSEC_AUTH_TRANSFORM_ID0;

typedef LPVOID IPSEC_CRYPTO_MODULE_ID;

typedef struct IPSEC_AUTH_TRANSFORM0_ {
  IPSEC_AUTH_TRANSFORM_ID0 authTransformId;
  IPSEC_CRYPTO_MODULE_ID   *cryptoModuleId;
} IPSEC_AUTH_TRANSFORM0;

typedef struct IPSEC_CIPHER_TRANSFORM0_ {
  IPSEC_CIPHER_TRANSFORM_ID0 cipherTransformId;
  IPSEC_CRYPTO_MODULE_ID     *cryptoModuleId;
} IPSEC_CIPHER_TRANSFORM0;

typedef struct IPSEC_SA_TRANSFORM0_ {
  IPSEC_TRANSFORM_TYPE ipsecTransformType;
  union DUMMYUNIONNAME {
    IPSEC_AUTH_TRANSFORM0            *ahTransform;
    IPSEC_AUTH_TRANSFORM0            *espAuthTransform;
    IPSEC_CIPHER_TRANSFORM0          *espCipherTransform;
    IPSEC_AUTH_AND_CIPHER_TRANSFORM0 *espAuthAndCipherTransform;
    IPSEC_AUTH_TRANSFORM0            *espAuthFwTransform;
  } ;
} IPSEC_SA_TRANSFORM0;

typedef struct IPSEC_CIPHER_TRANSFORM_ID0_ {
  IPSEC_CIPHER_TYPE   cipherType;
  IPSEC_CIPHER_CONFIG cipherConfig;
} IPSEC_CIPHER_TRANSFORM_ID0;

typedef struct IPSEC_AUTH_AND_CIPHER_TRANSFORM0_ {
  IPSEC_AUTH_TRANSFORM0   authTransform;
  IPSEC_CIPHER_TRANSFORM0 cipherTransform;
} IPSEC_AUTH_AND_CIPHER_TRANSFORM0;

typedef struct IPSEC_TUNNEL_POLICY0_ {
  UINT32                  flags;
  UINT32                  numIpsecProposals;
  IPSEC_PROPOSAL0         *ipsecProposals;
  IPSEC_TUNNEL_ENDPOINTS0 tunnelEndpoints;
  IPSEC_SA_IDLE_TIMEOUT0  saIdleTimeout;
  IKEEXT_EM_POLICY0       *emPolicy;
} IPSEC_TUNNEL_POLICY0;

typedef struct IPSEC_TUNNEL_ENDPOINTS0_ {
  FWP_IP_VERSION ipVersion;
  union DUMMYUNIONNAME1 {
    UINT32 localV4Address;
    UINT8  localV6Address[16];
  } ;
  union DUMMYUNIONNAME2 {
    UINT32 remoteV4Address;
    UINT8  remoteV6Address[16];
  } ;
} IPSEC_TUNNEL_ENDPOINTS0;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_IPSECTYPES*/
