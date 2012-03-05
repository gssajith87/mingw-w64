/* Memory-management prototypes.  */
int __cdecl _ic_heap_init (int);
void __cdecl _ic_heap_term (void);
void __cdecl _ic_heap_abort (void);
intptr_t __cdecl _ic_get_heap_handle (void);
int __cdecl _ic_heapadd (void *, size_t);
int __cdecl _ic_heapmin (void);
size_t __cdecl _ic_heapused (size_t *, size_t *);
int __cdecl _ic_heapset (unsigned int);
int __cdecl _ic_heapchk (void);
int __cdecl _ic_heapwalk (struct _ic_heapinfo_t *);

void * __cdecl ic_calloc (size_t, size_t);
void * __cdecl ic_malloc (size_t);
void * __cdecl _ic_recalloc (void *, size_t, size_t);
void * __cdecl ic_realloc (void *, size_t);
void __cdecl ic_free (void *);

void __cdecl _ic_freea (void *);

size_t __cdecl _ic_msize (void *);
void * __cdecl _ic_expand (void *, size_t);

size_t __cdecl _ic_get_sbh_threshold (void);
int __cdecl _ic_set_sbh_threshold (size_t);
ic_errno_t __cdecl _ic_set_amblksiz (size_t);
unsigned int * __cdecl __p_ic_amblksiz (void);
ic_errno_t __cdecl _ic_get_amblksiz (size_t *sz);

void  __cdecl _ic_aligned_free (void *);
void * __cdecl _ic_aligned_offset_recalloc (void *, size_t, size_t, size_t, size_t);
size_t __cdecl _ic_aligned_msize (void *, size_t, size_t);
void * __cdecl _ic_aligned_offset_realloc (void *, size_t, size_t,size_t);
void * __cdecl _ic_aligned_recalloc (void *, size_t, size_t, size_t);
void * __cdecl _ic_aligned_realloc (void *, size_t, size_t);
void * __cdecl _ic_aligned_offset_malloc (size_t, size_t, size_t);
void * __cdecl _ic_aligned_malloc (size_t, size_t);
int __cdecl _ic_callnewh (size_t);
ic_new_handler_t __cdecl ic_set_new_handler (ic_new_handler_t);

/* Error-management functions.  */
int * __cdecl _ic_errno (void);
ic_errno_t __cdecl _ic_set_errno (int);
ic_errno_t __cdecl _ic_get_errno (int *);
void __cdecl _ic_mapwinerr (unsigned long);
int __cdecl _ic_get_errno_from_winerr (unsigned long);
unsigned long * __cdecl __ic_doserrno (void);
ic_errno_t __cdecl _ic_set_doserrno (unsigned long );
ic_errno_t __cdecl _ic_get_doserrno (unsigned long *);
char ** __cdecl __ic_sys_errlist (void);
int * __cdecl __ic_sys_nerr (void);
const char * __cdecl _ic_get_sys_errmsg (int);

