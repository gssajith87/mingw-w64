#include <icrt.h>
#include "aligned.h"

void
__iCrt_aligned_free (void *ptr)
{
  if (ptr)
    {
        void **saved = SAVED_PTR (ptr);
        __iCrt_free (*saved);
    }
}
