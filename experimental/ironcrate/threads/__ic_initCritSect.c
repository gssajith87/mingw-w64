#include <ic_stdc.h>

typedef WINBOOL (WINAPI *fInitCritSpin) (CRITICAL_SECTION *, DWORD);

static WINBOOL WINAPI
l_initcritspin (CRITICAL_SECTION *pcs, DWORD c)
{
  InitializeCriticalSection (pcs);
  return 1;
}

int __cdecl
__ic_initCritSect (CRITICAL_SECTION *pcs, DWORD c)
{
  static fInitCritSpin l_ICS = NULL;
  HINSTANCE hmod;
  fInitCritSpin f = NULL;

  if (!l_ICS)
    {
      hmod = (HINSTANCE) GetModuleHandleA ("kernel32.dll");
      if (hmod)
	f = (fInitCritSpin) GetProcAddressA (hmod,"InitializeCriticalSectionAndSpinCount");
      if (!f)
	f = l_initcritspin;
      l_ICS = f;
    }

  return (*l_ICS) (pcs, c);
}

