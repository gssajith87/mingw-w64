__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(csin) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  int negate = signbit (__real__ z);
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  __real__ z = __FCT_ABIEXT(fabs) (__real__ z);

  if (i_class != FP_NAN && i_class != FP_INFINITE)
  {
    if (r_class != FP_NAN && r_class != FP_INFINITE)
    {
      __FCT_TYPE s_x, c_x;

      __FCT_ABIEXT(sincos) (__real__ z, &s_x, &c_x);

      __real__ ret = __FCT_ABIEXT(cosh) (__imag__ z) * s_x;
      __imag__ ret = __FCT_ABIEXT(sinh) (__imag__ z) * c_x;

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      if (i_class == FP_ZERO)
      {
	__real__ ret = __FCT_NAN;
	__imag__ ret = __imag__ z;
      }
      else
      {
	__real__ ret = __FCT_NAN;
	__imag__ ret = __FCT_NAN;
      }
    }
  }
  else if (i_class == FP_INFINITE)
  {
    if (r_class == FP_ZERO)
    {
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), negate ? -__FCT_CSTEXT(1.0) : __FCT_CSTEXT(1.0));
      __imag__ ret = __imag__ z;
    }
    else if (r_class > FP_ZERO)
    {
      __FCT_TYPE s_x, c_x;

      __FCT_ABIEXT(sincos) (__real__ z, &s_x, &c_x);

      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, s_x);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, c_x);

      if (negate)
	__real__ ret = -__real__ ret;
      if (signbit (__imag__ z))
	__imag__ ret = -__imag__ ret;
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_HUGE_VAL;
    }
  }
  else
  {
    if (r_class == FP_ZERO)
      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), negate ? -__FCT_CSTEXT(1.0) : __FCT_CSTEXT(1.0));
    else
      __real__ ret = __FCT_NAN;
    __imag__ ret = __FCT_NAN;
  }

  return ret;
}
