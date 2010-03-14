__FLT_TYPE __cdecl
__FLT_ABI(carg) (__FLT_TYPE __complex__ z)
{
  return __FLT_ABI(atan2) (__imag__ z, __real__ z);
}
