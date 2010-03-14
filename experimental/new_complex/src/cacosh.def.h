__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(cacosh) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  __complex__ __FCT_TYPE x;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FCT_HUGE_VAL;
      __imag__ ret = (r_class == FP_NAN ? __FCT_NAN
	: __FCT_ABIEXT(copysign) (
	(r_class == FP_INFINITE ?
	(__real__ z < __FCT_CSTEXT(0.0) ? __FCT_M_PI_3_4 : __FCT_M_PI_4) : __FCT_M_PI_2), __imag__ z));
    }
    else if (r_class == FP_INFINITE)
    {
      __real__ ret = __FCT_HUGE_VAL;
      __imag__ ret = ((i_class != FP_NAN && i_class != FP_INFINITE)
	? __FCT_ABIEXT(copysign) (signbit (__real__ z) ? __FCT_M_PI : __FCT_CSTEXT(0.0), __imag__ z) : __FCT_NAN);
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
    return ret;
  }

  if (r_class == FP_ZERO && i_class == FP_ZERO)
  {
    __real__ ret = __FCT_CSTEXT(0.0);
    __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_M_PI_2, __imag__ z);
    return ret;
  }

  __real__ x = (__real__ z - __imag__ z) * (__real__ z + __imag__ z) - __FCT_CSTEXT(1.0);
  __imag__ x = __FCT_CSTEXT(2.0) * __real__ z * __imag__ z;

  x = __FCT_ABIEXT(csqrt) (x);

  if (__real__ z < __FCT_CSTEXT(0.0))
    x = -x;

  __real__ x += __real__ z;
  __imag__ x += __imag__ z;

  ret = __FCT_ABIEXT(clog) (x);

  if (__real__ ret < __FCT_CSTEXT(0.0))
    ret = -ret;

  return ret;
}
