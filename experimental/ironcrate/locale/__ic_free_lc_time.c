#include <ic_stdc.h>

void __cdecl
__ic_free_lc_time (ic_lc_timedate_t *l)
{
  int i;
  if (!l)
    return;

  ic_free (l->ww_sdatefmt);
  ic_free (l->ww_ldatefmt);
  ic_free (l->ww_timefmt);

  ic_free (l->ampm[0]);
  ic_free (l->ampm[1]);

  for (i = 0; i < 7; i++)
    {
      ic_free (l->wday_abbr[i]);
      ic_free (l->wday[i]);
    }

  for (i = 0; i < 12; i++)
    {
      ic_free (l->month_abbr[i]);
      ic_free (l->month[i]);
    }
}

