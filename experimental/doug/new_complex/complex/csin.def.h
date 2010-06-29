__FLT_TYPE __complex__ __cdecl
__FLT_ABI(csin) (__FLT_TYPE __complex__ z)
{
  /* Annex G.6: csin(z) = -i csinh (iz) */
  __complex__ __FLT_TYPE ret;
  __complex__ __FLT_TYPE x;

  __real__ x = -__imag__ z;
  __imag__ x = __real__ z;

  x = __FLT_ABI(csinh) (x);

  __real__ ret = __imag__ x;
  __imag__ ret = -__real__ x;

  return ret;
}
