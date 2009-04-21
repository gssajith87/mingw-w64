/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_APPNAV_H
#define	_APPNAV_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 500

#error appnav.h is only available for Windows CE 5.01 and later

#else

#include <windows.h>

HRESULT CalendarNewAppointment();
HRESULT ContactsNewContact();


#endif /* _WIN32_WCE < 500 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _APPNAV_H */
