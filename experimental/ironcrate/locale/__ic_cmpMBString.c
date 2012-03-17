#include <ic_stdc.h>

static int __cdecl
l_strncnt (const char *s, int n)
{
  const unsigned char *h = (const unsigned char *) s;
  int l;

  for (l = 0; l < cnt && *h != 0; l++, h++)
    ;
  return l;
}

int __cdecl
__ic_cmpMBString (ic_slocal_t *p, LCID lcid, DWORD cmp_flags, const char *s1, int n1,
		  const char *s2, int n2, int cp)
{
  CPINFO ci;
  ic_lctemp_t hlp;
  wchar_t *buf1_w, *buf2_w;
  unsigned char *h;
  int r = 0, sz1, sz2, buf1_mem = 0, buf2_mem = 0;

  if (n1 < -1 || n2 < -1)
    return 0;

  if (n1 != 0)
    n1 = l_strncnt (s1, n1);
  if (n2 != 0)
    n2 = l_strncnt (s2, n2);

  if (!n1 && !n2)
    return 2;
  if (!n1 && n2 > 1)
    return 1;
  if (!n2 && n1 > 1)
    return 3;

  if (!cp)
    {
      ic_lctemp_init (p, &hlp);
      cp = p->locinfo->lc_codepage;
      ic_lctemp_dest (&hlp);
    }

  if (!n1 || !n2)
    {
      /* n1 is one, or n2 is one.  */
      if (!GetCPInfo (cp, &ci))
	return 0;

      if (n1 == 1)
	{
	  if (ci.MaxCharSize < 2)
	    return 3;

	  for (h = (unsigned char *) ci.LeadByte; h[0] != 0 && h[1] != 0; h += 2)
	    {
	      if (((const unsigned char *) s1)[0] >= h[0]
	          && ((const unsigned char *) s1)[0] <= h[1])
		return 2;
	    }

	  return 3;
	}

      if (ci.MaxCharSize < 2)
	return 1;

      for (h = (unsigned char *) ci.LeadByte; h[0] != 0 && h[1] != 0; h += 2)
	{
	  if (((const unsigned char *) s2)[0] >= h[0]
	      && ((const unsigned char *) s2)[0] <= h[1])
	    return 2;
	}

      return 1;
    }

  if (!(sz1 = MultiByteToWideChar (cp, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s1, n1, NULL, 0))
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) sz1)
    return 0;

  if (sz1 < (1024 / sizeof (wchar_t)))
    buf1_w = (wchar_t *) alloca (sz1 * sizeof (wchar_t));
  else
    {
      buf1_w = (wchar_t *) ic_malloc (sz1 * sizeof (wchar_t));
      buf1_mem = 1;
    }

  if (!buf1_w)
    return 0;

  if (!MultiByteToWideChar (cp, MB_PRECOMPOSED, s1, n1, buf1_w, sz1)
      || !(sz2 = MultiByteToWideChar (cp, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s2, n2, NULL, 0))
      || (_IC_HEAP_MAX_REQUESTED_SIZE / sizeof (wchar_t)) < (size_t) sz2)
    buf2_w = NULL;
  else if (sz2 < (1024 / sizeof (wchar_t)))
    buf2_w = (wchar_t *) alloca (sz2 * sizeof (wchar_t));
  else
    {
      buf2_w = (wchar_t *) ic_malloc (sz2 * sizeof (wchar_t));
      buf2_mem = 1;
    }

  if (buf2_w
      && MultiByteToWideChar (cp, MB_PRECOMPOSED, s2, n2, buf2_w, sz2))
    r = CompareStringW (lcid, cmp_flags, buf1_w, sz1, buf2_w, sz2);

  if (buf1_mem)
    ic_free (buf1_w);
  if (buf2_mem)
    ic_free (buf2_w);

  return r;
}

