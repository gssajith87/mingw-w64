#include <w64crt.h>
#include <windows.h>

typedef struct sLock {
  int init;
  CRITICAL_SECTION critical_section;
} sLock;

/* Statics forwarders.  */
static void _w64_lock_initialize (int);
static void _w64_lock_uninitialize (int);
static void _w64_lock_set_init (int, int);

static sLock _w64_locktbl[_TOTAL_LOCKS];

void
_w64_init_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    _w64_set_init (i, 0);

  _w64_lock_initialize (_LOCKTAB_LOCK);
}

void
_w64_free_mtlocks (void)
{
  int i;

  for (i = 0; i < (int) _TOTAL_LOCKS; i++)
    {
      if (_w64_locktbl[i].init != 0)
        _w64_lock_uninitialize (i);
    }
}

void
_w64_lock (int no)
{
  if (!_w64_locktbl[no].init)
    {
      _w64_lock ((int) _LOCKTAB_LOCK);

      if (!_w64_locktbl[no].init)
	_w64_lock_initialize (no);

      _w64_unlock ((int) _LOCKTAB_LOCK);
  }

  EnterCriticalSection (&_w64_locktbl[no].critical_section);
}

void
_w64_unlock (int no)
{
  LeaveCriticalSection (&_w64_locktbl[no].critical_section);
}

static void
_w64_lock_initialize (int no)
{
  InitializeCriticalSection (&_w64_locktbl[no].critical_section);
  _w64_lock_set_init (no, 1);
}

static void _w64_lock_uninitialize (int no)
{
  DeleteCriticalSection (&_w64_locktbl[no].critical_section);
  _w64_lock_set_init (no, 0);
}

static void
_w64_lock_set_init (int no, int init)
{
  _w64_locktbl[no].init = init;
}

