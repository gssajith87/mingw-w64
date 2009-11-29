#include <w64crt.h>
#include <windows.h>

/* See http://msdn.microsoft.com/en-us/library/y6118zwe%28VS.71%29.aspx */

int
__w64crt_heapset (unsigned int value)
{
  int retval;
  _HEAPINFO heap;

  memset (&heap, 0, sizeof (_HEAPINFO));
  _mlock (_HEAP_LOCK);

  while ((retval = _heapwalk (&heap)) == _HEAPOK)
    {
      if (heap._useflag == _FREEENTRY)
	memset(heap._pentry, value, heap._size);
    }
  _munlock (_HEAP_LOCK);

  return retval == _HEAPEND ? _HEAPOK : retval;
}
