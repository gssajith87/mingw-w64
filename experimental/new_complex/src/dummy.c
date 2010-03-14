#define _POSIX
#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
  complex double z = 1.1 + I*-1.1, res;
 res = cacosh (z);
 printf("%10.8f + I* %10.8f\n", creal(res), cimag(res));
 res = clog (z + csqrt (z-1.0) * csqrt (z+1.0));
 printf("%10.8f + I* %10.8f\n", creal(res), cimag(res));
 return 0;
}

