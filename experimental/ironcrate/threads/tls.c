#include <ic_stdc.h>

#define TLSFLS_INVALID_VALUE 0xffffffffUL

typedef void (WINAPI *fFlsCallback) (void *);
typedef DWORD (WINAPI *fFlsAlloc) (fFlsCallback);
typedef WINBOOL (WINAPI *fFlsFree) (DWORD);
typedef WINBOOL (WINAPI *fFlsSetValue) (DWORD, void *);
typedef void *(WINAPI *fFlsGetValue) (DWORD);

static unsigned long fls_id = TLSFLS_INVALID_VALUE;
static unsigned long tls_id = TLSFLS_INVALID_VALUE;

static fFlsAlloc l_alloc = NULL;
static fFlsFree l_free = NULL;
static fFlsGetValue l_getvalue = NULL;
static fFlsSetValue l_setvalue = NULL;

int __cdecl
__ic_fls_setvalue (void *p)
{
  return !((*l_setvalue) (fls_id, p)) ? 0 : 1;
}

void * __cdecl
__ic_fls_getvalue (DWORD id)
{
  return ((fFlsGetValue) __ic_fls_set_getvalue ()) (id);
}

static DWORD WINAPI
l_tlsalloc (fFlsCallback f)
{
  return TlsAlloc ();
}

void * WINAPI
__ic_tls_getvalue (DWORD dwFlsIndex)
{
  return ((fFlsGetValue) TlsGetValue (tls_id)) (dwFlsIndex);
}

unsigned long __cdecl
__ic_fls_getid (void)
{
  return fls_id;
}

void * __cdecl
__ic_fls_set_getvalue (void)
{
  fFlsGetValue flsGetValue = (fFlsGetValue) TlsGetValue (tls_id);

  if (!flsGetValue)
    {
      flsGetValue = l_getvalue;
      TlsSetValue (tls_id, flsGetValue);
    }

  return flsGetValue;
}

WINBOOL WINAPI
__ic_tls_setvalue (DWORD id, void *p)
{
  return (*l_setvalue) (id, p);
}


int __cdecl
_ic_tls_init (void)
{
  HINSTANCE hmod;
  ic_thrdata_t ptd;

  if (!(hmod = (HINSTANCE) GetModuleHandleA ("KERNEL32.DLL")))
    {
      _ic_tls_dest ();
      return 0;
    }

  l_alloc = (fFlsAlloc) GetProcAddressA (hmod, "FlsAlloc");
  l_free = (fFlsFree) GetProcAddressA (hmod, "FlsFree");
  l_getvalue = (fFlsGetValue) GetProcAddressA (hmod, "FlsGetValue");
  l_setvalue = (fFlsSetValue) GetProcAddressA (hmod, "FlsSetValue");

  if (!l_alloc || !l_free
      || !l_getvalue || !l_setvalue)
    {
      l_alloc = (fFlsAlloc) l_tlsalloc;
      l_free = (fFlsFree) TlsFree;
      l_getvalue = (fFlsGetValue) TlsGetValue;
      l_setvalue = (fFlsSetValue) TlsSetValue;
    }

  if ((tls_id = TlsAlloc ()) == TLSFLS_INVALID_VALUE
      || !TlsSetValue (tls_id, (void *) l_getvalue))
    return 0;

  if (!__ic_initlocks ()
      || (fls_id = (*l_alloc) (&__ic_fls_free)) == TLSFLS_INVALID_VALUE
      || !(ptd = ic_calloc (1, sizeof (_ic_thrdata_t)))
      || !((*l_setvalue) (fls_id, (void *) ptd)))
    {
      _ic_tls_dest ();
      return 0;
    }

  _ic_init_thrdata (ptd, NULL);

  ptd->_tid = __ic_threadid ();
  ptd->_thandle = (uintptr_t) -1;

  return 1;
}

void __cdecl
_ic_tls_dest (void)
{
  if (fls_id != TLSFLS_INVALID_VALUE)
    {
      (*l_free) (fls_id);
      fls_id = TLSFLS_INVALID_VALUE;
    }

  if (tls_id != TLSFLS_INVALID_VALUE)
    {
      TlsFree (tls_id);
      tls_id = TLSFLS_INVALID_VALUE;
    }

  __ic_destroylocks ();
}

void __cdecl
_ic_init_thrdata (ic_thrdata_t ptd, ic_threadlocinfo_t *p)
{
  ptd->_holdrand = 1;
  ptd->_ownlocale = 1;
  ptd->_setloc_data._cachein[0] = 'C';
  ptd->_setloc_data._cacheout[0] = 'C';
  ptd->ptmbcinfo = &__ic_global_mbcinfo;
  ptd->_pxcptacttab = (void *) __ic_excpt_act_table;

  InterlockedIncrement (&(ptd->ptmbcinfo->refcount));

  _ic_lock (_IC_LOCK_SETLOCALE);

  ptd->ptlocinfo = p;
  if (ptd->ptlocinfo == NULL)
    ptd->ptlocinfo = __ic_tls_li;
  __ic_add_locale_ref (ptd->ptlocinfo);

  _ic_unlock (_IC_LOCK_SETLOCALE);
}

ic_thrdata_t __cdecl
_ic_get_internal_thrdata (void)
{
  ic_thrdata_t ptd;
  DWORD sverr = GetLastError ();

  if ((ptd = (ic_thrdata_t) __ic_fls_getvalue (fls_id)) != NULL
      || (ptd = ic_calloc (1, sizeof(_ic_thrdata_t))) == NULL)
    {
      SetLastError (sverr);
      return ptd;
    }

  if (!((*l_setvalue) (fls_id, (void *) ptd)))
    {
      ic_free (ptd);

      SetLastError (sverr);
      return NULL;
    }

  _ic_init_thrdata (ptd, NULL);
  ptd->_tid = __ic_threadid ();
  ptd->_thandle = (uintptr_t)(-1);

  SetLastError (sverr);
  return ptd;
}

ic_thrdata_t __cdecl
_ic_getthrdata (void)
{
  ic_thrdata_t ptd;

  if (!(ptd = _ic_get_internal_thrdata ()))
    _ic_amsg_exit (_ICRT_MSG_THREADING_FAILED);
  return ptd;
}


void WINAPI
__ic_fls_free (void *data)
{
  ic_thrdata_t p;
  ic_threadlocinfo_t *pli;
  ic_tmbinfo_t *pmbi;

  if ((p = (ic_thrdata_t) data) == NULL)
    return;

  ic_free (p->_errmsg);
  ic_free (p->_namebuf0);
  ic_free (p->_namebuf1);
  ic_free (p->_asctimebuf);
  ic_free (p->_gmtimebuf);
  ic_free (p->_cvtbuf);

  if (p->_pxcptacttab != __ic_excpt_act_table)
    ic_free (p->_pxcptacttab);

  _ic_lock (_IC_LOCK_MBCODEPAGE);
  if ((pmbi = p->ptmbcinfo) != NULL
      && !InterlockedDecrement (&pmbi->refcount)
      && pmbi != &__ic_global_mbcinfo)
    ic_free (pmbi);
  _ic_unlock (_IC_LOCK_MBCODEPAGE);

  _ic_lock (_IC_LOCK_SETLOCALE);
  if ((pli = p->ptlocinfo) != NULL)
    {
      __ic_release_locale_ref (pli);
      if (pli != __ic_tls_li
	  && pli != &__ic_global_locinfo
	  && pli->refcount == 0)
	__ic_free_thrdlocinfo (pli);
    }
  _ic_unlock (_IC_LOCK_SETLOCALE);

  ic_free (p);
}

void __cdecl
_ic_free_thrdata (ic_thrdata_t p)
{
  if (fls_id != TLSFLS_INVALID_VALUE)
  {
    if (!p)
      p = ((fFlsGetValue) TlsGetValue (tls_id)) (fls_id);

    (*l_setvalue) (fls_id, NULL);
    __ic_fls_free (p);
  }

  if (tls_id != TLSFLS_INVALID_VALUE)
    TlsSetValue (tls_id, NULL);
}

