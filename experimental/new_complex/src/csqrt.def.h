__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(csqrt) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE ret;
  int r_class = fpclassify (__real__ z);
  int i_class = fpclassify (__imag__ z);

  if (r_class == FP_INFINITE || r_class == FP_NAN || i_class == FP_INFINITE || i_class == FP_NAN)
  {
    if (i_class == FP_INFINITE)
    {
      __real__ ret = __FCT_HUGE_VAL;
      __imag__ ret = __imag__ z;
    }
    else if (r_class == FP_INFINITE)
    {
      if (__real__ z < __FCT_CSTEXT(0.0))
      {
	__real__ ret = i_class == FP_NAN ? __FCT_NAN : 0;
	__imag__ ret = __FCT_ABIEXT(copysign) (__FCT_HUGE_VAL, __imag__ z);
      }
      else
      {
	__real__ ret = __real__ z;
	__imag__ ret = (i_class == FP_NAN ? __FCT_NAN : __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z));
      }
    }
    else
    {
      __real__ ret = __FCT_NAN;
      __imag__ ret = __FCT_NAN;
    }
  }
  else
  {
    if (i_class == FP_ZERO)
    {
      if (__real__ z < __FCT_CSTEXT(0.0))
      {
	__real__ ret = __FCT_CSTEXT(0.0);
	__imag__ ret = __FCT_ABIEXT(copysign) (__FCT_ABIEXT(sqrt) (-__real__ z), __imag__ z);
      }
      else
      {
	__real__ ret = __FCT_ABIEXT(fabs) (__FCT_ABIEXT(sqrt) (__real__ z));
	__imag__ ret = __FCT_ABIEXT(copysign) (__FCT_CSTEXT(0.0), __imag__ z);
      }
    }
    else if (r_class == FP_ZERO)
    {
      __FCT_TYPE r = __FCT_ABIEXT(sqrt) (__FCT_CSTEXT(0.5) * __FCT_ABIEXT(fabs) (__imag__ z));

      __real__ ret = r;
      __imag__ ret = __FCT_ABIEXT(copysign) (r, __imag__ z);
    }
    else
    {
      __FCT_TYPE d, r, s;

      d = __FCT_ABIEXT(hypot) (__real__ z, __imag__ z);
      if (__real__ z > 0)
      {
	r = __FCT_ABIEXT(sqrt) (__FCT_CSTEXT(0.5) * d + __FCT_CSTEXT(0.5) * __real__ z);
	s = (__FCT_CSTEXT(0.5) * __imag__ z) / r;
      }
      else
      {
	s = __FCT_ABIEXT(sqrt) (__FCT_CSTEXT(0.5) * d - __FCT_CSTEXT(0.5) * __real__ z);
	r = __FCT_ABIEXT(fabs) ((__FCT_CSTEXT(0.5) * __imag__ z) / s);
      }

      __real__ ret = r;
      __imag__ ret = __FCT_ABIEXT(copysign) (s, __imag__ z);
    }
  }

  return ret;
}
