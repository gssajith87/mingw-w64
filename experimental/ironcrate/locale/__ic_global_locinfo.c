#include <ic_stdc.h>

ic_threadlocinfo_t
__ic_global_locinfo =
{
  1, CP_ACP, CP_ACP,
  { 0, 0, 0, 0, 0, 0 },
  { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
    { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
  { { NULL, NULL, NULL, NULL }, { __ic_str_C, NULL, NULL, NULL },
    { __ic_str_C, NULL, NULL, NULL }, { __ic_str_C, NULL, NULL, NULL },
    { __ic_str_C, NULL, NULL, NULL }, { __ic_str_C, NULL, NULL, NULL } },
  1, 1,
  NULL, NULL, NULL,
  &__ic_lconv_c,
  NULL, NULL,
  __ic_newctype + 128,
  __ic_newclmap + 128,
  __ic_newcumap + 128,
  &__ic_lc_time_c,
};

