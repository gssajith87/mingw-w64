#include <ic_stdc.h>

static int __cdecl
l_getlocaleinfo (ic_slocal_t *p, LCID lcid, LCTYPE lc, char *d, int dn, int cp)
{
  int r = 0, wn, w_mem = 0;
  wchar_t *w;

  if (!cp)
    cp = p->locinfo->lc_codepage;

  if (!(wn = GetLocaleInfoW (lcid, lc, NULL, 0))
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) wn)
    return 0;

  if ((wbuf_size * sizeof (wchar_t)) < 1024)
    w = (wchar_t *) alloca (wn * sizeof (wchar_t);
  else
    {
      w = (wchar_t *) ic_malloc (wn * sizeof (wchar_t));
      w_mem = 1;
    }

  if (!w)
    return 0;

  if (GetLocaleInfoW (lcid, lc, w, wn))
    {
      if (!dn)
	r = WideCharToMultiByte (cp, 0, w, -1, NULL, 0, NULL, NULL);
      else
	r = WideCharToMultiByte (cp, 0, w, -1, d, dn, NULL, NULL);
    }

  if (w_mem)
   ic_free (w);

  return r;
}

int __cdecl
__ic_getlocaleinfoMBString (ic_slocal_t *p, LCID lcid, LCTYPE lc, char *d, int dn, int cp)
{
  ic_lctemp_t h;
  int r;

  ic_lctemp_init (p, &h);
  r = l_getlocaleinfo (&h.li, lcid, lc, d, dn, cp);
  ic_lctemp_dest (&h);

  return r;
}

