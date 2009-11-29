#include <w64crt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/h0c183dk%28VS.71%29.aspx */

int
__w64crt_heapwalk (_HEAPINFO *next)
{
  PROCESS_HEAP_ENTRY phe;

  _mlock (_HEAP_LOCK);
  phe.lpData = next->_pentry;
  phe.cbData = next->_size;
  phe.wFlags = next->_useflag == _USEDENTRY ? PROCESS_HEAP_ENTRY_BUSY : 0;

  if (phe.lpData && phe.wFlags & PROCESS_HEAP_ENTRY_BUSY
      && !HeapValidate (GetProcessHeap (), 0, phe.lpData))
    {
      _munlock (_HEAP_LOCK);
      __w64crt_set_doserrno (GetLastError ());
      return _HEAPBADNODE;
    }

  do
    {
      if (!HeapWalk (GetProcessHeap (), &phe))
        {
	  _munlock (_HEAP_LOCK);
	  if (GetLastError () == ERROR_NO_MORE_ITEMS)
	    return _HEAPEND;
	  __w64crt_set_doserrno (GetLastError ());
	  if (!phe.lpData)
	    return _HEAPBADBEGIN;
	  return _HEAPBADNODE;
        }
    }
  while (phe.wFlags & (PROCESS_HEAP_REGION | PROCESS_HEAP_UNCOMMITTED_RANGE));

  _munlock (_HEAP_LOCK);
  next->_pentry = phe.lpData;
  next->_size = phe.cbData;
  next->_useflag = phe.wFlags & PROCESS_HEAP_ENTRY_BUSY ? _USEDENTRY : _FREEENTRY;
  return _HEAPOK;
}
