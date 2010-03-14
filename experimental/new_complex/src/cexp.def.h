__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(cexp) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class != FP_NAN && r_class != FP_INFINITE)
  {
    if (i_class != FP_NAN && i_class != FP_INFINITE)
    {
      __FCT_TYPE exp_val = __FCT_ABIEXT(exp) (__real__ z);
      __FCT_TYPE s_x, c_x;

      __FCT_ABIEXT(sincos) (__imag__ z, &s_x, &c_x);

      if (isfinite (exp_val))
      {
	__real__ ret = exp_val * c_x;
	__imag__ ret = exp_val * s_x;
      }
      else
      {
	__real__ ret = __FCT_ABIEXT(copysign) (exp_val, c_x);
	__imag__ ret = __FCT_ABIEXT(copysign) (exp_val, s_x);
      }
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
    return ret;
  }

  if (r_class == FP_INFINITE)
  {
    if (i_class != FP_NAN && i_class != FP_INFINITE)
    {
      __FCT_TYPE value = signbit (__real__ z) ? __FCT_CSTEXT(0.0) : __FCT_HUGE_VAL;

      if (i_class == FP_ZERO)
      {
	__real__ ret = value;
	__imag__ ret = __imag__ z;
      }
      else
      {
	__FCT_TYPE s_x, c_x;

	__FCT_ABIEXT(sincos) (__imag__ z, &s_x, &c_x);

	__real__ ret = __FCT_ABIEXT(copysign) (value, c_x);
	__imag__ ret = __FCT_ABIEXT(copysign) (value, s_x);
      }
    }
    else if (signbit (__real__ z) == 0)
    {
      __real__ ret = __FCT_HUGE_VAL;
      __imag__ ret = __FCT_NAN;
    }
    else
    {
      __real__ ret = __FCT_CSTEXT(0.0);
      __imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
    }
    return ret;
  }

  __real__ ret = __FCT_NAN;
  __imag__ ret = __FCT_NAN;

  return ret;
}
