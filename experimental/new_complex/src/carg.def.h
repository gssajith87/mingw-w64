__FCT_TYPE __cdecl
__FCT_ABIEXT(carg) (__FCT_TYPE __complex__ z)
{
  return __FCT_ABIEXT(atan2) (__imag__ z, __real__ z);
}
