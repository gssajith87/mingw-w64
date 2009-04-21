/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
 
#ifndef	_FDRM_H
#define	_FDRM_H

#ifdef	__cplusplus
extern "C" {
#endif


#if _WIN32_WCE < 500

#error fdrm.h is only available for Windows CE 5.01 and later

#else

/* 
* DOCUMENTATION SOURCE
* http://msdn.microsoft.com/en-us/library/bb446724.aspx 
*/

/* Bitmasks for content rights */
#define FDRRF_PLAY           0x00000001      
#define FDRRF_DISPLAY        0x00000002      
#define FDRRF_EXECUTE        0x00000004      
#define FDRRF_PRINT          0x00000008      
#define FDRRF_FORWARD        0x00000010          


/* FileDrmCommitRights @360 NONAME */
HRESULT FileDrmIsDRM (LPCTSTR pszFile, PBOOL pfDRM);

/* FileDrmCreateFile @351 NONAME */
HRESULT FileDrmCreateFile (LPCTSTR pszFileName,
                           DWORD dwDesiredAccess,
                           DWORD dwShareMode,
                           LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                           DWORD dwCreationDisposition,
                           DWORD dwFlagsAndAttributes,
                           HANDLE hTemplateFile,
                           PHANDLE phFile);
                           
                           
                           
                           
                           
/* FileDrmCreateForwardableContent @352 NONAME*/
HRESULT FileDrmCreateForwardableContent (LPCTSTR pszFileName, 
                                         DWORD dwFlags,
                                         LPCTSTR pszOutputFile);

/* FileDrmDeleteFile @361 NONAME */
HRESULT FileDrmDeleteFile (LPCTSTR pszFileName);


/* FileDrmGetMetric @358 NONAME */
HRESULT FileDrmGetMetric (FDRMMETRIC drmID, DWORD *pdwMetric);

/* FileDrmHandleError @356 NONAME */
HRESULT FileDrmHandleError (HWND            hwndParent, 
                            HRESULT         hrError,   
                            LPCTSTR         pszFileName,
                            DWORD           dwFlags,
                            PDWORD          pdwStatus);


/* FileDrmIsDRM @350 NONAME */
HRESULT FileDrmIsDRM (LPCTSTR pszFile, PBOOL pfDRM);

/* FileDrmNotifyDisable @354 NONAME */
HRESULT FileDrmNotifyEnable (LPCTSTR pszFileName, 
                             LPTSTR pszValueName,
                             DWORD cchValueNameLen);

/* FileDrmNotifyEnable @353 NONAME */
HRESULT FileDrmNotifyDisable (LPCTSTR pszFileName);

/* FileDrmRenewRights @357 NONAME */
HRESULT FileDrmRenewRights (HWND hwndParent,
                            LPCTSTR pszFileName);
                            
/* FileDrmShowLicenseInfo @355 NONAME */
HRESULT FileDrmShowLicenseInfo (HWND hwndParent,
                                LPCTSTR pszFileName);
                                
/* FileDrmStoreContent @362 NONAME */
HRESULT FileDrmStoreContent (LPCTSTR pszInputFileName, 
                             LPCTSTR pszOutputFileName,
                             LPVOID  pvReserved,
                             LPTSTR  pszMimeType,
                             DWORD  *pcchMimeTypeLen);
                             
                             
/* FileDrmVerifyRights @359 NONAME */
HRESULT FileDrmVerifyRightsEx (HWND     hwndParent,
                               LPCTSTR  pszFileName, 
                               DWORD    dwRight,
                               DWORD    dwFlags,
                               PDWORD   pdwRightsStatus,
                               LPGUID   pguidFilter);
                               
/* FileDrmVerifyRightsEx @386 NONAME */
HRESULT FileDrmVerifyRightsEx (HWND     hwndParent,
                               LPCTSTR  pszFileName, 
                               DWORD    dwRight,
                               DWORD    dwFlags,
                               PDWORD   pdwRightsStatus,
                               LPGUID   pguidFilter);


#endif /* _WIN32_WCE < 500 */ 

#ifdef	__cplusplus
}
#endif

#endif	/* _FDRM_H */
