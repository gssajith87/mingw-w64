#include <icrt.h>
#include "aligned.h"

void *
__iCrt_aligned_malloc (size_t sz, size_t align)
{
  return __iCrt_aligned_offset_malloc (sz, align, 0);
}
