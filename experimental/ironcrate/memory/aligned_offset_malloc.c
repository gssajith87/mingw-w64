#include <icrt.h>
#include "aligned.h"

void *
__iCrt_aligned_offset_malloc (size_t sz, size_t align, size_t off)
{
  void *ret, *tmp;

  if ((align & (align - 1)) != 0 || off >= sz)
    {
      __iCrt_set_errno (EINVAL);
      return NULL;
    }

  if (align < sizeof(void *))
    align = sizeof(void *);

  if ((tmp = __iCrt_malloc (sz + align + sizeof(void *))) == NULL)
    return NULL;

  ret = ALIGN_PTR (tmp, align, off);
  *((void **) SAVED_PTR (ret)) = tmp;

  return ret;
}
