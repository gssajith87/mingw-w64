#include <math.h>
#include <complex.h>
#include "compare_flt.c"

/* conj: ctan (conj (z)) == conj (ctan (z)) */

const complex float test[5] = {
  1.5F + 4.0IF,
  1.0F - 2.0IF,
  0.0F + 0.0IF,
  -1.0F + 2.0IF,
  -1.5F - 4.0IF
};

int main() {
  int i;
  for (i = 0; i < 5; i++) {
    if (compare_cflt (ctanf (conjf (test[i])), conjf (ctanf (test[i]))))
      return 1;
  } 
  return 0;
}

