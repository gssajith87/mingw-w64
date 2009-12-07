#include <w64crt.h>
#include "aligned.h"

void *
__w64crt_aligned_offset_realloc (void *ptr, size_t sz, size_t align, size_t off)
{
  void *tmp, **savep;
  size_t pad_old, pad_new, sz_old;

  if (!ptr)
    return __w64crt_aligned_offset_malloc (sz, align, off);

  if ((align & (align - 1)) != 0 || off >= sz)
    {
      __w64crt_set_errno(EINVAL);
      return NULL;
    }

  if (!sz)
    {
      __w64crt_aligned_free (ptr);
        return NULL;
    }

  if (align < sizeof (void *))
    align = sizeof (void *);

  savep = (void **) SAVED_PTR (ptr);
  if (ptr != ALIGN_PTR(*savep, align, off))
    {
      __w64crt_set_errno (EINVAL);
      return NULL;
    }

  pad_old = (char *) ptr - (char *) *savep;
  sz_old = _msize (*savep);
  if (sz_old == SZ_MINUSONE || sz_old < pad_old)
    {
      __w64crt_set_errno (EINVAL);
      return NULL;
    }

  sz_old -= pad_old;

  tmp = __w64crt_realloc (*savep, sz + align + sizeof (void *));

  if (!tmp)
    return NULL;

  ptr = ALIGN_PTR (tmp, align, off);
  savep = (void **) SAVED_PTR (ptr);
  pad_new = (char *) ptr - (char *) tmp;

  if (pad_new != pad_old)
    memmove ((char *) ptr, (char *) tmp + pad_old, (sz_old < sz ? sz_old : sz));

  *savep = tmp;
  return ptr;
}
