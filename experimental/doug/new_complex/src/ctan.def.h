__FLT_TYPE __complex__ __cdecl
__FLT_ABI(ctan) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE s, c, d;

  if (!isfinite (__real__ z) || !isfinite (__imag__ z))
  {
    if (isinf (__imag__ z))
    {
      __real__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __real__ z);
      __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(1.0), __imag__ z);
      return ret;
    }
    if (__real__ z == __FLT_CST(0.0))
      return z;

    __real__ ret = __FLT_NAN;
    __imag__ ret = __FLT_NAN;
    return ret;
  }

  __FLT_ABI(sincos) (__FLT_CST(2.0) * __real__ z, &s, &c);

  d = c + __FLT_ABI(cosh) (__FLT_CST(2.0) * __imag__ z);

  if (d == __FLT_CST(0.0))
  {
    __complex__ __FLT_TYPE ez = __FLT_ABI(cexp) (1.0i * z);
    __complex__ __FLT_TYPE emz = __FLT_ABI(cexp) (-1.0i * z);

    return (ez - emz) / (ez + emz) * -1.0i;
  }
  __real__ ret = s / d;
  __imag__ ret = __FLT_ABI(sinh) (__FLT_CST(2.0) * __imag__ z) / d;

  return ret;
}
