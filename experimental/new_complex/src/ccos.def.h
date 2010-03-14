__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(ccos) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE x;

  if (!isfinite (__real__ z) || __isnan (__imag__ z))
  {
    __complex__ __FCT_TYPE ret;
    if (__real__ z == __FCT_CSTEXT(0.0) || __imag__ z == __FCT_CSTEXT(0.0))
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_CSTEXT(0.0);
    }
    else
    {
      __imag__ ret = __FCT_NAN;
      __real__ ret =  (isinf (__imag__ z) ? __FCT_HUGE_VAL : __FCT_NAN);
    }
    return ret;
  }

  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  return __FCT_ABIEXT(ccosh) (x);
}
