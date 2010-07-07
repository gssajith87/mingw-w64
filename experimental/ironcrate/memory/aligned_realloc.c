#include <icrt.h>
#include "aligned.h"

void *
__iCrt_aligned_realloc (void *ptr, size_t sz, size_t align)
{
  return __iCrt_aligned_offset_realloc (ptr, sz, align, (size_t) 0);
}
