__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(cproj) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  __FCT_TYPE d;

  if (isnan (__real__ z) && isnan (__imag__ z))
    return z;

  if (!isfinite (__real__ z) || !isfinite (__imag__ z))
  {
    __real__ ret = INFINITY;
    __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
    return ret;
  }

  d = __real__ z * __real__ z + __imag__ z * __imag__ z + __FCT_CSTEXT(1.0);

  __real__ ret = (__FCT_CSTEXT(2.0) * __real__ z) / d;
  __imag__ ret = (__FCT_CSTEXT(2.0) * __imag__ z) / d;

  return ret;
}
