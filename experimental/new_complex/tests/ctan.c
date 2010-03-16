#include <math.h>
#include <complex.h>

/* ctan: ctan(-z) == -ctan(z) */
/* ctan: ctan(conj(z)) == conj (ctan (z)) */
/* ctan:
  ctan (+0 - i*0) = +0 - i*0
  ctan (+0 + i*0) = +0 + i*0
  ctan (-0 + i*0) = -0 + i*0
  ctan (-0 - i*0) = -0 - i*0
  ctan (inf - i*x) = nan + i*nan for finite x
  ctan (-inf + i*x) = nan + i*nan for finite x
  ctan (nan + i*x) = nan + i*nan for finite x
  ctan (y - i*inf) = 0*sin(2*y) - i*1 for positive-signed finite y
  ctan (y + i*inf) = 0*sin(2*y) + i*1
  ctan (-y + i*inf) = -0*sin(2*y) + i*1
  ctan (-y - i*inf) = -0*sin(2*y) - i*1
  ctan (+inf - i*inf) = +/-0 - i*1
  ctan (+inf + i*inf) = +/-0 + i*1
  ctan (-inf + i*inf) = +/-0 + i*1
  ctan (-inf - i*inf) = +/-0 - i*1
  ctan (nan  - i*inf) = +/-0 - i*1
  ctan (nan + i*inf) = +/-0 + i*1
  ctan (+0 + i*nan) = +0 + i*nan
  ctan (-0 + i*nan) = -0 + i*nan
  ctan (y + i*nan) = nan + i*nan for all nonzero y
*/

int main() {
  return 0;
}

