/* Memory-management internal function prototypes.  */
ic_new_handler_t __cdecl _ic_query_new_handler (void);
ic_new_handler_t __cdecl _ic_set_new_handler (ic_new_handler_t);

void * __cdecl _ic_markalloca (void *, unsigned int);
