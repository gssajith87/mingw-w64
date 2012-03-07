#include <ic_stdc.h>

void __cdecl
__ic_add_locale_ref (ic_threadlocinfo_t *p)
{
  int i;

  InterlockedIncrement (&p->refcount);
  if (p->lconv_intl_refcount)
    InterlockedIncrement (p->lconv_intl_refcount);

  if (p->lconv_mon_refcount)
    InterlockedIncrement (p->lconv_mon_refcount);

  if (p->lconv_num_refcount)
    InterlockedIncrement (p->lconv_num_refcount);

  if (ptli->ctype1_refcount)
    InterlockedIncrement (p->ctype1_refcount);

  for (i = 0; i < 6; i++)
    {
      if (p->lc_category[i].locale != __ic_str_C
	  && p->lc_category[i].refcount)
	InterlockedIncrement (p->lc_category[i].refcount);
      if (p->lc_category[i].wlocale
	  && p->lc_category[i].wrefcount)
	InterlockedIncrement (p->lc_category[i].wrefcount);
    }

  if (p->lc_time_curr)
    InterlockedIncrement (&p->lc_time_curr->refcount);
}

