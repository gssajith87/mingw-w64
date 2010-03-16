#include <math.h>
#include <complex.h>
#include "compare_flt.c"

/* conj: ctan (conj (z)) == conj (ctan (z)) */

const complex double test[5] = {
  1.5L + 4.0IL,
  1.0L - 2.0IL,
  0.0L + 0.0IL,
  -1.0L + 2.0IL,
  -1.5L - 4.0IL
};

int main() {
  int i;
  for (i = 0; i < 5; i++) {
    if (compare_cldbl (ctanl (conjl (test[i])), conjl (ctanl (test[i]))))
      return 1;
  } 
  return 0;
}

