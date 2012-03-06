/* Internal global variables.  */

/* Exception-management.  */
extern struct _ic_exception_action_t __ic_excpt_act_table[];
extern int __ic_excpt_act_table_sz;
extern int __ic_excpt_act_table_num;

/* Memory-management.  */
extern HANDLE _ic_theheap;
extern ic_new_handler_t __ic_newhandle_fct;
