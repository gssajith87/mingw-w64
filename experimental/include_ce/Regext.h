/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_REGEXT_H
#define	_REGEXT_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 500

#error Regext.h is only available for Windows CE 5.01 and later

#else

#include <windows.h>

#define E_ALREADY_REGISTERED         HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED)
#define E_DATATYPE_MISMATCH          HRESULT_FROM_WIN32(ERROR_DATATYPE_MISMATCH)
#define E_INSUFFICIENT_BUFFER        HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)
#define E_INVALID_HANDLE             HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE)
#define E_NOT_READY                  HRESULT_FROM_WIN32(ERROR_NOT_READY)

DECLARE_HANDLE(HREGNOTIFY); // transient notification handle
typedef enum tagREG_COMPARISONTYPE 
{ 
    REG_CT_ANYCHANGE,
    REG_CT_EQUAL,
    REG_CT_NOT_EQUAL,
    REG_CT_GREATER,
    REG_CT_GREATER_OR_EQUAL,
    REG_CT_LESS,
    REG_CT_LESS_OR_EQUAL,
    REG_CT_CONTAINS,
    REG_CT_STARTS_WITH,
    REG_CT_ENDS_WITH
} REG_COMPARISONTYPE;



typedef struct tagNOTIFICATIONCONDITION
{
    REG_COMPARISONTYPE ctComparisonType;
    DWORD dwMask;
    union
    {
        LPCTSTR psz;
        DWORD dw;
    } TargetValue;
} NOTIFICATIONCONDITION;


#define RNAF_NONAMEONCMDLINE 0x00000001


typedef struct tagNOTIFYMSGQUEUEPACKET
{
    HREGNOTIFY hNotify;
    DWORD dwUserData;
    UINT cbData;
    BYTE rgData[1];
} NOTIFYMSGQUEUEPACKET;



typedef void (*REGISTRYNOTIFYCALLBACK)(HREGNOTIFY hNotify,
                                       DWORD dwUserData,
                                       const PBYTE pData,
                                       const UINT cbData);
                                       
HRESULT WINAPI RegistryBatchNotification(HREGNOTIFY hNotify,
                                         DWORD dwMillisecondsIdle,
                                         DWORD dwMillisecondsMax);
                                         
HRESULT WINAPI RegistryCloseNotification(HREGNOTIFY hNotify);

HRESULT WINAPI RegistryDeleteValue(HKEY hKey, 
                                   LPCTSTR pszSubKey,
                                   LPCTSTR pszValueName);
                                   
HRESULT WINAPI RegistryGetDWORD(HKEY hKey,
                                LPCTSTR pszSubKey,
                                LPCTSTR pszValueName,
                                DWORD * pdwData);



HRESULT WINAPI RegistryGetString(HKEY hKey,
                                 LPCTSTR pszSubKey,
                                 LPCTSTR pszValueName,
                                 LPTSTR pszData,
                                 UINT cchData);
                                 
HRESULT WINAPI RegistryNotifyApp(HKEY hKey,
                                 LPCTSTR pszSubKey,
                                 LPCTSTR pszValueName,
                                 LPCTSTR pszName,
                                 LPCTSTR pszApp,
                                 LPCTSTR pszClass,
                                 LPCTSTR pszWindow,
                                 UINT msg,
                                 DWORD dwFlags,
                                 NOTIFICATIONCONDITION * pCondition);

HRESULT WINAPI RegistryNotifyCallback(HKEY hKey,
                                      LPCTSTR pszSubKey,
                                      LPCTSTR pszValueName,
                                      REGISTRYNOTIFYCALLBACK pfnRegistryNotifyCallback,
                                      DWORD dwUserData,
                                      NOTIFICATIONCONDITION * pCondition,
                                      HREGNOTIFY * phNotify);

HRESULT WINAPI RegistryNotifyMsgQueue(HKEY hKey,
                                      LPCTSTR pszSubKey,
                                      LPCTSTR pszValueName,
                                      LPCTSTR pszMsgQueue,
                                      DWORD dwUserData,
                                      NOTIFICATIONCONDITION * pCondition,
                                      HREGNOTIFY * phNotify);
                                      
HRESULT WINAPI RegistryNotifyWindow(HKEY hKey,
                                    LPCTSTR pszSubKey,
                                    LPCTSTR pszValueName,
                                    HWND hWnd,
                                    UINT msg,
                                    DWORD dwUserData,
                                    NOTIFICATIONCONDITION * pCondition,
                                    HREGNOTIFY * phNotify);
                                    
HRESULT WINAPI RegistrySetDWORD(HKEY hKey,
                                LPCTSTR pszSubKey,
                                LPCTSTR pszValueName,
                                DWORD dwData);



HRESULT WINAPI RegistrySetString(HKEY hKey,
                                 LPCTSTR pszSubKey,
                                 LPCTSTR pszValueName,
                                 LPCTSTR pszData);



HRESULT WINAPI RegistryTestExchangeDWORD(HKEY hKey,
                                         LPCTSTR pszSubKey,
                                         LPCTSTR pszValueName,
                                         DWORD dwOldValue,
                                         DWORD dwNewValue);


#endif /* _WIN32_WCE < 500 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _REGEXT_H */






















HRESULT WINAPI RegistryStopNotification(LPCTSTR pszName);









