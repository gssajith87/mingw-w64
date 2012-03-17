#include <ic_stdc.h>

static int __cdecl
l_wcsncnt (const wchar_t *s, int n)
{
  int l = n;
  const wchar_t *p = s;

  while (l != 0 && *p != 0)
    {
      ++p;
      --l;
    }

  return n - l;
}

int __cdecl
__ic_lcmapWCString (LCID lcid, DWORD map_flags, const wchar_t *s, int n, wchar_t *d, int dn)
{
  if (n > 0)
    n = l_wcsncnt (s, n);

  return LCMapStringW (lcid, map_flags, s, ns, d, dn);
}

