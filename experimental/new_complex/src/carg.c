#include <math.h>
#include <complex.h>

/* carg?(z) = atan2?(__imag__ z, __real__ z);  */

double
carg (double complex z)
{
  double ret;

  __asm__ ("fpatan;"
           : "=t" (ret) : "0" (__real__ z), "u" (__imag__ z) : "st(1)");

  return ret;
}

float
cargf (float complex z)
{
  float ret;

  __asm__ ("fpatan;"
           : "=t" (ret) : "0" (__real__ z), "u" (__imag__ z) : "st(1)");

  return ret;
}

long double
cargl (long double complex z)
{
  long double ret;

  __asm__ ("fpatan;"
           : "=t" (ret) : "0" (__real__ z), "u" (__imag__ z) : "st(1)");

  return ret;
}

