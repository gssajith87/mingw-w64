__FLT_TYPE __complex__ __cdecl
__FLT_ABI(casinh) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __complex__ __FLT_TYPE x;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, __real__ z);

      if (r_class == FP_NAN)
	__imag__ ret = __FLT_NAN;
      else
	__imag__ ret = __FLT_ABI(copysign) ((r_class != FP_NAN && r_class != FP_INFINITE) ? __FLT_PI_2 : __FLT_PI_4, __imag__ z);
    }
    else if (r_class == FP_INFINITE || r_class == FP_NAN)
    {
      __real__ ret = __real__ z;
      if ((r_class == FP_INFINITE && !(i_class == FP_NAN || i_class == FP_INFINITE))
	|| (r_class == FP_NAN && i_class == FP_ZERO))
	__imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
      else
	__imag__ ret = __FLT_NAN;
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

  __real__ x = (__real__ z - __imag__ z) * (__real__ z + __imag__ z) + __FLT_CST(1.0);
  __imag__ x = __FLT_CST(2.0) * __real__ z * __imag__ z;

  x = __FLT_ABI(csqrt) (x);

  __real__ x += __real__ z;
  __imag__ x += __imag__ z;

  return __FLT_ABI(clog) (x);
}
