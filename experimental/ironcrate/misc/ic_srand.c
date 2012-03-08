#include <ic_stdc.h>

void __cdecl
ic_srand (unsigned int seed)
{
  _ic_getthrdata ()->_holdrand = seed;
}

