__FLT_TYPE __complex__ __cdecl
__FLT_ABI(ccos) (__FLT_TYPE __complex__ z)
{
  /* Annex G.6, ccos(z) = ccosh(iz) */
  __complex__ __FLT_TYPE x;
  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  return __FLT_ABI(ccosh) (x);
}
