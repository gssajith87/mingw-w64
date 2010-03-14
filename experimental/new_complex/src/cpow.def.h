__FCT_TYPE __complex__ __cdecl
__FCT_ABIEXT(cpow) (__FCT_TYPE __complex__ z, __FCT_TYPE __complex__ x)
{
  return __FCT_ABIEXT(cexp) (x * __FCT_ABIEXT(clog) (z));
}
