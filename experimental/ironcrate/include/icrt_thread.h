#ifndef __ICRT_THREAD_H
#define __ICRT_THREAD_H

typedef struct __iCrt_thrdata {
  unsigned long _thrd_id;
  uintptr_t _thrd_handle;
  int _thrd_errno;
  unsigned long _thrd_winerror; /* Is aliased as _thrd_doserror.  */
#define _thrd_doserror _thrd_winerror
} _thrdata, *_pthrdata;

_pthrdata *__iCrt_getpthrdata (void);

#endif
