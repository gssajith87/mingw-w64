#ifndef _INC_EAPHOSTPEERTYPES
#define _INC_EAPHOSTPEERTYPES
#if (_WIN32_WINNT >= 0x0600)
#include <windows.h>
#include <eaptypes.h>

typedef enum tagEapHostPeerMethodResultReason {
  EapHostPeerMethodResultAltSuccessReceived   = 1,
  EapHostPeerMethodResultTimeout              = 2,
  EapHostPeerMethodResultFromMethod           = 3 
} EapHostPeerMethodResultReason;

typedef enum tagEapHostPeerResponseAction {
  EapHostPeerResponseDiscard               = 0,
  EapHostPeerResponseSend                  = 1,
  EapHostPeerResponseResult                = 2,
  EapHostPeerResponseInvokeUI              = 3,
  EapHostPeerResponseRespond               = 4,
  EapHostPeerResponseStartAuthentication   = 5,
  EapHostPeerResponseNone                  = 6 
} EapHostPeerResponseAction;

typedef enum tagEapHostPeerAuthParams {
  EapHostPeerAuthStatus             = 1,
  EapHostPeerIdentity               = 2,
  EapHostPeerIdentityExtendedInfo   = 3,
  EapHostNapInfo                    = 4 
} EapHostPeerAuthParams;

typedef enum _ISOLATION_STATE {
  ISOLATION_STATE_UNKNOWN             = 0,
  ISOLATION_STATE_NOT_RESTRICTED      = 1,
  ISOLATION_STATE_IN_PROBATION        = 2,
  ISOLATION_STATE_RESTRICTED_ACCESS   = 3 
} ISOLATION_STATE;

typedef enum _EAPHOST_AUTH_STATUS {
  EapHostInvalidSession         = 0,
  EapHostAuthNotStarted         = 1,
  EapHostAuthIdentityExchange   = 2,
  EapHostAuthNegotiatingType    = 3,
  EapHostAuthInProgress         = 4,
  EapHostAuthSucceeded          = 5,
  EapHostAuthFailed             = 6 
} EAPHOST_AUTH_STATUS;

typedef struct _EAPHOST_AUTH_INFO {
  EAPHOST_AUTH_STATUS status;
  DWORD               dwErrorCode;
  DWORD               dwReasonCode;
} EAPHOST_AUTH_INFO;

#if (_WIN32_WINNT >= 0x0601)
typedef struct _tagEapHostPeerNapInfo  {
  ISOLATION_STATE isolationState;
  ProbationTime   probationTime;
  UINT32          stringCorrelationIdLength;
} EapHostPeerNapInfo, *PEapHostPeerNapInfo;
#endif /*(_WIN32_WINNT >= 0x0601)*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EAPHOSTPEERTYPES*/
