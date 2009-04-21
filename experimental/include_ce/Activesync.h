/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_ACTIVESYNC_H
#define	_ACTIVESYNC_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 500

#error ActiveSync.h is only available for Windows CE 5.01 and later

#else

#include <windows.h>

HRESULT ActiveSyncStart();
HRESULT ActiveSyncStop();

#endif /* _WIN32_WCE < 500 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _ACTIVESYNC_H */
