/* Thread-management prototypes.  */
uintptr_t __cdecl __ic_threadhandle (void);
unsigned long __cdecl __ic_threadid (void);

/* Thread locale prototypes  */
void __cdecl _ic_free_locale (ic_slocal_t *);
int __cdecl _ic_configthreadlocale (int);
ic_slocal_t * __cdecl _ic_get_current_locale (void);

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

/* Random numer functions.  */
void __cdecl ic_srand (unsigned int);
int __cdecl ic_rand (void);
ic_errno_t __cdecl ic_rand_s (unsigned int *);

/* Sort/search functions.  */
void __cdecl ic_qsort_s (void *, size_t, size_t,
  int (__cdecl *) (void *, const void *, const void *), void *);
void __cdecl ic_qsort (void *, size_t, size_t,
  int (__cdecl *) (const void *, const void *));
void * __cdecl _ic_lsearch (const void *, void *, unsigned int *, size_t,
  int (__cdecl *)(const void *, const void *));
void * __cdecl _ic_lsearch_s (const void *, void *, unsigned int *, size_t,
  int (__cdecl *)(void *, const void *, const void *), void *);
void * __cdecl _ic_lfind_s (const void *, const void *, unsigned int *, size_t,
  int (__cdecl *)(void *,const void *, const void *), void *);
void * __cdecl _ic_lfind (const void *, const void *, unsigned int *, size_t,
  int (__cdecl *)(const void *, const void *));
void * __cdecl ic_bsearch (const void *, const void *, size_t, size_t,
  int (__cdecl *)(const void *, const void *));
void * __cdecl ic_bsearch_s (const void *, const void *, size_t, size_t,
  int (__cdecl *)(void *, const void *, const void *), void *);


/* Memory base manipulation routines.  */
void * __cdecl ic_memmove (void *, const void *, size_t);
void * __cdecl ic_memcpy (void *, const void *, size_t);
void * __cdecl ic_memchr (const void *, int ch, size_t);
int __cdecl ic_memcmp (const void *, const void *, size_t);
void * __cdecl ic_memset (void *, int, size_t);

ic_errno_t __cdecl ic_memmove_s (void *, size_t, const void *, size_t);
ic_errno_t __cdecl ic_memcpy_s (void *, size_t, const void *, size_t);
void * __cdecl _ic_memccpy (void *, const void *, int, size_t);
int __cdecl _ic_memicmp (const void *, const void *, size_t);
int __cdecl _ic_memicmp_l (const void *, const void *, size_t, ic_slocal_t *);

wchar_t * __cdecl ic_wmemchr (const wchar_t *, wchar_t, size_t);
int __cdecl ic_wmemcmp (const wchar_t *, const wchar_t *, size_t);
wchar_t * __cdecl ic_wmemcpy (wchar_t *, const wchar_t *, size_t);
wchar_t * __cdecl ic_wmemmove (wchar_t *, const wchar_t *, size_t);
wchar_t * __cdecl ic_wmemset (wchar_t *, wchar_t, size_t);

ic_errno_t __cdecl ic_wmemcpy_s (wchar_t *, rsize_t, const wchar_t *, rsize_t);
ic_errno_t __cdecl ic_wmemmove_s (wchar_t *, rsize_t, const wchar_t *, rsize_t);
