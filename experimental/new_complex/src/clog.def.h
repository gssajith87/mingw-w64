__FLT_TYPE __complex__ __cdecl
__FLT_ABI(clog) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_ZERO && i_class == FP_ZERO)
  {
    __imag__ ret = signbit (__real__ z) ? __FLT_PI : __FLT_CST(0.0);
    __imag__ ret = __FLT_ABI(copysign) (__imag__ ret, __imag__ z);
    __real__ ret = -__FLT_CST(1.0) / __FLT_ABI(fabs) (__real__ z);
    return ret;
  }

  if (r_class == FP_NAN || i_class == FP_NAN)
  {
    __imag__ ret = __FLT_NAN;
    __real__ ret = ((r_class == FP_INFINITE || i_class == FP_INFINITE) ? __FLT_HUGE_VAL : __FLT_NAN);

    return ret;
  }

  __real__ ret = __FLT_ABI(log) (__FLT_ABI(hypot) (__real__ z, __imag__ z));
  __imag__ ret = __FLT_ABI(atan2) (__imag__ z, __real__ z);
  return ret;
}
