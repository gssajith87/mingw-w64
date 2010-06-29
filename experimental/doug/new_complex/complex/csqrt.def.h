__FLT_TYPE __complex__ __cdecl
__FLT_ABI(csqrt) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE d, r, s;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FLT_HUGE_VAL;
      __imag__ ret = __imag__ z;
      return ret;
    }

    if (r_class == FP_INFINITE)
    {
      if (__real__ z < __FLT_CST(0.0))
      {
	__real__ ret = i_class == FP_NAN ? __FLT_NAN : __FLT_CST(0.0);
	__imag__ ret = __FLT_ABI(copysign) (__FLT_HUGE_VAL, __imag__ z);
	return ret;
      }

      __real__ ret = __real__ z;
      __imag__ ret = (i_class == FP_NAN
	? __FLT_NAN : __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z));
      return ret;
    }

    __real__ ret = __FLT_NAN;
    __imag__ ret = __FLT_NAN;
    return ret;
  }

  if (i_class == FP_ZERO)
  {
    if (__real__ z < __FLT_CST(0.0))
    {
      __real__ ret = __FLT_CST(0.0);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_ABI(sqrt) (-__real__ z), __imag__ z);
    }
    else
    {
      __real__ ret = __FLT_ABI(fabs) (__FLT_ABI(sqrt) (__real__ z));
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    }
    return ret;
  }

  if (r_class == FP_ZERO)
  {
    r = __FLT_ABI(sqrt) (__FLT_CST(0.5) * __FLT_ABI(fabs) (__imag__ z));

    __real__ ret = r;
    __imag__ ret = __FLT_ABI(copysign) (r, __imag__ z);
    return ret;
  }

  d = __FLT_ABI(hypot) (__real__ z, __imag__ z);
  if (__real__ z > __FLT_CST(0.0))
  {
    r = __FLT_ABI(sqrt) (__FLT_CST(0.5) * d + __FLT_CST(0.5) * __real__ z);
    s = (__FLT_CST(0.5) * __imag__ z) / r;
  }
  else
  {
    s = __FLT_ABI(sqrt) (__FLT_CST(0.5) * d - __FLT_CST(0.5) * __real__ z);
    r = __FLT_ABI(fabs) ((__FLT_CST(0.5) * __imag__ z) / s);
  }

  __real__ ret = r;
  __imag__ ret = __FLT_ABI(copysign) (s, __imag__ z);

  return ret;
}
