__FLT_TYPE __complex__ __cdecl
__FLT_ABI(csin) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE s_x, c_x;
  int negate = signbit (__real__ z);
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  __real__ z = __FLT_ABI(fabs) (__real__ z);

  if (i_class != FP_NAN && i_class != FP_INFINITE)
  {
    if (r_class != FP_NAN && r_class != FP_INFINITE)
    {
      __FLT_ABI(sincos) (__real__ z, &s_x, &c_x);

      __real__ ret = __FLT_ABI(cosh) (__imag__ z) * s_x;
      __imag__ ret = __FLT_ABI(sinh) (__imag__ z) * c_x;

      if (negate)
	__real__ ret = -__real__ ret;
    }
    else
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = (i_class == FP_ZERO ? __imag__ z : __FLT_NAN);
    }
    return ret;
  }

  if (i_class == FP_INFINITE)
  {
    if (r_class == FP_ZERO)
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), negate ? -__FLT_CST(1.0) : __FLT_CST(1.0));
      __imag__ ret = __imag__ z;
    }
    else if (r_class > FP_ZERO)
    {
      __FLT_ABI(sincos) (__real__ z, &s_x, &c_x);

      __real__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, s_x);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, c_x);

      if (negate)
	__real__ ret = -__real__ ret;
      if (signbit (__imag__ z))
	__imag__ ret = -__imag__ ret;
    }
    else
    {
      __real__ ret = __FLT_NAN;
      __imag__ ret = __FLT_HUGE_VAL;
    }
    return ret;
  }

  __real__ ret = (r_class == FP_ZERO ?
    (__FLT_ABI(copysign) (__FLT_CST(0.0), negate ? -__FLT_CST(1.0) : __FLT_CST(1.0)))
    : __FLT_NAN);
  __imag__ ret = __FLT_NAN;

  return ret;
}

