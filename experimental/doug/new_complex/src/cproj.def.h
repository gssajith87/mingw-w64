__FLT_TYPE __complex__ __cdecl
__FLT_ABI(cproj) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE ret;
  __FLT_TYPE d;

  if (isnan (__real__ z) && isnan (__imag__ z))
    return z;

  if (!isfinite (__real__ z) || !isfinite (__imag__ z))
  {
    __real__ ret = INFINITY;
    __imag__ ret = __FLT_ABI(copysign) (__FLT_CST(0.0), __imag__ z);
    return ret;
  }

  d = __real__ z * __real__ z + __imag__ z * __imag__ z + __FLT_CST(1.0);

  __real__ ret = (__FLT_CST(2.0) * __real__ z) / d;
  __imag__ ret = (__FLT_CST(2.0) * __imag__ z) / d;

  return ret;
}
