__FLT_TYPE __complex__ __cdecl
__FLT_ABI(catanh) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE i2, n, d;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __real__ z);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_PI_2, __imag__ z);
      return ret;
    }

    if (r_class == FP_INFINITE || r_class == FP_ZERO)
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __real__ z);
      __imag__ ret = ((i_class != FP_NAN && i_class != FP_INFINITE)
        ? __FLT_ABI(copysign) (__FLT_PI_2, __imag__ z) : __FLT_NAN);
      return ret;
    }

    __real__ ret = __FLT_NAN;
    __imag__ ret = __FLT_NAN;
    return ret;
  }

  if (r_class == FP_ZERO && i_class == FP_ZERO)
    return z;

  i2 = __imag__ z * __imag__ z;

  n = __FLT_CST(1.0) + __real__ z;
  n = i2 + n * n;

  d = __FLT_CST(1.0) - __real__ z;
  d = i2 + d * d;

  __real__ ret = __FLT_CST(0.25) * (__FLT_ABI(log) (n) - __FLT_ABI(log) (d));

  d = 1 - __real__ z * __real__ z - i2;

  __imag__ ret = __FLT_CST(0.5) * __FLT_ABI(atan2) (__FLT_CST(2.0) * __imag__ z, d);

  return ret;
}
