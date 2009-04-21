/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_DEVMGMT_H
#define	_DEVMGMT_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 500

#error Devmgmt.h is only available for Windows CE 5.01 and later

#else

#include "cfgmgrapi.h"

HRESULT WINAPI QueryPolicy(DWORD dwPolicyId, PDWORD pdwPolicyValue);

#endif /* _WIN32_WCE < 500 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _DEVMGMT_H */

