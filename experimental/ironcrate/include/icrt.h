#ifndef __ICRT_H
#define __ICRT_H

#include <icrt_defs.h>
#include <icrt_map.h>

/* Internal crt locking.  */
typedef enum iCrt_eLocks {
  _LOCKTAB_LOCK = 0,
  _HEAP_LOCK,
  _GLOBAL_LOCK,
  _SIGNAL_LOCK,
  _EXIT_LOCK,
  _TOTAL_LOCKS
} iCrt_eLocks;

extern void __iCrt_init_mtlocks (void);
extern void __iCrt_free_mtlocks (void);
extern void __iCrt_lock (int no);
extern void __iCrt_unlock (int no);

#ifdef BUILD_MT
#define _mlock(NO) __iCrt_lock ((NO))
#define _munlock(NO) __iCrt_unlock ((NO))
#else
#define _mlock(NO) do { } while (0)
#define _munlock(NO) do { } while (0);
#endif

/* Error reporting and misc.  */
int __iCrt_MessageBoxA (const char *, const char *, unsigned int);
int __iCrt_MessageBoxW (const wchar_t *, const wchar_t *, unsigned int);

/* Errno and _doserrno functions.  */
int __iCrt_get_errno_from_oserr (unsigned long);
#define __iCrt_set_errno(ERR) do { ; } while (0)
#define __iCrt_set_doserrno(WINERR) do { ; } while (0)

#include <icrt_string.h>
#include <icrt_memory.h>
#include <icrt_thread.h>

#endif
