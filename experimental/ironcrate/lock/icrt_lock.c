#include <icrt.h>
#include <windows.h>

typedef struct sLock {
  int init;
  CRITICAL_SECTION critical_section;
} sLock;

/* Statics forwarders.  */
static void __iCrt_lock_initialize (int);
static void __iCrt_lock_uninitialize (int);
static void __iCrt_lock_set_init (int, int);

static sLock __iCrt_locktbl[_TOTAL_LOCKS];

void
__iCrt_init_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    __iCrt_lock_set_init (i, 0);

  __iCrt_lock_initialize (_LOCKTAB_LOCK);
}

void
__iCrt_free_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    {
      if (__iCrt_locktbl[i].init != 0)
        __iCrt_lock_uninitialize (i);
    }
}

void
__iCrt_lock (int no)
{
  if (!__iCrt_locktbl[no].init)
    {
      __iCrt_lock ((int) _LOCKTAB_LOCK);

      if (!__iCrt_locktbl[no].init)
	__iCrt_lock_initialize (no);

      __iCrt_unlock ((int) _LOCKTAB_LOCK);
  }

  EnterCriticalSection (&__iCrt_locktbl[no].critical_section);
}

void
__iCrt_unlock (int no)
{
  LeaveCriticalSection (&__iCrt_locktbl[no].critical_section);
}

static void
__iCrt_lock_initialize (int no)
{
  InitializeCriticalSection (&__iCrt_locktbl[no].critical_section);
  __iCrt_lock_set_init (no, 1);
}

static void __iCrt_lock_uninitialize (int no)
{
  DeleteCriticalSection (&__iCrt_locktbl[no].critical_section);
  __iCrt_lock_set_init (no, 0);
}

static void
__iCrt_lock_set_init (int no, int init)
{
  __iCrt_locktbl[no].init = init;
}

