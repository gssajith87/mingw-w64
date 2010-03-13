#include <math.h>
#include <complex.h>

double
cimag (double complex z)
{
  return __imag__ z;
}

float
cimagf (float complex z)
{
  return __imag__ z;
}

long double
cimagl (long double complex z)
{
  return __imag__ z;
}
