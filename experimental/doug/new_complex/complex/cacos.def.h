__FLT_TYPE __complex__ __cdecl
__FLT_ABI(cacos) (__FLT_TYPE __complex__ z)
{
  __complex__ __FLT_TYPE x;
  __complex__ __FLT_TYPE ret;

  x = __FLT_ABI(casin) (z);

  __real__ ret = (__FLT_TYPE) __FLT_PI_2 - __real__ x;
  __imag__ ret = -__imag__ x;

  return ret;
}
