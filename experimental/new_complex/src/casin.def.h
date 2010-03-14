__FLT_TYPE __complex__ __cdecl
__FLT_ABI(casin) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __complex__ __FLT_TYPE x;

  if (isnan (__real__ z) || isnan (__imag__ z))
  {
    if (__real__ z == __FLT_CST(0.0))
      return z;

    __real__ ret = __FLT_NAN;
    __imag__ ret = (isinf (__real__ z) || isinf (__imag__ z)
      ? __FLT_ABI(copysign) (__FLT_HUGE_VAL, __imag__ z) : __FLT_NAN);
    return ret;
  }

  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  x = __FLT_ABI(casinh) (x);

  __real__ ret = __imag__ x;
  __imag__ ret = -__real__ x;

  return ret;
}
