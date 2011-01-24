#define _DFP32_FLOAT /* Dummy */
#include "dfp_internal.h"
#include <stdio.h>

_Decimal64 __cdecl __infd64(__UNUSED_PARAM(const char *_X)){
  const t64 v = {.b = 0x7800000000000000ULL};
  return v.a;
}

_Decimal128 __cdecl __infd128(__UNUSED_PARAM(const char *_X)){
  const t128 v = {.b = {.b = 0x7800000000000000ULL, .a = 0}};
  return v.a;
}

_Decimal32 __cdecl __infd32(__UNUSED_PARAM(const char *_X)){
  const t32 v = {.b = 0x78000000UL};
  return v.a;
}
