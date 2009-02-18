#ifndef	_AYGSHELL_H
#define	_AYGSHELL_H

#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef	__cplusplus
extern "C" {
#endif


#include <windows.h>
#include <basetyps.h>	/* Make sure we have a CLSID definition */
#include <shellapi.h>	/* for WINSHELLAPI */
#include <sipapi.h>
#include <prsht.h>

/* Undocumented functions
* AssociateNoteWithCall 
* CancelSIPUp 
* CheckPhoneFeatureLevel
* ClearAppHWND
* ComboBoxEditSubProc
* ComboEditAutoComplete
* CreateFontVariant
* CreateImageCache
* DPI_ExtractIconEx
* DPI_LoadImageFile
* DPI_LoadLibraryRes
* DisplayNotRunnableAppDialog
* DoEditContextMenu
* DrawAlignedIcon
* FreeRegisteredAppInfo
* GetMenuItemCountEM
* GetMenuItemIDEM
* GetMenuStateEM
* GetNextSpan
* GetProtocol
* GetRegisteredAppInfo
* HIDPI_ImageList_LoadImage  - could we make supposition ?
* HIDPI_ImageList_ReplaceIcon
* HomeHideOwnedWindows
* IUnknown_GetObjectOfPDP
* IUnknown_Set
* IUnknown_SetOwner
* InitializeKH
* InsertMenuItemEM
* IsFullScreenWindow
* IsModulePreWinCE421
* IsPhoneAppWindow
* IsSANMessage
* LFHeightForPoint
* LoadStringEtcOver
* LoadStringEtcOverNoCache
* NotifyAppsOnEvent
* OnDefTalkButton
* PhoneGetCallProperties
* PhoneGetCallPropertyBag
* PopulateAndLaunchDialer
* PopulateComboWithMRU
* PopulateMenuWithMRU
* RegOpenKeyEM
* RegQueryValueEM
* SHAnimateListviewOpen
* SHAnimateRects
* SHAnimationSequenceFree
* SHAnimationSequenceHalt
* SHAnimationSequenceHandleTimer
* SHAnimationSequenceInit
* SHAnimationSequenceIsAnimating
* SHAnimationSequenceLaunch
* SHAppNotifyDone
* SHAppendAutorunPath
* SHBoldFontAllowed
* SHBorderPolyline
* SHBorderRectangle
* SHBox
* SHBoxEx
* SHCHGetCOLORREF
* SHCHSetColorFromAttribute
* SHCHSetColorFromString
*/





/* 
The following functions are exported from aygshell.def but MSDN
does not mention them. Definitions are taken from winhq 
http://source.winehq.org/WineAPI/AddMRUData.html
http://source.winehq.org/source/dlls/comctl32/comctl32undoc.c
*/
int AddMRUData (HANDLE  hList, LPCVOID lpData, DWORD cbData);
int AddMRUStringA(HANDLE hList,LPCSTR lpszString);
int AddMRUStringW(HANDLE hList,LPCWSTR lpszString);

typedef struct tagCREATEMRULISTA
{
    DWORD cbSize;
    DWORD nMaxItems;
    DWORD dwFlags;
    HKEY hKey;
    LPCSTR lpszSubKey;
    PROC lpfnCompare;
} CREATEMRULISTA, *LPCREATEMRULISTA;
typedef struct tagCREATEMRULISTW
{
    DWORD cbSize;
    DWORD nMaxItems;
    DWORD dwFlags;
    HKEY hKey;
    LPCWSTR lpszSubKey;
    PROC lpfnCompare;
} CREATEMRULISTW, *LPCREATEMRULISTW;


HANDLE WINAPI CreateMRUListW(LPCREATEMRULISTW);
HANDLE WINAPI CreateMRUListA(LPCREATEMRULISTA);

#ifdef UNICODE
typedef CREATEMRULISTW CREATEMRULIST, *PCREATEMRULIST;
#define CreateMRUList   CreateMRUListW
#else
typedef CREATEMRULISTA CREATEMRULIST, *PCREATEMRULIST;
#define CreateMRUList   CreateMRUListA
#endif

BOOL DelMRUString(HANDLE hList, int nItemPos );

int WINAPI EnumMRUListA(HANDLE hList, int nItemPos, LPVOID lpBuffer, 
                 DWORD nBufferSize);
int WINAPI EnumMRUListW(HANDLE hList, int nItemPos, LPVOID lpBuffer, 
                 DWORD  nBufferSize);

int WINAPI FindMRUData (HANDLE hList, LPCVOID lpData, DWORD cbData,
                         LPINT lpRegNum);

int WINAPI  FindMRUStringA(HANDLE hList, LPCSTR lpszString, LPINT lpRegNum);
int WINAPI  FindMRUStringW(HANDLE hList, LPCWSTR lpszString, LPINT lpRegNum);
void WINAPI FreeMRUList (HANDLE hMRUList);



#define DFRC_FOCUSCOLOR             0  
#define DFRC_SELECTEDBRUSH          1  
BOOL DrawFocusRectColor(HDC hdc, const RECT* lprc, UINT uFlags);

LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

BOOL ExitWindowsEx(UINT uFlags,DWORD dwReserved);

/* Defined in fdrm.h
* FileDrmCommitRights @360 NONAME
* FileDrmCreateFile @351 NONAME
* FileDrmCreateForwardableContent @352 NONAME
* FileDrmDeleteFile @361 NONAME
* FileDrmGetMetric @358 NONAME
* FileDrmHandleError @356 NONAME
* FileDrmIsDRM @350 NONAME
* FileDrmNotifyDisable @354 NONAME
* FileDrmNotifyEnable @353 NONAME
* FileDrmRenewRights @357 NONAME
* FileDrmShowLicenseInfo @355 NONAME
* FileDrmStoreContent @362 NONAME
* FileDrmVerifyRights @359 NONAME
* FileDrmVerifyRightsEx @386 NONAME
*/

/*  NOT SURE */
HWND GetAppHWND();


typedef enum tagOFN_SORTORDER
{
   OFN_SORTORDER_AUTO,
   OFN_SORTORDER_DATE,
   OFN_SORTORDER_NAME,
   OFN_SORTORDER_SIZE,
   OFN_SORTORDER_ASCENDING = 0x00008000

} OFN_SORTORDER;

typedef enum tagOFN_EXFLAG
{
    OFN_EXFLAG_DETAILSVIEW          = 0x00000001,
    OFN_EXFLAG_THUMBNAILVIEW        = 0x00000002,
    OFN_EXFLAG_LOCKDIRECTORY        = 0x00000100,
    OFN_EXFLAG_NOFILECREATE         = 0x00000200,
    OFN_EXFLAG_HIDEDRMPROTECTED     = 0x00010000,     
    OFN_EXFLAG_HIDEDRMFORWARDLOCKED = 0x00020000 
} OFN_EXFLAG;


typedef struct tagOPENFILENAMEEX
{
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCTSTR      lpstrFilter;
   LPTSTR       lpstrCustomFilter;
   DWORD        nMaxCustFilter;
   DWORD        nFilterIndex;
   LPTSTR       lpstrFile;
   DWORD        nMaxFile;
   LPTSTR       lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCTSTR      lpstrInitialDir;
   LPCTSTR      lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCTSTR      lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCTSTR      lpTemplateName;

   // Extended fields
   DWORD       dwSortOrder;
   DWORD       ExFlags;
}OPENFILENAMEEX, *LPOPENFILENAMEEX ;

BOOL GetOpenFileNameEx(LPOPENFILENAMEEX lpofnex);

/* CAMERA STUFF */
typedef enum {
    CAMERACAPTURE_MODE_STILL = 0,
    CAMERACAPTURE_MODE_VIDEOONLY,
    CAMERACAPTURE_MODE_VIDEOWITHAUDIO,
} CAMERACAPTURE_MODE;

typedef enum {
    CAMERACAPTURE_STILLQUALITY_DEFAULT = 0,
    CAMERACAPTURE_STILLQUALITY_LOW,
    CAMERACAPTURE_STILLQUALITY_NORMAL,
    CAMERACAPTURE_STILLQUALITY_HIGH,
} CAMERACAPTURE_STILLQUALITY;

typedef enum {
    CAMERACAPTURE_VIDEOTYPE_ALL = 0xFFFF,
    CAMERACAPTURE_VIDEOTYPE_STANDARD = 1,
    CAMERACAPTURE_VIDEOTYPE_MESSAGING = 2,
} CAMERACAPTURE_VIDEOTYPES;

typedef struct tagSHCAMERACAPTURE
{
    DWORD                       cbSize;
    HWND                        hwndOwner;
    TCHAR                       szFile[MAX_PATH];   
    LPCTSTR                     pszInitialDir;
    LPCTSTR                     pszDefaultFileName;
    LPCTSTR                     pszTitle;
    CAMERACAPTURE_STILLQUALITY  StillQuality;
    CAMERACAPTURE_VIDEOTYPES    VideoTypes;
    DWORD                       nResolutionWidth;
    DWORD                       nResolutionHeight;
    DWORD                       nVideoTimeLimit;
    CAMERACAPTURE_MODE          Mode;
}SHCAMERACAPTURE, *PSHCAMERACAPTURE;

HRESULT SHCameraCapture(PSHCAMERACAPTURE pshcc);




#ifdef	__cplusplus
}
#endif

#endif	/* _AYGSHELL_H */
