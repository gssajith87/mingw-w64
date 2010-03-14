__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(clog) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE result;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_ZERO && i_class == FP_ZERO)
  {
    __imag__ result = signbit (__real__ z) ? __FCT_M_PI : __FCT_CSTEXT(0.0);
    __imag__ result = __FCT_ABIEXT(copysign) (__imag__ result, __imag__ z);
    __real__ result = -__FCT_CSTEXT(1.0) / __FCT_ABIEXT(fabs) (__real__ z);
    return ret;
  }

  if (r_class != FP_NAN && i_class != FP_NAN)
  {
    __real__ result = __FCT_ABIEXT(log) (__FCT_ABIEXT(hypot) (__real__ z, __imag__ z));
    __imag__ result = __FCT_ABIEXT(atan2) (__imag__ z, __real__ z);
    return ret;
  }

  __imag__ result = __FCT_NAN;
  __real__ result = (r_class == FP_INFINITE || i_class == FP_INFINITE ? __FCT_HUGE_VAL : __FCT_NAN);

  return result;
}
