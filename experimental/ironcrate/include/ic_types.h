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

/* Locale related types.  */

struct _ic_ctype_compat
{
  unsigned long id;
  int is_clike;
};

typedef struct LC_ID {
    unsigned short wLanguage;
    unsigned short wCountry;
    unsigned short wCodePage;
} LC_ID;

typedef struct _ic_setloc_t
{
  char *pchLanguage;
  char *pchCountry;
  int iLcidState;
  int iPrimaryLen;
  BOOL bAbbrevLanguage;
  BOOL bAbbrevCountry;
  LCID lcidLanguage;
  LCID lcidCountry;
  LC_ID _cacheid;
  UINT _cachecp;
  char _cachein[131];
  char _cacheout[131];
  struct _ic_ctype_compat _Lcid_c[5];
} _ic_setloc_t;

