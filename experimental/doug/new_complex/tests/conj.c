#include <math.h>
#include <complex.h>
#include "compare_flt.c"

/* conj: ctan (conj (z)) == conj (ctan (z)) */

const complex double test[5] = {
  1.5 + 4.0I,
  1.0 - 2.0I,
  0.0 + 0.0I,
  -1.0 + 2.0I,
  -1.5 - 4.0I
};

int main() {
  int i;
  for (i = 0; i < 5; i++) {
    if (compare_cdbl (ctan (conj (test[i])), conj (ctan (test[i]))))
      return 1;
  } 
  return 0;
}

