__FLT_TYPE __complex__ __cdecl
__FLT_ABI(cpow) (__FLT_TYPE __complex__ z, __FLT_TYPE __complex__ x)
{
  return __FLT_ABI(cexp) (x * __FLT_ABI(clog) (z));
}
