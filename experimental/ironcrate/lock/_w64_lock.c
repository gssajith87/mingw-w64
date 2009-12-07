#include <w64crt.h>
#include <windows.h>

typedef struct sLock {
  int init;
  CRITICAL_SECTION critical_section;
} sLock;

/* Statics forwarders.  */
static void __w64crt_lock_initialize (int);
static void __w64crt_lock_uninitialize (int);
static void __w64crt_lock_set_init (int, int);

static sLock __w64crt_locktbl[_TOTAL_LOCKS];

void
__w64crt_init_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    __w64crt_lock_set_init (i, 0);

  __w64crt_lock_initialize (_LOCKTAB_LOCK);
}

void
__w64crt_free_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    {
      if (__w64crt_locktbl[i].init != 0)
        __w64crt_lock_uninitialize (i);
    }
}

void
__w64crt_lock (int no)
{
  if (!__w64crt_locktbl[no].init)
    {
      __w64crt_lock ((int) _LOCKTAB_LOCK);

      if (!__w64crt_locktbl[no].init)
	__w64crt_lock_initialize (no);

      __w64crt_unlock ((int) _LOCKTAB_LOCK);
  }

  EnterCriticalSection (&__w64crt_locktbl[no].critical_section);
}

void
__w64crt_unlock (int no)
{
  LeaveCriticalSection (&__w64crt_locktbl[no].critical_section);
}

static void
__w64crt_lock_initialize (int no)
{
  InitializeCriticalSection (&__w64crt_locktbl[no].critical_section);
  __w64crt_lock_set_init (no, 1);
}

static void __w64crt_lock_uninitialize (int no)
{
  DeleteCriticalSection (&__w64crt_locktbl[no].critical_section);
  __w64crt_lock_set_init (no, 0);
}

static void
__w64crt_lock_set_init (int no, int init)
{
  __w64crt_locktbl[no].init = init;
}

