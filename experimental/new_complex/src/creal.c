#include <math.h>
#include <complex.h>

double
creal (double complex z)
{
  return __real__ z;
}

float
crealf (float complex z)
{
  return __real__ z;
}

long double
creall (long double complex z)
{
  return __real__ z;
}

