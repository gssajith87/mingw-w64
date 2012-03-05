#include <ic_stdc.h>

void * __cdecl
ic_malloc (size_t sz)
{
  void *r;

  if (sz > _IC_HEAP_MAX_REQUESTED_SIZE)
    {
      _ic_callnewh (sz);
      ic_errno = IC_ENOMEM;
      return NULL;
    }

  if (!_ic_theheap)
    {
      __ic_showbanner ();
      __ic_showmsg (_ICRT_CRT_NOT_INIT);
      __ic_processexit (255);
    }

  do
    {
      if ((r = HeapAlloc (_ic_theheap, 0, (!sz ? 1 : sz))) != NULL)
	return r;
    }
  while (_ic_newmode && _ic_callnewh (sz));

  ic_errno = IC_ENOMEM;
  return NULL;
}

