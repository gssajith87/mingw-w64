__FLT_TYPE __complex__ __cdecl
__FLT_ABI(ccos) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE x;

  if (!isfinite (__real__ z) || __isnan (__imag__ z))
  {
    __complex__ __FLT_TYPE ret;
    if (__real__ z == __FLT_CST(0.0) || __imag__ z == __FLT_CST(0.0))
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_CST(0.0);
    }
    else
    {
      __imag__ ret = __FLT_NAN;
      __real__ ret =  (isinf (__imag__ z) ? __FLT_HUGE_VAL : __FLT_NAN);
    }
    return ret;
  }

  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  return __FLT_ABI(ccosh) (x);
}
