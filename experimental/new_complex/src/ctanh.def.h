__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(ctanh) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;

  if (!isfinite (__real__ z) || !isfinite (__imag__ z))
  {
    if (isinf (__real__ z))
    {
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(1.0), __real__ z);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
    }
    else if (__imag__ z == __FCT_CSTEXT(0.0))
      ret = z;
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
  }
  else
  {
    __FCT_TYPE s, c, d;

    __FCT_ABIEXT(sincos) (__FCT_CSTEXT(2.0) * __imag__ z, &s, &c);

    d = (__FCT_ABIEXT(cosh) (__FCT_CSTEXT(2.0) * __real__ z) + c);

    if (d == __FCT_CSTEXT(0.0))
    {
      __complex__ __FCT_TYPE ez = __FCT_ABIEXT(cexp) (z);
      __complex__ __FCT_TYPE emz = __FCT_ABIEXT(cexp) (-z);

      ret = (ez - emz) / (ez + emz);
    }
    else
    {
      __real__ ret = __FCT_ABIEXT(sinh) (__FCT_CSTEXT(2.0) * __real__ z) / d;
      __imag__ ret = s / d;
    }
  }

  return ret;
}
