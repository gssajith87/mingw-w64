/* Defines used for building ironCrate.  */

#ifdef __x86_64__
#define _IC_HEAP_MAX_REQUESTED_SIZE 0xFFFFFFFFFFFFFFE0ULL
#else
#define _IC_HEAP_MAX_REQUESTED_SIZE 0xFFFFFFE0UL
#endif

/* Internal error-message ids.  Numbers according to list found
   on msdn research.  */
#define _ICRT_MSG_FLOAT_TRAP 1
#define _ICRT_MSG_NOSPACE_FOR_ARGS 2
#define _ICRT_MSG_NOSPACE_FOR_ENV 3
#define _ICRT_MSG_ABORT 4
#define _ICRT_MSG_THREADING_FAILED 5
#define _ICRT_MSG_LOCK_FAILED 6
#define _ICRT_MSG_HEAP_FAILURE 7
#define _ICRT_MSG_ONEXIT_FAILED 8
#define _ICRT_MSG_PUREVIRT 9
#define _ICRT_MSG_STDIO_INIT_FAILED 10
#define _ICRT_MSG_LOW_IO_INIT_FAILED 11
#define _ICRT_HEAPINIT_FAILED 12
#define _ICRT_CRT_NOT_INIT 13
#define _ICRT_MSG_CRT_INIT_MULTIPLE 14
#define _ICRT_LOCALE_INIT_FAILED 15

/* Error-numbers of _ic_errno.  Numbers according to msdn.  */
#define IC_EPERM        1
#define IC_ENOENT       2
#define IC_ESRCH        3
#define IC_EINTR        4
#define IC_EIO          5
#define IC_ENXIO        6
#define IC_E2BIG        7
#define IC_ENOEXEC      8
#define IC_EBADF        9
#define IC_ECHILD       10
#define IC_EAGAIN       11
#define IC_ENOMEM       12
#define IC_EACCES       13
#define IC_EFAULT       14
#define IC_ENOTBLK      15
#define IC_EBUSY        16
#define IC_EEXIST       17
#define IC_EXDEV        18
#define IC_ENODEV       19
#define IC_ENOTDIR      20
#define IC_EISDIR       21
#define IC_EINVAL       22
#define IC_ENFILE       23
#define IC_EMFILE       24
#define IC_ENOTTY       25
#define IC_ETXTBSY      26
#define IC_EFBIG        27
#define IC_ENOSPC       28
#define IC_ESPIPE       29
#define IC_EROFS        30
#define IC_EMLINK       31
#define IC_EPIPE        32
#define IC_EDOM         33
#define IC_ERANGE       34
#define IC_EUCLEAN      35
#define IC_EDEADLK      36

#define IC_ENAMETOOLONG 38
#define IC_ENOLCK       39
#define IC_ENOSYS       40
#define IC_ENOTEMPTY    41
#define IC_EILSEQ       42

#define IC_STRUNCATE    80

/* The heapwalk results.  Values are according to msdn's _heapwalk
   documentation.  */
#define IC_HEAP_EMPTY -1
#define IC_HEAP_OK -2
#define IC_HEAP_BAD_BEGIN -3
#define IC_HEAP_BAD_NODE -4
#define IC_HEAP_END -5
#define IC_HEAP_BAD_POINTER -6

/* Errno helpers.  */
#define ic_errno   (*_ic_errno ())
#define _ic_doserrno   (*__ic_doserrno ())
#define _ic_sys_errlist (__ic_sys_errlist ())
#define _ic_sys_nerr (*__ic_sys_nerr ())

/* I/O base constants.  */
#define IC_NSTREAM   512
#define _IC_IOB_ELEMS 20

/* Internal locking constants.  */
#define _IC_LOCK_SIG 0
#define _IC_LOCK_IOB_SEEK 1
#define _IC_LOCK_TMPNAME 2
#define _IC_LOCK_CONIO 3
#define _IC_LOCK_HEAP 4
#define _IC_LOCK_UNDNAME 5
#define _IC_LOCK_TIME 6
#define _IC_LOCK_ENV 7
#define _IC_LOCK_EXIT1 8
#define _IC_LOCK_POPEN 9
#define _IC_LOCK_TAB 10
#define _IC_LOCK_OSHANDLE 11
#define _IC_LOCK_SETLOCALE 12
#define _IC_LOCK_MBCODEPAGE 13
#define _IC_LOCK_TYPEINFO 14
#define _IC_LOCK_DEBUG 15
#define _IC_LOCK_STREAMS 16

#define _IC_LOCK_STREAM_LAST (_IC_LOCK_STREAMS + _IC_IOB_ELEMS - 1)
#define _IC_LOCK_TOTAL (_IC_LOCK_STREAM_LAST + 1)
#define _IC_LOCK_BITS_IN_INTS (_IC_LOCK_TOTAL / 32) + 1

/* Exception-management.  */
#ifndef STATUS_INVALID_PARAMETER
#define STATUS_INVALID_PARAMETER         (0xc000000dL)
#endif

#ifndef STATUS_FATAL_APP_EXIT
#define STATUS_FATAL_APP_EXIT            (0x40000015L)
#endif

#define IC_SIGINT 2
#define IC_SIGILL 4
#define IC_SIGABRT_COMPAT 6
#define IC_SIGFPE 8
#define IC_SIGSEGV 11
#define IC_SIGTERM 15
#define IC_SIGBREAK 21
#define IC_SIGABRT 22

#define IC_SIG_DFL (void (__cdecl *)(int)) ((intptr_t) 0)
#define IC_SIG_IGN (void (__cdecl *)(int)) ((intptr_t) 1)
#define IC_SIG_GET (void (__cdecl *)(int)) ((intptr_t) 2)
#define IC_SIG_SGE (void (__cdecl *)(int)) ((intptr_t) 3)
#define IC_SIG_ACK (void (__cdecl *)(int)) ((intptr_t) 4)
#define IC_SIG_DIE (void (__cdecl *)(int)) ((intptr_t) 5)
#define IC_SIG_ERR (void (__cdecl *)(int)) ((intptr_t) -1)

/* C-type and MB-type related defines.  */
#define _IC_UPPER       0x1
#define _IC_LOWER	0x2
#define _IC_DIGIT	0x4
#define _IC_SPACE	0x8
#define _IC_PUNCT	0x10
#define _IC_CONTROL	0x20
#define _IC_BLANK	0x40
#define _IC_HEX		0x80

#define _IC_LEADBYTE	0x8000
#define _IC_ALPHA	(0x0100 | _IC_UPPER | _IC_LOWER)

#define IC_LC_MIN	0
#define IC_LC_MAX	5

#define IC_LC_ALL	0
#define IC_LC_COLLATE	1
#define IC_LC_CTYPE	2
#define IC_LC_MONETARY	3
#define IC_LC_NUMERIC	4
#define IC_LC_TIME	5

/* Thread-locale modes.  */
#define IC_TL 0x1
#define IC_NO_TL 0x2
#define IC_TL_GLOBAL 0x10
#define IC_NO_TL_GLOBAL 0x20
#define IC_TL_NEW 0x100
#define IC_NO_TL_NEW 0x200
