__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(casin) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  __complex__ __FCT_TYPE x;

  if (isnan (__real__ z) || isnan (__imag__ z))
  {
    if (__real__ z == __FCT_CSTEXT(0.0))
    {
      ret = z;
    }
    else if (isinf (__real__ z) || isinf (__imag__ z))
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, __imag__ z);
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
    return ret;
  }

  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  x = __FCT_ABIEXT(casinh) (x);

  __real__ ret = __imag__ x;
  __imag__ ret = -__real__ x;

  return ret;
}
