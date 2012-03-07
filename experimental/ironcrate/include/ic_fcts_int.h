/* Locale helper functions.  */
void __cdecl __ic_add_locale_ref (ic_threadlocinfo_t *);
void * __cdecl __ic_release_locale_ref (ic_threadlocinfo_t *);
void __cdecl __ic_free_thrdlocinfo (ic_threadlocinfo_t *);
void __cdecl __ic_free_lconv_mon (struct ic_lconv_t *);
void __cdecl __ic_free_lconv_num (struct ic_lconv_t *);
void __cdecl __ic_free_lc_time (ic_lc_timedate_t *);

/* Thread-locking API.  */
int  __cdecl __ic_initlocks (void);
void __cdecl __ic_destroylocks (void);
int  __cdecl _ic_init_locknum (int);
void __cdecl _ic_lock (int);
void __cdecl _ic_unlock (int);

/* Memory-management internal function prototypes.  */
ic_new_handler_t __cdecl _ic_query_new_handler (void);
ic_new_handler_t __cdecl _ic_set_new_handler (ic_new_handler_t);

void * __cdecl _ic_markalloca (void *, unsigned int);
