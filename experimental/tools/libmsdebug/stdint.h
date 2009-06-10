#ifndef STDINT_HXX
#define STDINT_HXX

#ifndef __GNUC__
#define __extension__
#define __attribute__(G)

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#else
#include <stdint.h>
#endif
#endif

