#include "dfp_internal.h"
//todo: check with AC_C_BIGENDIAN ([action-if-true], [action-if-false], [action-if-unknown])
int __FLT_ABI(isinf) (__FLT_TYPE _X){
  unsigned char b;
  union {
  __FLT_TYPE d;
  unsigned char b[sizeof(__FLT_TYPE)];
  } u;
  u.d = _X;
#if (IS_BIG_ENDIAN)
  b = u.b[0];
#elif (IS_LITTLE_ENDIAN)
  b = u.b[sizeof(__FLT_TYPE)-1];
#else
#error Unsupported endian
#endif
  return (b & DECIMAL_NaN) == DECIMAL_Inf;
}
