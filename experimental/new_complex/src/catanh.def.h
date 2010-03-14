__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(catanh) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  __FCT_TYPE i2, n, d;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __real__ z);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_M_PI_2, __imag__ z);
    }
    else if (r_class == FP_INFINITE || r_class == FP_ZERO)
    {
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __real__ z);
      if (!(i_class == FP_NAN || i_class == FP_INFINITE))
	__imag__ ret = __FCT_ABIEXT(copysign) (__FCT_M_PI_2, __imag__ z);
      else
	__imag__ ret = __FCT_NAN;
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
    return ret;
  }

  if (r_class == FP_ZERO && i_class == FP_ZERO)
    return z;

  i2 = __imag__ z * __imag__ z;

  n = __FCT_CSTEXT(1.0) + __real__ z;
  n = i2 + n * n;

  d = __FCT_CSTEXT(1.0) - __real__ z;
  d = i2 + d * d;

  __real__ ret = __FCT_CSTEXT(0.25) * (__FCT_ABIEXT(log) (n) - __FCT_ABIEXT(log) (d));

  d = 1 - __real__ z * __real__ z - i2;

  __imag__ ret = __FCT_CSTEXT(0.5) * __FCT_ABIEXT(atan2) (__FCT_CSTEXT(2.0) * __imag__ z, d);

  return ret;
}
