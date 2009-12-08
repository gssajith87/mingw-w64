#ifndef __ICRT_MEMORY_H
#define __ICRT_MEMORY_H

#include <icrt.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64
#define _HEAP_MAXREQ 0xFFFFFFFFFFFFFFE0
#else
#define _HEAP_MAXREQ 0xFFFFFFE0
#endif

/* Return codes for _heapwalk()  */
#define _HEAPEMPTY (-1)
#define _HEAPOK (-2)
#define _HEAPBADBEGIN (-3)
#define _HEAPBADNODE (-4)
#define _HEAPEND (-5)
#define _HEAPBADPTR (-6)

/* Values for _heapinfo.useflag */
#define _FREEENTRY 0
#define _USEDENTRY 1

#ifndef _HEAPINFO_DEFINED
#define _HEAPINFO_DEFINED
 /* The structure used to walk through the heap with _heapwalk.  */
  typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;
#endif

#undef alloca
#ifdef __GNUC__
#define alloca(x) __builtin_alloca((x))
#else
#define alloca _alloca
#endif

#ifdef HEAPHOOK
#ifndef _HEAPHOOK_DEFINED
#define _HEAPHOOK_DEFINED
  typedef int (*_HEAPHOOK)(int,size_t,void *,void **);
#endif

  _HEAPHOOK _setheaphook(_HEAPHOOK _NewHook);

#define _HEAP_MALLOC 1
#define _HEAP_CALLOC 2
#define _HEAP_FREE 3
#define _HEAP_REALLOC 4
#define _HEAP_MSIZE 5
#define _HEAP_EXPAND 6
#endif

typedef void (*__iCrt_new_handler_func)(size_t size);

unsigned int *__iCrt_p__amblksize (void);
size_t __iCrt_get_sbh_threshold (void);
int __iCrt_set_sbh_threshold (size_t threshold);

void __iCrt_aligned_free (void *);
void *__iCrt_aligned_malloc (size_t sz, size_t align);
void *__iCrt_aligned_offset_malloc (size_t sz, size_t align, size_t off);
void *__iCrt_aligned_offset_realloc (void *ptr, size_t sz, size_t align, size_t off);
void *__iCrt_aligned_realloc (void *ptr, size_t sz, size_t align);

void *__iCrt_expand (void *mem, size_t sz);
int __iCrt_heapadd (void *mem, size_t sz);
int __iCrt_heapchk (void);
int __iCrt_heapmin (void);
int __iCrt_heapset (unsigned int value);
int __iCrt_heapwalk (struct _heapinfo *next);

size_t __iCrt_msize (void *ptr);
void *__iCrt_calloc (size_t sz, size_t cnt);
void __iCrt_free (void *ptr);
void *__iCrt_malloc (size_t sz);
void *__iCrt_realloc (void *ptr, size_t sz);

int __iCrt_callnewh (size_t sz);
int __iCrt_set_new_mode (int mode);
__iCrt_new_handler_func __iCrt_set_new_handler (void *func);
__iCrt_new_handler_func __iCrt__set_new_handler (__iCrt_new_handler_func func);
int __iCrt_query_new_mode (void);
__iCrt_new_handler_func __iCrt_query_new_handler (void);
void __iCrt_operator_delete (void *ptr);
void *__iCrt_operator_new (size_t sz);

#ifdef __cplusplus
}
#endif

#endif

