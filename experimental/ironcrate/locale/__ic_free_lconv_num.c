#include <ic_stdc.h>

void __cdecl
__ic_free_lconv_num (struct ic_lconv_t *l)
{
  if (!l)
    return;

  if (l->decimal_point != __ic_lconv_c.decimal_point)
    ic_free (l->decimal_point);

  if (l->grouping != __ic_lconv_c.grouping)
    ic_free (l->grouping);

  if (l->thousands_sep != __ic_lconv_c.thousands_sep)
    ic_free (l->thousands_sep);
}

