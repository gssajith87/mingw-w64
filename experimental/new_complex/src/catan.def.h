__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(catan) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  __FCT_TYPE r2, n, d;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (r_class == FP_INFINITE)
    {
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_M_PI_2, __real__ z);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
    }
    else if (i_class == FP_INFINITE)
    {
      if (!(r_class == FP_NAN || r_class == FP_INFINITE))
	__real__ ret = __FCT_ABIEXT(copysign) (__FCT_M_PI_2, __real__ z);
      else
	__real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
    }
    else if (i_class == FP_ZERO || i_class == FP_INFINITE)
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
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

  r2 = __real__ z * __real__ z;

  d = 1 - r2 - __imag__ z * __imag__ z;

  __real__ ret = __FCT_CSTEXT(0.5) * __FCT_ABIEXT(atan2) (__FCT_CSTEXT(2.0) * __real__ z, d);

  n = __imag__ z + __FCT_CSTEXT(1.0);
  n = r2 + n * n;

  d = __imag__ z - __FCT_CSTEXT(1.0);
  d = r2 + d * d;

  __imag__ ret = __FCT_CSTEXT(0.25) * __FCT_ABIEXT(log) (n / d);

  return ret;
}
