#include <math.h>
#include <complex.h>
#include "compare_flt.c"

int main() {
  const complex double test = 3.0 + 4.0I;
  double result = cabs (test);
  return compare_dbl(5.0, result);
}

