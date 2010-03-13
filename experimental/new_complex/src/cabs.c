#include <complex.h>

double
cabs (double complex z)
{
  return _hypot (__real__ z, __imag__ z);
}

float
cabsf (float complex z)
{
  return (float) _hypot (__real__ z, __imag__ z);
}

long double
cabsl (long double complex z)
{
  return hypotl (__real__ z, __imag__ z);
}
