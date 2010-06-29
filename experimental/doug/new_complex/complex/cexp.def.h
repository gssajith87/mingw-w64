__FLT_TYPE __complex__ __cdecl
__FLT_ABI(cexp) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE s_x, c_x, exp_val, v;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE)
  {
    if (i_class != FP_NAN && i_class != FP_INFINITE)
    {
      v = signbit (__real__ z) ? __FLT_CST(0.0) : __FLT_HUGE_VAL;

      if (i_class == FP_ZERO)
      {
	__real__ ret = v;
	__imag__ ret = __imag__ z;
	return ret;
      }

      __FLT_ABI(sincos) (__imag__ z, &s_x, &c_x);

      __real__ ret = __FLT_ABI(copysign) (v, c_x);
      __imag__ ret = __FLT_ABI(copysign) (v, s_x);
      return ret;
    }

    if (signbit (__real__ z) == 0)
    {
      __real__ ret = __FLT_HUGE_VAL;
      __imag__ ret = __FLT_NAN;
    }
    else
    {
      __real__ ret = __FLT_CST(0.0);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    }
    return ret;
  }

  if (r_class == FP_NAN || i_class == FP_NAN || i_class == FP_INFINITE)
  {
    __real__ ret = __FLT_NAN;
    __imag__ ret = __FLT_NAN;
    return ret;
  }

  exp_val = __FLT_ABI(exp) (__real__ z);

  __FLT_ABI(sincos) (__imag__ z, &s_x, &c_x);

  if (isfinite (exp_val))
  {
    __real__ ret = exp_val * c_x;
    __imag__ ret = exp_val * s_x;
  }
  else
  {
    __real__ ret = __FLT_ABI(copysign) (exp_val, c_x);
    __imag__ ret = __FLT_ABI(copysign) (exp_val, s_x);
  }
  return ret;
}
