#include <math.h>
#include <complex.h>

double
carg (double complex z)
{
  return atan2 (__imag__ z, __real__ z);
}

float
cargf (float complex z)
{
  return atan2f (__imag__ z, __real__ z);
}

long double
cargl (long double complex z)
{
  return atan2l (__imag__ z, __real__ z);
}

