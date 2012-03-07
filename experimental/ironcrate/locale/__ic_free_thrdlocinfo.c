#include <ic_stdc.h>

void __cdecl
__ic_free_thrdlocinfo (ic_threadlocinfo_t *p)
{
  int i;

  if (p->lconv && p->lconv != &__ic_lconv_c
      && p->lconv_intl_refcount
      && p->lconv_intl_refcount[0] == 0)
    {
      if (p->lconv_mon_refcount && p->lconv_mon_refcount[0] == 0)
	{
	  ic_free (p->lconv_mon_refcount);
	  __ic_free_lconv_mon (p->lconv);
	}

      if (p->lconv_num_refcount && p->lconv_num_refcount[0] == 0)
	{
	  ic_free (p->lconv_num_refcount);
	  __ic_free_lconv_num (p->lconv);
	}

      ic_free (p->lconv_intl_refcount);
      ic_free (p->lconv);
    }

  if (p->lc_time_curr != &__ic_lc_time_c
      && p->lc_time_curr->refcount == 0)
    {
      __ic_free_lc_time (p->lc_time_curr);
      ic_free (p->lc_time_curr);
    }

  if (p->ctype1_refcount
      && p->ctype1_refcount[0] == 0)
    {
      ic_free ((char *) (p->ctype1) - 127);
      ic_free ((char *) p->pclmap - 128);
      ic_free ((char *) p->pcumap - 128);
      ic_free (p->ctype1_refcount);
    }

  for (i = 0; i < 6; i++)
    {
      if (p->lc_category[i].locale != __ic_str_C
	  && p->lc_category[i].refcount
	  && p->lc_category[i].refcount[0] == 0)
	ic_free (p->lc_category[i].refcount);

      if (p->lc_category[i].wlocale
	  && p->lc_category[i].wrefcount
	  && p->lc_category[i].wrefcount[0] == 0)
	ic_free (p->lc_category[i].wrefcount);
    }

  ic_free (p);
}

