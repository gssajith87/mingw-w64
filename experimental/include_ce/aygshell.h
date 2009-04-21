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
* SHCheckForContextMenu
* SHCleanMenu
* SHClearStartedBit
* SHColorDisplay
* SHCommandBar_EnableCommand
* SHCommandBar_GetClientRect
* SHCommandBar_GetCommandBarByID
* SHCopyBitmap
* SHCopyIcon
* SHCreateCOleWindow
* SHCreateContextMenu
* SHCreateMainWindow
* SHCreateMenuBarInternal
* SHCreateSystemFont
* SHDeleteTodayWallpaper
* SHDialogAutoClose
* SHDocManagerCreate
* SHDocManagerDestroy
* SHDocManagerQuery
* SHDocManagerRegister
* SHDrawBranding
* SHDrawClippedText
* SHDrawIcon
* SHDrawIconColor
* SHDrawIconEx
* SHDrawMultipleGradient
* SHDrawMultipleGradientBackground
* SHDrawTextOverImage
* SHDrawUnderline
* SHDrawUnderlineColor
* SHEnableEditMenu
* SHEnableRadio
* SHEndProfileObj
* SHEnumFiles
* SHEnumFolders
* SHEscapeAccelerators
* SHEscapeBubbleHtml
* SHFadeImage
* SHFindForegroundMenuBar
* SHFindMenuBarInternal
* SHFindPreviousInstance
* SHFindPreviousInstanceEx
* SHFixMenuIndex
* SHFontMgrCreate
* SHFontMgrDestroy
* SHFontMgrManageFonts
* SHForceBaseState
* SHForceBaseStateEx
* SHFreeScanners
* SHGUIDFromStringW
* SHGetBitmapLogPixels
* SHGetCarrierBranding
* SHGetCarrierBrandingFlag
* SHGetDPISpecificRegKey
* SHGetDeviceFeatureLevel
* SHGetDeviceStateInfo
* SHGetDisplayRotation
* SHGetFontHeight
* SHGetGradientColor
* SHGetKOBits
* SHGetLandscapeRotationSettings
* SHGetLastActiveWindow
* SHGetLegacySupportWindow
* SHGetLocaleInfo
* SHGetMenuItemData
* SHGetMessageBoxIcon
* SHGetMetric
* SHGetNavBarItemRect
* SHGetPowerOnTime
* SHGetPresetMessage
* SHGetSaveFileName
* SHGetScreenOrientation
* SHGetShellWindow
* SHGetSimToolkitMenu
* SHGetSoundFileList
* SHGetStyleBkColor
* SHGetStyleColor
* SHGetStyleFont
* SHGetSystemDefaultLCID
* SHGetTimeFormat
* SHGetUiInfo
* SHGradientDeInit
* SHGradientDraw
* SHGradientInit
* SHHandleActivate
* SHHandleHotkey
* SHHandleSipChange
* SHHdrGrpSepLineDraw
* SHImListPopup
* SHInitDialerClass
* SHInitPresetMessages
* SHInsertPresetMessage
* SHInvalidateScreen
* SHInvokeContextMenuCommand
* SHIsPreOzoneUpdate
* SHIsPreRapierApp
* SHKeyToVerb
* SHLoadFileContextMenuExtensions
* SHLoadFontFromResource
* SHLoadFormattedImageFile
* SHLoadHelperObject
* SHLoadMenuExtensions
* SHLoadSKFromReg
* SHLucyGetTestMode
* SHLucySendMsg
* SHMakeCall
* SHMakeValidFilename
* SHMapCallerPtrArray
* SHMessageBox
* SHNewProfileObj
* SHNotifyAppsOnCallConnect
* SHNotifyAppsOnCarkit
* SHNotifyAppsOnDock
* SHNotifyAppsOnHeadset
* SHNotifyAppsOnIncomingCall
* SHNotifyAppsOnSpeakerPhone
* SHOnFullScreenAppActivate
* SHOnMissedCallCountChange
* SHOnPluginDataChange
* SHOnSAN_NOTIFY
* SHOnVoiceMailCountChange
* SHOriginalClassNameFromATL
* SHPaintBubbleFrame
* SHPolyline
* SHPopulatePresetMessageMenu
* SHPreProcessLogFont
* SHProcessVerb
* SHQueryMenuExtensions
* SHRCMLDialogProc
* SHRectangle
* SHRefreshStartMenu
* SHRegGetHKCUDWValue
* SHRegGetHLMDWValue
* SHRegSetValueEx
* SHReleaseLegacySupportWindow
* SHReleasePresetMessages
* SHResizeDialogProc
* SHRunCpl
* SHRunFontManager
* SHRunPresetMessagesEdit
* SHRunSafeApplet
* SHSameWindowProcesses
* SHSavePWWarning
* SHScanBuffer
* SHScanFile
* SHSendBackToFocusWindow
* SHSendShellMessage
* SHSetAsWatermark
* SHSetBack
* SHSetBubbleRegion
* SHSetDisplayRotation
* SHSetForegroundLastActivePopup
* SHSetKOBits @134 NONAME
* SHSetMenuItemData @268 NONAME
* SHSetPresetMessage @154 NONAME
* SHSetSimToolkitMenu @170 NONAME
* SHSetSoftKey @1003 NONAME
* SHSetStretchMode @300 NONAME
* SHSetWindowBits @59 NONAME
* SHShowContextMenu @67 NONAME
* SHShowSimToolkitUI @2018 NONAME
* SHShowSoftKeys @1004 NONAME
* SHSignalDone @79 NONAME
* SHSipMightBlockUI @314 NONAME
* SHSkipDialogInitialFocus @308 NONAME
* SHSoundManGetDisplayName @207 NONAME
* SHSoundManGetDisplayNameList @205 NONAME
* SHSoundManGetFileName @206 NONAME
* SHStartAndBlock @93 NONAME
* SHStartIfNeeded @85 NONAME
* SHStartProfile @87 NONAME
* SHStretchBitmap @284 NONAME
* SHStretchBltBitmap @290 NONAME
* SHStretchBltBitmapEx @291 NONAME
* SHStretchIcon @307 NONAME
* SHSubclassWindow @275 NONAME
* SHTextBox @105 NONAME
* SHToolkitQueryShell @171 NONAME
* SHTrackPopupMenu @57 NONAME
* SHTranslateQwertyToPhone @394 NONAME
* SHTurnScreenOn @1000 NONAME
* SHUnEscapeAccelerators @240 NONAME
* SHUnlock @122 NONAME
* SHUpdateBaseHue @382 NONAME
* SHUpdateSysColors @371 NONAME
* SHVerifyBackgroundImageRights @374 NONAME
* SHVerifyEventSoundRights @393 NONAME
* SHVoiceTagDelete @2003 NONAME
* SHVoiceTagPlayback @2002 NONAME
* SHVoiceTagRecognize @2001 NONAME
* SHVoiceTagTrain @2000 NONAME
* SHWriteLockState @124 NONAME
* SetDialogAutoScrollBar @301 NONAME
* SetForegroundApp @274 NONAME
* SetKeyHoldableKH @262 NONAME
* SetRegisteredAppInfo @12 NONAME
* SetWindowPosOnRotate @296 NONAME
* Shell_Alloc @15 NONAME
* Shell_AllocString @17 NONAME
* Shell_CatStrAlloc @18 NONAME
* Shell_Free @16 NONAME
* Shell_HeapCreate @14 NONAME
* Shell_LoadStringAlloc @19 NONAME
* Shell_MergeMenus @263 NONAME
* Shell_RegAllocString @20 NONAME
* Shell_UnMergeMenus @264 NONAME
* SndGetSound @390 NONAME
* SndGetSoundDirectoriesList @387 NONAME
* SndGetSoundFileList @388 NONAME
* SndSetSound @389 NONAME
* StrStrI @51 NONAME
* SubClassThisWindow @47 NONAME
* TZFindClose @199 NONAME
* TZFindNext @197 NONAME
* TZFindOpen @196 NONAME
* TZGetData @198 NONAME
* TranslateMessageKH @261 NONAME
* UIHGetTextToStruct @1005 NONAME
* UIHLimitTextControls @1007 NONAME
* UIHSetHWNDToStruct @1008 NONAME
* UIHSetTextFromStruct @1006 NONAME
* VerifyFileTrust @2019 NONAME
* VerifyTrust @236 NONAME
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

BOOL SHCloseApps( DWORD dwMemSought );

/*
 * Menu Bar
 */
#if (_WIN32_WCE >= 0x0300)

typedef struct tagSHMENUBARINFO {
	DWORD		cbSize;
	HWND		hwndParent;
	DWORD		dwFlags;
	UINT		nToolBarId;
	HINSTANCE	hInstRes;
	int nBmpId;
	int cBmpImages;
	HWND		hwndMB;
	COLORREF	clrBk;
} SHMENUBARINFO, *PSHMENUBARINFO;

/* Values for dwFlags */
#define	SHCMBF_EMPTYBAR		0x01
#define	SHCMBF_HIDDEN		0x02
#define	SHCMBF_HIDESIPBUTTON	0x04
#define	SHCMBF_COLORBK		0x08
#define	SHCMBF_HMENU		0x10

#define SHIDIM_FLAGS                0x0001

#define SHIDIF_DONEBUTTON           0x0001
#define SHIDIF_SIZEDLG              0x0002
#define SHIDIF_SIZEDLGFULLSCREEN    0x0004
#define SHIDIF_SIPDOWN              0x0008
#define SHIDIF_FULLSCREENNOMENUBAR  0x0010
#define SHIDIF_EMPTYMENU            0x0020

typedef struct tagSHACTIVATEINFO
{
	DWORD	cbSize;
	HWND	hwndLastFocus;
	UINT	fSipUp:1;
	UINT	fSipOnDeactivation:1;
	UINT	fActive:1;
	UINT	fReserved:29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

typedef struct tagSHINITDLGINFO
{
	DWORD	dwMask;
	HWND	hDlg;
	DWORD	dwFlags;
} SHINITDLGINFO, *PSHINITDLGINFO;

WINSHELLAPI BOOL WINAPI SHCreateMenuBar(SHMENUBARINFO *);
WINSHELLAPI HWND WINAPI SHFindMenuBar(HWND hwnd);
WINSHELLAPI HRESULT WINAPI SHCreateNewItem(HWND,REFCLSID);
HWND SHCreateWorkerWindow(LONG  wndProc,HWND  hWndParent, DWORD dwExStyle,DWORD dwStyle,HMENU hMenu,LONG  z);

#define	WS_NONAVDONEBUTTON	WS_MINIMIZEBOX
#define SHDB_SHOW                   0x0001
#define SHDB_HIDE                   0x0002
#define SHDB_SHOWCANCEL             0x0004
BOOL SHDoneButton(HWND, DWORD);

WINSHELLAPI HRESULT  SHEnableSoftkey(HWND hwndMenuBar, UINT uid,  BOOL bByIndex, BOOL bEnable);

BOOL SHEnumPropSheetHandlers(HKEY hkey, int *pcPages, HPROPSHEETPAGE
        *prghPropPages, IShellPropSheetExt **prgpispse);

/* http://source.winehq.org/WineAPI/SHFillRectClr.html */
DWORD SHFillRectClr(HDC hDC,LPCRECT  pRect,COLORREF cRef);

BOOL SHFreeContextMenuExtensions(HANDLE hCMExtensions);

/* Values for the second parameter to SHFullScreen */
#define	SHFS_SHOWTASKBAR	1
#define	SHFS_HIDETASKBAR	2
#define	SHFS_SHOWSIPBUTTON	4
#define	SHFS_HIDESIPBUTTON	8
#define	SHFS_SHOWSTARTICON	16
#define	SHFS_HIDESTARTICON	32

BOOL SHFullScreen(HWND,DWORD);

BYTE SHGetAppKeyAssoc( LPCTSTR ptszApp );
BOOL SHSetAppKeyWndAssoc( BYTE bVk, HWND hwnd );

BOOL SHGetAutoRunPath( LPTSTR pAutoRunPath );

HRESULT SHGetEmergencyCallList(TCHAR *pwszBuffer, UINT uLenBuf);

HRESULT SHGetInputContext( HWND hwnd, DWORD dwFeature, LPVOID lpValue, LPDWORD lpdwSize );

HRESULT SHGetUIMetrics(SHUIMETRIC shuim, PVOID pvBuffer, DWORD cbBufferSize, DWORD *pcbRequired);

typedef struct
{
    DWORD cbSize;
    HWND hwndLastFocus;
    UINT fSipUp :1;
    UINT fSipOnDeactivation :1;
    UINT fActive :1;
    UINT fReserved :29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

#define SHA_INPUTDIALOG 0x00000001

WINSHELLAPI BOOL SHHandleWMActivate(HWND hwnd, WPARAM wParam, LPARAM lParam, SHACTIVATEINFO* psai, DWORD dwFlags);
WINSHELLAPI BOOL SHHandleWMSettingChange(HWND hwnd, WPARAM wParam, LPARAM lParam, SHACTIVATEINFO* psai);

void WINAPI SHIdleTimerReset();

/* IME */
typedef enum tagSHIME_MODE
{
    SHIME_MODE_NONE                = 0,
    SHIME_MODE_SPELL               = 1,
    SHIME_MODE_SPELL_CAPS          = 2,
    SHIME_MODE_SPELL_CAPS_LOCK     = 3,
    SHIME_MODE_AMBIGUOUS           = 4,
    SHIME_MODE_AMBIGUOUS_CAPS      = 5,
    SHIME_MODE_AMBIGUOUS_CAPS_LOCK = 6,
    SHIME_MODE_NUMBERS             = 7,
    SHIME_MODE_CUSTOM              = 8,
} SHIME_MODE;
HRESULT SHImeGetClearMessage(HIMC himc, UINT *pMsg, WPARAM *pWParam, LPARAM *pLParam);
HRESULT SHImeOnKeyPress(void);
HRESULT SHImeSetCustomInputIcons(HBITMAP hbm);
HRESULT SHImeSetModeIcon(SHIME_MODE mode, DWORD iCustomMode);

/* WM SHELL Dialogs */
typedef struct tagSHINITDLGINFO
{
    DWORD dwMask;
    HWND  hDlg;
    DWORD dwFlags;
} SHINITDLGINFO, *PSHINITDLGINFO;
BOOL SHInitDialog(PSHINITDLGINFO pshidi);

BOOL SHInitExtraControls(void);

void SHInputDialog(HWND hwnd, UINT uMsg, WPARAM wParam);

http://forum.xda-developers.com/showthread.php?t=366184
HRESULT SHIsLocked(LPDWORD pdwState);
HRESULT SHLock(DWORD dwCommand);

BOOL SHLoadContextMenuExtensions(IUnknown *punkOwner, LPCTSTR pszContext,
    LPCTSTR pszClass, HMENU hmenu, UINT idCmdFirst, UINT idCmdLast,
    HANDLE *phCMExtensions);

HBITMAP SHLoadImageFile(LPCTSTR pszFileName);
HBITMAP SHLoadImageResource(HINSTANCE hinst, UINT uIdGif);

http://source.winehq.org/WineAPI/SHLoadMenuPopup.html
BOOL SHLoadMenuPopup(HINSTANCE hInst,LPCWSTR   szName);

http://forum.xda-developers.com/showthread.php?t=234879
typedef struct tagSHMAKECALL
{
        int cbSize;
        int Flag;
        wchar_t *Tel;
        int Unknown[3];
}SHMAKECALL, LPSHMAKECALL;
BOOL SHMakeCall(LPSHMAKECALL lpCall);

define  SHMBOF_NODEFAULT     1 
#define SHMBOF_NOTIFY       2 
#define SHCMBM_OVERRIDEKEY  (WM_USER + 403)
void WINAPI SHNavigateBack();

/*
 * PocketPC Notifications
 */
typedef struct _SHNOTIFICATIONDATA
{
    DWORD        cbStruct;     
    DWORD        dwID;         
    SHNP         npPriority;   
    DWORD        csDuration;   
    HICON        hicon;        
    DWORD        grfFlags;     
    CLSID        clsid;        
    HWND         hwndSink;     
    LPCTSTR      pszHTML;      
    LPCTSTR      pszTitle;     
    LPARAM       lParam;       

} SHNOTIFICATIONDATA;

LRESULT SHNotificationAdd(SHNOTIFICATIONDATA *pndAdd);
LRESULT SHNotificationGetData(const CLSID *pclsid, DWORD dwID,
    SHNOTIFICATIONDATA *pndBuffer);
LRESULT SHNotificationRemove(const CLSID *pclsid, DWORD dwID);
LRESULT SHNotificationUpdate(DWORD grnumUpdateMask, SHNOTIFICATIONDATA * pndNew);

/*
 * PocketPC Gesture
 */

typedef struct tagSHRGI {
    DWORD cbSize;
    HWND hwndClient;
    POINT ptDown;
    DWORD dwFlags;
} SHRGINFO, *PSHRGINFO;

typedef struct tagNMRGINFO 
{
    NMHDR hdr;
    POINT ptAction;
    DWORD dwItemSpec;
} NMRGINFO, *PNMRGINFO;

#define  GN_CONTEXTMENU       1000

#define  SHRG_RETURNCMD       0x00000001
#define  SHRG_NOTIFYPARENT    0x00000002
#define  SHRG_LONGDELAY       0x00000008 

WINSHELLAPI DWORD SHRecognizeGesture(SHRGINFO *shrg);

HRESULT SHSetInputContext( HWND hwnd, DWORD dwFeature, const LPVOID lpValue );

BOOL SHSetNavBarText(HWND hwndRequester, LPCTSTR pszText);

/*
 * PocketPC SIP
 */
#define WC_SIPPREF    L"SIPPREF"

#define SPI_SETSIPINFO          224
#define SPI_GETSIPINFO          225
#define SPI_SETCURRENTIM        226
#define SPI_GETCURRENTIM        227

BOOL SHSipPreference(HWND hwnd, SIPSTATE st);
WINSHELLAPI BOOL SHSipInfo(UINT uiAction,UINT uiParam,PVOID pvParam,UINT fWinIni );


#endif /* (_WIN32_WCE >= 0x0300) */


#ifdef	__cplusplus
}
#endif

#endif	/* _AYGSHELL_H */
