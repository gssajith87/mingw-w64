__FLT_TYPE __complex__ __cdecl
__FLT_ABI(ctanh) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE s, c, d;

  if (!isfinite (__real__ z) || !isfinite (__imag__ z))
  {
    if (isinf (__real__ z))
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_CST(1.0), __real__ z);
      /* fmod will return NaN if __imag__ z is infinity.  This is actually
         OK, because imaginary infinity returns a + or - zero (unspecified).
         for +x, sin (x) is negative if fmod (x, 2pi) > pi.
         for -x, sin (x) is positive if fmod (x, 2pi) < pi.  */
      s = __FLT_ABI(fmod) (__imag__ z, __FLT_PI);
      if (signbit (__imag__ z))
	__imag__ ret = (s < -__FLT_PI_2) ? 0.0 : -0.0;
      else
	__imag__ ret = (s > __FLT_PI_2) ? -0.0 : 0.0;
      return ret;
    }

    if (__imag__ z == __FLT_CST(0.0))
      return z;

    __real__ ret = __FLT_NAN;
    __imag__ ret = __FLT_NAN;
    return ret;
  }

  __FLT_ABI(sincos) (__FLT_CST(2.0) * __imag__ z, &s, &c);

  d = (__FLT_ABI(cosh) (__FLT_CST(2.0) * __real__ z) + c);

  if (d == __FLT_CST(0.0))
  {
    __complex__ __FLT_TYPE ez = __FLT_ABI(cexp) (z);
    __complex__ __FLT_TYPE emz = __FLT_ABI(cexp) (-z);

    return (ez - emz) / (ez + emz);
  }

  __real__ ret = __FLT_ABI(sinh) (__FLT_CST(2.0) * __real__ z) / d;
  __imag__ ret = s / d;
  return ret;
}
