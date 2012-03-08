#include <ic_stdc.h>

/* MS uses here a linear congruential scheme. The function is multiplying and
   adding to a number, which is taken module 2^32, and returning the upper
   16 bit as "random" number.
   Because it is multiplying and adding numbers, which are coprime to the
   modulus, this creates a sort of uniformaly distributed numbers.
   Base function is a linear function f(x) = ((x * prime-1) + prime-2) % 2^32.
   The final result is (f(x) >> 16) & 0x7fff;
   The prime-1 is 214013, and the prime-2 is 2531011.
   */
int __cdecl
ic_rand (void)
{
  ic_thrdata_t p = _ic_getthrdata ();

  p->_holdrand = p->_holdrand * 214013 + 2531011;

  return (p->_holdrand >> 16) & 0x7fff;
}

