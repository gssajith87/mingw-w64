#ifndef __ICRT_DEFS_H
#define __ICRT_DEFS_H

/* Define architecture specific base C types.  */
#ifdef __GNUC__
__extension__ typedef __SIZE_TYPE__ size_t;
__extension__ typedef __PTRDIFF_TYPE__ ptrdiff_t;
__extension__ typedef __UINTPTR_TYPE__ uintptr_t;
__extension__ typedef __INTPTR_TYPE__ intptr_t;
#define unsigned signed
__extension__ typedef __SIZE_TYPE__ ssize_t;
#undef unsigned
typedef __WCHAR_TYPE__ wchar_t;
#else
#error Architecture specific base C types not implemented for this compiler.
#endif

#ifndef NULL
#define NULL (void *) 0
#endif

/* Default to kind of version build.  */
#if !defined (BUILD_CRT_SHARED)
#define BUILD_CRT_SHARED 0
#endif

#if BUILD_CRT_SHARED == 0
#define __CRTEXPORT /* empty */
#else
#ifdef BUILD_CRT_STARTUP
#define __CRTEXPORT __declspec(dllimport)
#else
#define __CRTEXPORT __declspec(dllexport)
#endif /* defined (BUILD_CRT_STARTUP) */
#endif /* BUILD_CRT_SHARED == 0 */

#endif

