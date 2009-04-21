/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_BTHUTIL_H
#define	_BTHUTIL_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 420

#error bthutil.h is only available for Windows CE 5.01 and later

#else

enum BTH_RADIO_MODE
{
    BTH_POWER_OFF,
    BTH_CONNECTABLE,
    BTH_DISCOVERABLE
};

int BthSetMode( DWORD dwMode );
int BthGetMode( DWORD* pdwMode );


#endif /* _WIN32_WCE < 420 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _BTHUTIL_H */
