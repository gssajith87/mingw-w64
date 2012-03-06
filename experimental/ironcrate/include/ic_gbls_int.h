/* Internal global variables.  */

/* Local-management.  */
extern ic_threadlocinfo_t __ic_global_locinfo;
extern ic_slocal_t __ic_global_li;
extern ic_threadlocinfo_t *__ic_tls_li;
extern LCID __ic_lc_handle[];
extern UINT __ic_lc_codepage;
extern UINT __ic_lc_collate_cp;
extern int __ic_lc_clike;
extern ic_lc_timedate_t __ic_lc_time_c;
extern struct ic_lconv_t __ic_lconv_c;
extern struct ic_lconv_t *__ic_lconv;

/* C-type/MB-type globals.  */
extern ic_tmbinfo_t __ic_global_mbcinfo;
extern ic_tmbinfo_t *__ic_ptmbcinfo;
extern unsigned char _ic_mbctype[];
extern unsigned char _ic_mbcasemap[];
extern const unsigned short __ic_newctype[];
extern unsigned short __ic_mbulinfo[];
extern const unsigned char __ic_newclmap[];
extern const unsigned char __ic_newcumap[];
extern int __ic_mbcodepage;
extern int __ic_ismbcodepage;
extern int __ic_mblcid;


/* Exception-management.  */
extern struct _ic_exception_action_t __ic_excpt_act_table[];
extern int __ic_excpt_act_table_sz;
extern int __ic_excpt_act_table_num;

/* Memory-management.  */
extern HANDLE _ic_theheap;
extern ic_new_handler_t __ic_newhandle_fct;

/* Misc global.  */
extern char __ic_str_C[];
extern char __ic_lconv_str_decimal[];
extern char __ic_lconv_str_empty[];

