#ifndef __W64CRT_H
#define __W64CRT_H

#include <w64crt_defs.h>

/* Internal crt locking.  */
typedef enum eW64CrtLocks {
  _LOCKTAB_LOCK = 0,
  _GLOBAL_LOCK,
  _SIGNAL_LOCK,
  _EXIT_LOCK,
  _TOTAL_LOCKS
} eW64CrtLocks;

extern void __w64crt_init_mtlocks (void);
extern void __w64crt_free_mtlocks (void);
extern void __w64crt_lock (int no);
extern void __w64crt_unlock (int no);

#ifdef _BUILD_MT
#define _mlock(NO) __w64crt_lock ((NO))
#define _munlock(NO) __w64crt_unlock ((NO))
#else
#define _mlock(NO) do { } while (0)
#define _munlock(NO) do { } while (0);
#endif

/* Error reporting and misc.  */
int __w64crt_MessageBoxA (const char *, const char *, unsigned int);
int __w64crt_MessageBoxW (const wchar_t *, const wchar_t *, unsigned int);

/* Todo. */
#define _w64crt_get_winmajor() 4

#endif

