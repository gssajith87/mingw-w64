__FCT_TYPE __cdecl
__FCT_ABIEXT(cabs) (__FCT_TYPE __complex__ z)
{
  return __FCT_ABIEXT(hypot) (__real__ z, __imag__ z);
}
