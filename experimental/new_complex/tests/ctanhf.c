#include <math.h>
#include <complex.h>

/*
  ctanh (+0 + i*0) = +0 + i*0
  ctanh (x + i*inf) = nan + i*nan for finite x
  ctanh (x + i*nan) = nan + i*nan for finite x
  ctanh (+inf + i*y) = 1 + i*0*sin(2y) for positive-signed finite y
  ctanh (+inf + i*inf) = 1 +/- i*0 (unspecified sign of zero for C99)
  ctanh (+inf + i*nan) = 1 +/- i*0 (unspecified sign of zero for C99)
  ctanh (nan + i*0) = nan + i*0
  ctanh (nan + i*y) = nan + i*nan for all nonzero y
  ctanh (nan + i*nan) = nan + i*nan
*/

int main() {
  return 0;
}

