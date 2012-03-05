/* Memory-management  types.  */
typedef int (__cdecl *ic_new_handler_t) (size_t);

typedef struct _ic_heapinfo_t
{
  int *_pentry;
  size_t _size;
  int _useflag;
} _ic_heapinfo_t;

/* Error types.  */
typedef int ic_errno_t;
