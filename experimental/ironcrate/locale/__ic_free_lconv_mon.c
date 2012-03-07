#include <ic_stdc.h>

void __cdecl
__ic_free_lconv_mon (struct ic_lconv_t *l)
{
  if (!l)
    return;

  if (l->int_curr_symbol != __ic_lconv_c.int_curr_symbol)
    ic_free (l->int_curr_symbol);

  if (l->currency_symbol != __ic_lconv_c.currency_symbol)
    ic_free (l->currency_symbol);

  if (l->mon_decimal_point != __ic_lconv_c.mon_decimal_point)
    ic_free (l->mon_decimal_point);

  if (l->mon_grouping != __ic_lconv_c.mon_grouping)
    ic_free (l->mon_grouping);

  if (l->mon_thousands_sep != __ic_lconv_c.mon_thousands_sep)
    ic_free (l->mon_thousands_sep);

  if (l->positive_sign != __ic_lconv_c.positive_sign)
    ic_free (l->positive_sign);

  if (l->negative_sign != __ic_lconv_c.negative_sign)
    ic_free (l->negative_sign);
}

