#include <ic_stdc.h>

void * __cdecl
__ic_release_locale_ref (ic_threadlocinfo_t *p)
{
  int i;

  if (!p)
    return NULL;

  InterlockedDecrement (&p->refcount);

  if (p->lconv_intl_refcount)
    InterlockedDecrement (p->lconv_intl_refcount);

  if (p->lconv_num_refcount)
    InterlockedDecrement (p->lconv_num_refcount);

  if (p->lconv_mon_refcount)
    InterlockedDecrement (p->lconv_mon_refcount);

  if (p->ctype1_refcount)
    InterlockedDecrement (p->ctype1_refcount);

  for (i = 0; i < 6; i++)
    {
      if (p->lc_category[i].locale != __ic_str_C
	  && p->lc_category[i].refcount)
	InterlockedDecrement (p->lc_category[i].refcount);
      if (p->lc_category[i].wlocale
	  && p->lc_category[i].wrefcount)
	InterlockedDecrement (p->lc_category[i].wrefcount);
    }

  if (p->lc_time_curr)
    InterlockedDecrement (&p->lc_time_curr->refcount);

  return p;
}

