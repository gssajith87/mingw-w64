#include <ic_stdc.h>

int __cdecl
_ic_heapwalk (struct _ic_heapinfo_t *phi)
{
  PROCESS_HEAP_ENTRY phe;
  DWORD e;

  if (!phi)
    {
      ic_errno = IC_EINVAL;
      IC_INV_PARAM("Invalid argument");
      return IC_HEAP_BAD_POINTER;
    }

  ic_memset (&phe, 0, sizeof (phe));

  if (!(phe.lpData = phi->_pentry))
    {
      if (!HeapWalk (_ic_theheap, &phe))
	{
	  if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
	    {
	      _ic_doserrno = ERROR_CALL_NOT_IMPLEMENTED;
	      ic_errno = IC_ENOSYS;
	      return IC_HEAP_END;
	    }
	  return IC_HEAP_BAD_BEGIN;
	}
    }
  else
    {
      if (phi->_useflag == 1)
	{
	  if (!HeapValidate (_ic_theheap, 0, phi->_pentry))
	    return IC_HEAP_BAD_NODE;
	  phe.wFlags = PROCESS_HEAP_ENTRY_BUSY;
	}
      do
        {
	  if (!HeapWalk (_ic_theheap, &phe))
	    {
	      if ((e = GetLastError ()) == ERROR_NO_MORE_ITEMS)
		return IC_HEAP_END;

	      if (e != ERROR_CALL_NOT_IMPLEMENTED)
	        return IC_HEAP_BAD_NODE;

	      _ic_doserrno = e;
	      ic_errno = IC_ENOSYS;
	      return IC_HEAP_END;
	    }
	}
      while ((phe.wFlags & (PROCESS_HEAP_REGION | PROCESS_HEAP_UNCOMMITTED_RANGE)) != 0);
    }

  phi->_pentry = phe.lpData;
  phi->_size = phe.cbData;
  phi->_useflag = (phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0;

  return IC_HEAP_OK;
}

