#include <ic_stdc.h>

static int __cdecl
l_strncnt (const char *s, int n)
{
  int l;

  for (l = 0; l < n && s[l] != 0; l++)
    ;
  return l;
}


static int __cdecl
l_lcmap (ic_slocal_t *p, LCID lcid, DWORD mflags, const char *s, int n, char *d, int dn, int cp, DWORD flags)
{
  wchar_t *ws = NULL, *wd = NULL;
  int r, ws_sz, wd_sz, ws_mem = 0, wd_mem = 0;

  if (n > 0)
    {
      r = l_strncnt (s, n);
      if (r < n)
        r += 1;
      n = r;
    }

  r = 0;

  if (!cp)
    cp = p->locinfo->lc_codepage;

  if (!(ws_sz = MultiByteToWideChar (cp, MB_PRECOMPOSED | flags, s, n, NULL, 0))
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) ws_sz)
    return 0;

  if ((ws_sz * sizeof (wchar_t)) < 1024)
    ws = (wchar_t *) alloca (ws_sz * sizeof (wchar_t));
  else
    {
      ws = (wchar_t *) ic_malloc (ws_sz * sizeof (wchar_t));
      ws_mem = 1;
    }

  if (!ws)
    return 0;

  if (!MultiByteToWideChar (cp, MB_PRECOMPOSED, s, n, ws, ws_sz)
      || !(r = LCMapStringW (lcid, mflags, ws, ws_sz, NULL, 0)))
    {
      if (ws_mem)
	ic_free (ws);
      return 0;
    }

  if ((mflags & LCMAP_SORTKEY) != 0)
    {
      if (dn != 0 && r <= dn)
	LCMapStringW (lcid, mflags, ws, ws_sz, (wchar_t *) d, dn);
      if (ws_mem)
	ic_free (ws);

      return r;
    }
  wd_sz = r;
  if (!wd_sz
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) wd_sz)
    wd = NULL;
  else if ((wd_sz * sizeof (wchar_t)) < 1024)
    wd = (wchar_t *) alloca (wd_sz * sizeof (wchar_t));
  else
    {
      wd = (wchar_t *) ic_malloc (wd_sz * sizeof (wchar_t));
      wd_mem = 1;
    }

  if (wd && LCMapStringW (lcid, mflags, ws, ws_sz, wd, wd_sz))
    {
      if ((!dn)
	r = WideCharToMultiByte (cp, 0, wd, wd_sz, NULL, 0, NULL, NULL);
      else
	r = WideCharToMultiByte (cp, 0, wd, wd_sz, d, dn, NULL, NULL);
    }

  if (wd_mem)
    ic_free (wd);
  if (ws_mem)
    ic_free (ws);

  return r;
}

int __cdecl
__ic_lcmapMBString (ic_slocal_t *p, LCID lcid, DWORD mflags, const char *s, int n,
		    char *d, int dn, int cp, DWORD flags)
{
  ic_lctemp_t h;
  int r;

  ic_lctemp_init (p, &h);
  r = l_lcmap (&h.li, lcid, mflags, s, n, d, dn, cp, flags);
  ic_lctemp_dest (&h);

  return r;
}

