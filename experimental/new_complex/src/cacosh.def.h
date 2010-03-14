__FLT_TYPE __complex__ __cdecl
__FLT_ABI(cacosh) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __complex__ __FLT_TYPE x;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FLT_HUGE_VAL;
      __imag__ ret = (r_class == FP_NAN ? __FLT_NAN : __FLT_ABI(copysign) (
	(r_class == FP_INFINITE ? (__real__ z < __FLT_CST(0.0) ? __FLT_PI_3_4 : __FLT_PI_4) : __FLT_PI_2), __imag__ z));
    }
    else if (r_class == FP_INFINITE)
    {
      __real__ ret = __FLT_HUGE_VAL;
      __imag__ ret = ((i_class != FP_NAN && i_class != FP_INFINITE)
	? __FLT_ABI(copysign) (signbit (__real__ z) ? __FLT_PI : __FLT_CST(0.0), __imag__ z) : __FLT_NAN);
    }
    else
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_NAN;
    }
    return ret;
  }

  if (r_class == FP_ZERO && i_class == FP_ZERO)
  {
    __real__ ret = __FLT_CST(0.0);
    __imag__ ret = __FLT_ABI(copysign) (__FLT_PI_2, __imag__ z);
    return ret;
  }

  __real__ x = (__real__ z - __imag__ z) * (__real__ z + __imag__ z) - __FLT_CST(1.0);
  __imag__ x = __FLT_CST(2.0) * __real__ z * __imag__ z;

  x = __FLT_ABI(csqrt) (x);

  if (__real__ z < __FLT_CST(0.0))
    x = -x;

  __real__ x += __real__ z;
  __imag__ x += __imag__ z;

  ret = __FLT_ABI(clog) (x);

  if (__real__ ret < __FLT_CST(0.0))
    ret = -ret;

  return ret;
}
