__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(csinh) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  int negate = signbit (__real__ z);
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  __real__ z = __FCT_ABIEXT(fabs) (__real__ z);

  if (r_class != FP_NAN && r_class != FP_INFINITE)
  {
    if (i_class != FP_NAN && i_class != FP_INFINITE)
    {
      __FCT_TYPE s_x, c_x;

      __FCT_ABIEXT(sincos) (__imag__ z, &s_x, &c_x);

      __real__ ret = __FCT_ABIEXT(sinh) (__real__ z) * c_x;
      __imag__ ret = __FCT_ABIEXT(cosh) (__real__ z) * s_x;

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      if (r_class == FP_ZERO)
      {
	__real__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), negate ? -__FCT_CSTEXT(1.0) : __FCT_CSTEXT(1.0));
	__imag__ ret = __FCT_NAN + __FCT_NAN;
      }
      else
      {
	__real__ ret = __FCT_NAN;
	__imag__ ret = __FCT_NAN;
      }
    }
    return ret;
  }

  if (r_class == FP_INFINITE)
  {
    if (i_class == FP_ZERO)
    {
      __real__ ret = negate ? -__FCT_HUGE_VAL : __FCT_HUGE_VAL;
      __imag__ ret = __imag__ z;
    }
    else if (i_class > FP_ZERO)
    {
      __FCT_TYPE s_x, c_x;

      __FCT_ABIEXT(sincos) (__imag__ z, &s_x, &c_x);

      __real__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, c_x);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, s_x);

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      __real__ ret = __FCT_HUGE_VAL;
      __imag__ ret = __FCT_NAN + __FCT_NAN;
    }
    return ret;
  }

  __real__ ret = __FCT_NAN;
  __imag__ ret = __imag__ z == __FCT_CSTEXT(0.0) ? __imag__ z : __FCT_NAN;

  return ret;
}
