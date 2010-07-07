#include <icrt.h>
#include <tchar.h>
#include <windows.h>

static int initFctPointers (void);

#ifndef _UNICODE
#define __iCrt_MessageBox __iCrt_MessageBoxA
#else
#define __iCrt_MessageBox __iCrt_MessageBoxW
#endif

typedef int (WINAPI *fMessageBox)(HWND, LPCTSTR, LPCTSTR, UINT);
typedef HWND (WINAPI *fGetActiveWindow)(void);
typedef HWND (WINAPI *fGetLastActivePopup)(HWND);
typedef int (WINAPI *fGetUserObjectInformation)(HANDLE, int, void *, DWORD, DWORD *);
typedef HWINSTA (WINAPI *fGetProcessWindowStation)(void);

static fMessageBox pMessageBox;
static fGetActiveWindow pGetActiveWindow;
static fGetLastActivePopup pGetLastActivePopup;
static fGetUserObjectInformation pGetUserObjectInformation;
static fGetProcessWindowStation pGetProcessWindowStation;
static HMODULE hModUser32;

static int
initFctPointers (void)
{
  if (pMessageBox != NULL)
    return 1;
  if (!hModUser32)
    hModUser32 = LoadLibrary (_T("USER32.DLL"));
  if (!hModUser32)
    return 0;

  pGetActiveWindow = (fGetActiveWindow) GetProcAddress (hModUser32, "GetActiveWindow");
  pGetLastActivePopup = (fGetLastActivePopup) GetProcAddress (hModUser32, "GetLastActivePopup");
  pGetProcessWindowStation = (fGetProcessWindowStation) GetProcAddress (hModUser32, "GetProcessWindowStation");
#if _UNICODE
  pMessageBox = (fMessageBox) GetProcAddress (hModUser32, "MessageBoxW");
  pGetUserObjectInformation =
    (fGetUserObjectInformation) GetProcAddress (hModUser32, "GetUserObjectInformationW");
#else
  pMessageBox = (fMessageBox) GetProcAddress (hModUser32, "MessageBoxA");
  pGetUserObjectInformation =
    (fGetUserObjectInformation) GetProcAddress (hModUser32, "GetUserObjectInformationA");
#endif
  
  return (pMessageBox ? 1 : 0);
}

int
__iCrt_MessageBox (LPCTSTR msg, LPCTSTR caption, unsigned int msg_type)
{
  HWND hWnd = NULL;
  int nia = 0;
  HWINSTA hwin;
  DWORD n;
  USEROBJECTFLAGS uof;
  
  if (!initFctPointers ())
    return 0;
  if (pGetUserObjectInformation && pGetProcessWindowStation)
    {
      hwin = (*pGetProcessWindowStation) ();
      if (!hwin || (*pGetUserObjectInformation) (hwin, UOI_FLAGS, &uof, sizeof (uof), &n) == 0
	  || (uof.dwFlags & WSF_VISIBLE) == 0)
	nia = 1;
    }
  if (nia)
    msg_type |= (__iCrt_get_winmajor () >= 4 ? MB_SERVICE_NOTIFICATION : MB_SERVICE_NOTIFICATION_NT3X);
  else
    {
      if (pGetActiveWindow)
        hWnd = (*pGetActiveWindow) ();
      if (hWnd && pGetLastActivePopup)
        hWnd = (*pGetLastActivePopup) (hWnd);
    }

  return (*pMessageBox) (hWnd, msg, caption, msg_type);
}
