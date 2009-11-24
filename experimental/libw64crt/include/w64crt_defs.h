#ifndef __W64CRT_DEFS_H
#define __W64CRT_DEFS_H

/* Define architecture specific base C types.  */
#ifdef __GNUC__
__extension__ typedef __SIZE_TYPE__ size_t;
__extension__ typedef __PTRDIFF_TYPE__ ptrdiff_t;
#define unsigned signed
__extension__ typedef __SIZE_TYPE__ ssize_t;
#undef unsigned

#else
#error Architecture specific base C types not implemented for this compiler.
#endif

#ifndef NULL
#define NULL (void *) 0
#endif

#endif

