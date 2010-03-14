__FLT_TYPE __complex__ __cdecl
__FLT_ABI(catan) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE r2, n, d;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (r_class == FP_INFINITE)
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_PI_2, __real__ z);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    }
    else if (i_class == FP_INFINITE)
    {
      if (!(r_class == FP_NAN || r_class == FP_INFINITE))
	__real__ ret = __FLT_ABI(copysign) (__FLT_PI_2, __real__ z);
      else
	__real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    }
    else if (i_class == FP_ZERO || i_class == FP_INFINITE)
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    }
    else
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_NAN;
    }
    return ret;
  }

  if (r_class == FP_ZERO && i_class == FP_ZERO)
    return z;

  r2 = __real__ z * __real__ z;

  d = 1 - r2 - __imag__ z * __imag__ z;

  __real__ ret = __FLT_CST(0.5) * __FLT_ABI(atan2) (__FLT_CST(2.0) * __real__ z, d);

  n = __imag__ z + __FLT_CST(1.0);
  n = r2 + n * n;

  d = __imag__ z - __FLT_CST(1.0);
  d = r2 + d * d;

  __imag__ ret = __FLT_CST(0.25) * __FLT_ABI(log) (n / d);

  return ret;
}
