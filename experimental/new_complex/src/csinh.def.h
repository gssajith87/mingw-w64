__FLT_TYPE __complex__ __cdecl
__FLT_ABI(csinh) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE s_x, c_x;
  int negate = signbit (__real__ z);
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  __real__ z = __FLT_ABI(fabs) (__real__ z);

  if (r_class != FP_NAN && r_class != FP_INFINITE)
  {
    if (i_class != FP_NAN && i_class != FP_INFINITE)
    {
      __FLT_ABI(sincos) (__imag__ z, &s_x, &c_x);

      __real__ ret = __FLT_ABI(sinh) (__real__ z) * c_x;
      __imag__ ret = __FLT_ABI(cosh) (__real__ z) * s_x;

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      if (r_class == FP_ZERO)
      {
	__real__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), negate ? -__FLT_CST(1.0) : __FLT_CST(1.0));
	__imag__ ret = __FLT_NAN + __FLT_NAN;
      }
      else
      {
	__real__ ret = __FLT_NAN;
	__imag__ ret = __FLT_NAN;
      }
    }
    return ret;
  }

  if (r_class == FP_INFINITE)
  {
    if (i_class == FP_ZERO)
    {
      __real__ ret = negate ? -__FLT_HUGE_VAL : __FLT_HUGE_VAL;
      __imag__ ret = __imag__ z;
    }
    else if (i_class > FP_ZERO)
    {
      __FLT_ABI(sincos) (__imag__ z, &s_x, &c_x);

      __real__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, c_x);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, s_x);

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      __real__ ret = __FLT_HUGE_VAL;
      __imag__ ret = __FLT_NAN + __FLT_NAN;
    }
    return ret;
  }

  __real__ ret = __FLT_NAN;
  __imag__ ret = __imag__ z == __FLT_CST(0.0) ? __imag__ z : __FLT_NAN;

  return ret;
}
