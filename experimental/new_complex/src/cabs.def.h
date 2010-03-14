__FLT_TYPE __cdecl
__FLT_ABI(cabs) (__FLT_TYPE __complex__ z)
{
  return __FLT_ABI(hypot) (__real__ z, __imag__ z);
}
