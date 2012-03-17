#include <ic_stdc.h>

static int __cdecl
l_wcsncnt (const wchar_t *s, int n)
{
  int l = n;
  wchar_t *p = (wchar_t *) s;

  while (l != 0 && *p != 0)
    {
      ++p;
      --l;
    }

  return n - l;
}

int __cdecl
__ic_cmpWCString (LCID lcid, DWORD cmp_flags, const wchar_t *s1, int n1, const wchar_t *s2, int n2)
{
  if (n1 > 0)
    n1 = l_wcsncnt (s1, n1);
  if (n2 > 0)
    n2 = l_wcsncnt (s2, n2);

  if (!n1 || !n2)
    return (n1 == n2 ? 2 : (n1 < n2 ? 1 : 3));

  return CompareStringW (lcid, cmp_flags, s1, n1, s2, n2);
}

