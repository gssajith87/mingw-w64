#include <icrt.h>
#include <windows.h>

static __w64crt_new_handler_func new_handler;
static int new_mode;

void *__w64crt_operator_new (size_t sz)
{
  void *retval = HeapAlloc (GetProcessHeap(), 0, sz);
  
  if (retval)
    return retval;
  _mlock (_HEAP_LOCK);
  if (new_handler)
    (*new_handler) (sz);
  _munlock (_HEAP_LOCK);
  return retval;
}

void __w64crt_operator_delete (void *ptr)
{
  HeapFree (GetProcessHeap (), 0, ptr);
}

__w64crt_new_handler_func __w64crt_query_new_handler (void)
{
  return new_handler;
}

int
__w64crt_query_new_mode (void)
{
  return new_mode;
}

__w64crt_new_handler_func
__w64crt__set_new_handler (__w64crt_new_handler_func func)
{
  __w64crt_new_handler_func old_handler;
  _mlock (_HEAP_LOCK);
  old_handler = new_handler;
  new_handler = func;
  _munlock (_HEAP_LOCK);
  return old_handler;
}

__w64crt_new_handler_func
__w64crt_set_new_handler (void *func)
{
  return __w64crt__set_new_handler (func);
}

int
__w64crt_set_new_mode (int mode)
{
  int old_mode;
  _mlock (_HEAP_LOCK);
  old_mode = new_mode;
  new_mode = mode;
  _munlock (_HEAP_LOCK);
  return old_mode;
}

int
__w64crt_callnewh (size_t sz)
{
  if (new_handler)
    (*new_handler) (sz);
  return 0;
}
