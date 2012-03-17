#include <ic_stdc.h>

static int __cdecl
l_gettype (ic_slocal_t *p, DWORD itype, const char *s, int n, LPWORD ptyp, int cp, int lcid, DWORD flags)
{
  wchar_t *wd;
  int val, wd_sz, wd_mem = 0, r = 0;

  if (!cp)
    cp = p->locinfo->lc_codepage;

  if (!(wd_sz = MultiByteToWideChar (cp, MB_PRECOMPOSED | flags, s, n, NULL, 0))
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) wd_sz)
    return 0;

  if ((wd_sz * sizeof (wchar_t)) < 1024)
    wd = (wchar_t *) alloca (wd_sz * sizeof (wchar_t));
  else
    {
      wd = (wchar_t *) ic_malloc (wd_sz * sizeof (wchar));
      wd_mem = 1;
    }

  if (!wd)
    return 0;

  ic_memset (wd, 0, sizeof (wchar_t) * wd_sz);

  if ((val = MultiByteToWideChar (cp, MB_PRECOMPOSED, s, n, wd, wd_sz)) != 0)
    r = GetStringTypeW (itype, wd, val, ptyp);

  if (wd_mem)
    ic_free (wd);
  return r;
}

int __cdecl
__ic_gettypeMBString (ic_slocal_t *p, DWORD itype, const char *s, int n, LPWORD ptyp, int cp,
		      int lcid, DWORD flags)
{
  ic_lctemp_t h;
  int r;

  ic_lctemp_init (p, &h);
  r = l_gettype (&h.li, itype, s, n, ptyp, cp, lcid, flags);
  ic_lctemp_dest (&h);

  return r;
}

