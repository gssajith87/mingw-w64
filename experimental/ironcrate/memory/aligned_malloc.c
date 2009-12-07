#include <icrt.h>
#include "aligned.h"

void *
__w64crt_aligned_malloc_0_0 (size_t sz, size_t align)
{
  return __w64crt_aligned_offset_malloc (sz, align, 0);
}
