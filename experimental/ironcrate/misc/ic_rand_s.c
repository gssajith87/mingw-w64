#include <ic_stdc.h>

typedef WINBOOL (WINAPI *fRtlGenRandom)(void *, ULONG);

/* See http://msdn.microsoft.com/en-us/library/windows/desktop/aa387694%28v=vs.85%29.aspx
   for RtlGenRandom function (aka SystemFunction036 in Advapi32.dll).
   Interesting note here is that ic_srand's seed has no influence on
   ic_rand_s' result.  */

ic_errno_t __cdecl
ic_rand_s (unsigned int *rval)
{
  static fRtlGenRandom l_GenRandom = NULL;
  HMODULE hmod;
  fRtlGenRandom f = NULL;

  if (!rval)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid arguments");
      return IC_EINVAL;
    }

  *rval = 0;

  if (!l_GenRandom)
    {
      hmod = LoadLibraryA ("ADVAPI32.DLL");
      if (!hmod)
	{
	  ic_errno = IC_EINVAL;
	  IC_INV_PARAM("Invalid arguments");
	  return IC_EINVAL;
	}

      f = (fRtlGenRandom) GetProcAddressA (hmod, "SystemFunction036");
      if (!f)
	{
	  ic_errno = _ic_get_errno_from_winerr (GetLastError ());
	  IC_INV_PARAM("Invalid arguments");
	  return ic_errno;
	}
      l_GenRandom = f;
    }

  if ((*l_GenRandom) (rval, (ULONG) sizeof (unsigned int)))
    return 0;

  ic_errno = IC_ENOMEM;
  return IC_ENOMEM;
}

