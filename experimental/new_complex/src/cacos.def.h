__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(cacos) (__FCT_TYPE __complex__ z)
{
  __complex__ __FCT_TYPE x;
  __complex__ __FCT_TYPE ret;

  x = __FCT_ABIEXT(casin) (z);

  __real__ ret = (__FCT_TYPE) __FCT_M_PI_2 - __real__ x;
  __imag__ ret = -__imag__ x;

  return ret;
}
