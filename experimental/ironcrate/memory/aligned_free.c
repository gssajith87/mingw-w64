#include <icrt.h>
#include "aligned.h"

void
__w64crt_aligned_free_0_0 (void *ptr)
{
  if (ptr)
    {
        void **saved = SAVED_PTR (ptr);
        __w64crt_free (*saved);
    }
}
