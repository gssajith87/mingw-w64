/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_CFGMGRAPI_H
#define	_CFGMGRAPI_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 300

#error appnav.h is only available for Windows CE 3.00 and later

#else

#include <windows.h>

/* Configmanager flags */
#define CFGFLAG_PROCESS                     0x0001
#define CFGFLAG_METADATA                    0x0002

/* error code */
#define CONFIG_E_OBJECTBUSY                 _HRESULT_TYPEDEF_(0x80042001)
#define CONFIG_E_CANCELTIMEOUT              _HRESULT_TYPEDEF_(0x80042002)
#define CONFIG_E_ENTRYNOTFOUND              _HRESULT_TYPEDEF_(0x80042004)
#define CONFIG_S_PROCESSINGCANCELED         _HRESULT_TYPEDEF_(0x00042005)
#define CONFIG_E_CSPEXCEPTION               _HRESULT_TYPEDEF_(0x80042007)
#define CONFIG_E_TRANSACTIONINGFAILURE      _HRESULT_TYPEDEF_(0x80042008)
#define CONFIG_E_BAD_XML                    _HRESULT_TYPEDEF_(0x80042009)

HRESULT DMProcessConfigXML(LPCWSTR pszWXMLin, DWORD dwFlags, LPWSTR *ppszwXMLout);

#endif /* _WIN32_WCE < 300 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _CFGMGRAPI_H */
