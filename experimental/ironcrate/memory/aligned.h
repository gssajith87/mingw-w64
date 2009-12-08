#ifndef __ICRT_ALIGNED_H
#define __ICRT_ALIGNED_H

#define SAVED_PTR(x) ((void *)((uintptr_t) ((char *) x - sizeof (void *)) & ~(sizeof (void *) - 1)))
#define ALIGN_PTR(ptr, alignment, offset) \
  ((void *) ((((uintptr_t) ((char *) ptr + alignment + sizeof (void *) + offset)) & ~(alignment - 1)) - offset))

#define SZ_MINUSONE (~((size_t) 0))

#endif
