#define _POSIX
#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
 complex long double z = 1.1 + I*-1.1, res;
 res = cacoshl (z);
 printf("%10.8Lf + I* %10.8Lf\n", creall(res), cimagl(res));
 res = clogl (z + csqrtl (z-1.0L) * csqrtl (z+1.0L));
 printf("%10.8Lf + I* %10.8Lf\n", creall(res), cimagl(res));
 return 0;
}

