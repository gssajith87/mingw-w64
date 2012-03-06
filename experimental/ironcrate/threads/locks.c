#include <ic_stdc.h>

typedef struct l_lock_kind_t {
  PCRITICAL_SECTION cs;
  int is_fixed; /* if zero, lock has kind of lazy initialization.  */
} l_lock_kind_t;

static l_lock_kind_t
l_locks[_IC_LOCK_TOTAL] =
{
  { NULL, 1 }, /* _IC_LOCK_SIG */
  { NULL, 1 }, /* _IC_LOCK_IOB_SEEK */
  { NULL, 0 }, /* _IC_LOCK_TMPNAME */
  { NULL, 1 }, /* _IC_LOCK_CONIO */
  { NULL, 1 }, /* _IC_LOCK_HEAP */
  { NULL, 0 }, /* _IC_LOCK_UNDNAME */
  { NULL, 1 }, /* _IC_LOCK_TIME */
  { NULL, 1 }, /* _IC_LOCK_ENV */
  { NULL, 1 }, /* _IC_LOCK_EXIT1 */
  { NULL, 0 }, /* _IC_LOCK_POPEN */
  { NULL, 1 }, /* _IC_LOCK_TAB */
  { NULL, 0 }, /* _IC_LOCK_OSHANDLE */
  { NULL, 1 }, /* _IC_LOCK_SETLOCALE */
  { NULL, 1 }, /* _IC_LOCK_MBCODEPAGE */
  { NULL, 1 }, /* _IC_LOCK_TYPEINFO */
  { NULL, 0 },   /* _IC_LOCK_DEBUG */
  { NULL, 1 }, /* stdin  _IC_LOCK_STREAMS */
  { NULL, 1 }, /* stdout _IC_LOCK_STREAMS + 1 */
  { NULL, 1 }, /* stderr _IC_LOCK_STREAMS + 2 */
  /*      { NULL, 0 }, /* ... */
};

static CRITICAL_SECTION l_css[(_IC_LOCK_STREAMS - 2)];

int __cdecl
__ic_initlocks (void)
{
  int i, c;

  for (c = i = 0 ; i < _IC_LOCK_TOTAL; i++)
    {
      if (!l_locks[i].is_fixed)
        continue;

      l_locks[i].cs = &l_css[c++];

      if (!__ic_initCritSect (l_locks[i].cs, 4000))
	{
	  l_locks[i].cs = NULL;
	  return 0;
	}
    }

  return 1;
}

void __cdecl
__ic_destroylocks (void)
{
  PCRITICAL_SECTION p;
  int i;

  for (i = 0; i < _IC_LOCK_TOTAL; i++)
    {
      if (!l_locks[i].cs)
        continue;

      p = l_locks[i].cs;
      DeleteCriticalSection (p);

      if (!l_locks[i].is_fixed)
	{
	  ic_free (pcs);
	  l_locks[i].cs = NULL;
	}
    }
}

void __cdecl
_ic_lock (int n)
{
  if (!l_locks[n].cs && !_ic_init_locknum (n))
    _ic_amsg_exit (_ICRT_MSG_LOCK_FAILED);

  EnterCriticalSection (l_locks[n].cs);
}

void __cdecl
_ic_unlock (int n)
{
  LeaveCriticalSection (l_locks[n].cs);
}

int __cdecl
_ic_init_locknum (int n)
{
  PCRITICAL_SECTION p;
  int r = 1;

  if (!_ic_theheap)
    {
      __ic_showbanner ();
      __ic_showmsg (_ICRT_CRT_NOT_INIT);
      __ic_processexit (255);
    }

  if (l_locks[n].cs != NULL)
    return 1;

  if ((p = ic_malloc (sizeof (CRITICAL_SECTION))) == NULL)
    {
      ic_errno = IC_ENOMEM;
      return 0;
    }

  _ic_lock (_IC_LOCK_TAB);

  /* See if we might had meanwhile already an initialization?  */
  if (l_locks[n].cs)
    {
      ic_free (p);
      _ic_unlock (_IC_LOCK_TAB);
      return 1;
    }

  if (!__ic_initCritSect (p, 4000))
    {
      ic_free (p);
      ic_errno = IC_ENOMEM;
      _ic_unlock (_IC_LOCK_TAB);
      return 0;
    }
  l_locks[n].cs = p;

  _ic_unlock (_IC_LOCK_TAB);

  return r;
}

