#include <icrt.h>

static unsigned int __w64crt_amblksize = 16;

unsigned int *
__w64crt_p__amblksize (void)
{
  return &__w64crt_amblksize;
}
