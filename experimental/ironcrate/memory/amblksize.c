#include <icrt.h>

static unsigned int __iCrt_amblksize = 16;

unsigned int *
__iCrt_p__amblksize (void)
{
  return &__iCrt_amblksize;
}
