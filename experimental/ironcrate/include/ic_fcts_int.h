/* Locale helper functions.  */
void __cdecl __ic_add_locale_ref (ic_threadlocinfo_t *);
void * __cdecl __ic_release_locale_ref (ic_threadlocinfo_t *);
void __cdecl __ic_free_thrdlocinfo (ic_threadlocinfo_t *);
void __cdecl __ic_free_lconv_mon (struct ic_lconv_t *);
void __cdecl __ic_free_lconv_num (struct ic_lconv_t *);
void __cdecl __ic_free_lc_time (ic_lc_timedate_t *);

/* TLS internal routines for thread-data.  */
void * __cdecl __ic_fls_getvalue (DWORD);
int __cdecl __ic_fls_setvalue (void *);
void * WINAPI __ic_tls_getvalue (DWORD dwFlsIndex);
void WINAPI __ic_fls_free (void *);
unsigned long __cdecl __ic_fls_getid (void);
WINBOOL WINAPI __ic_tls_setvalue (DWORD, void *);
void * __cdecl __ic_fls_set_getvalue (void);
int __cdecl _ic_tls_init (void);
void __cdecl _ic_tls_dest (void);

/* Thread-data routines.  */
ic_thrdata_t __cdecl _ic_get_internal_thrdata (void);
void __cdecl _ic_init_thrdata (ic_thrdata_t, ic_threadlocinfo_t *);
ic_thrdata_t __cdecl _ic_getthrdata (void);
void __cdecl _ic_free_thrdata (ic_thrdata_t);

/* Thread-locking API.  */
int  __cdecl __ic_initlocks (void);
void __cdecl __ic_destroylocks (void);
int  __cdecl _ic_init_locknum (int);
void __cdecl _ic_lock (int);
void __cdecl _ic_unlock (int);
int __cdecl __ic_initCritSect (CRITICAL_SECTION *, DWORD);

/* Memory-management internal function prototypes.  */
ic_new_handler_t __cdecl _ic_query_new_handler (void);
ic_new_handler_t __cdecl _ic_set_new_handler (ic_new_handler_t);

void * __cdecl _ic_markalloca (void *, unsigned int);
