#ifndef GETIDL_TYPINFO_HXX
#define GETIDL_TYPINFO_HXX

#define TITYP_NONE -1
#define TITYP_NAME  0
#define TITYP_STR   1
#define TITYP_GUIDS 2
#define TITYP_TYPINFO_NAMES 3
#define TITYP_DEREF 4
#define TITYP_ARRAY 5
#define TITYP_REF   6
#define TITYP_IMP   7
#define TITYP_UNKNOWN 8
#define TITYP_CUSTOMDATA 9
#define TITYP_CUSTOMGUID 10
#define TITYP_IMPREF	 11

#define TITYP_MAX 12

typedef struct sTITyp {
  uint32_t memid;
  int32_t kind;
  int32_t refkind;
  uint32_t refmem;
  char *refstr;
  char *poststr;
  char name[1];
} sTITyp;

typedef struct sTITypsHash
{
  size_t count;
  size_t max;
  sTITyp **arr;
} sTITypsHash;

typedef struct sTITyps {
  sTITypsHash buc[TITYP_MAX];
} sTITyps;

int32_t TI_init_typs (sTITyps *ptyp);
int32_t TI_dest_typs (sTITyps *ptyp);
int32_t TI_add_typ (sTITyps *ptyp, uint32_t memid, int32_t kind, int32_t refkind, uint32_t refmem,
		const char *refstr, const char *name, const char *poststr);
sTITyp *TI_get_typ (sTITyps *ptyp, uint32_t memid, int32_t kind);
char *TI_get_typ_name (sTITyps *ptyp, uint32_t memid, int32_t kind, const char *varName);

int32_t TI2_import_name (sTITyps *nptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_guid (sTITyps *gptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_typinfo_names (sTITyps *tptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_string (sTITyps *sptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_typedesc (sTITyps *dptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_customdata (sTITyps *dptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_customdataguid (sTITyps *gptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_importlibs (sTITyps *iptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_ref (sTITyps *gptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_array (sTITyps *gptr, unsigned char *dta, uint32_t len);
int32_t TI2_import_importref (sTITyps *gptr, unsigned char *dta, uint32_t len);

const char *decode_VT_name_tmp (unsigned short vt);
size_t getVT_data (sTITyps *dptr, uint32_t vt, unsigned char *dta, char **ret);
char *TI_getVTorDref (sTITyps *ptyp,uint32_t vt, const char *varName);
size_t getVT_size (uint32_t vt, unsigned char *dta, size_t *basesz);
size_t getVT_data (sTITyps *dptr, uint32_t vt, unsigned char *dta, char **ret);

typedef struct sTI2TypeBaseMemItem {
  int beFunc;
  union {
    unsigned char *mem;
    sMSFT_func *func;
    sMSFT_var *var;
  };
  uint32_t *customData;
  sMSFT_FuncParam *funcParam;
  uint32_t *extData;
  size_t max;
} sTI2TypeBaseMemItem;

typedef struct sTI2TypeBaseMem
{
  size_t count;
  sTI2TypeBaseMemItem *items;
} sTI2TypeBaseMem;

typedef struct sTI2TypeBase {
  uint32_t kind;
  uint32_t kflags;
  int32_t cVars;
  int32_t cFuncs;
  int32_t flags;
  char *name;
  char *guid;
  char *docstr;
  char *custData;
  uint32_t version;
  char *dataType;
  sMSFT_TypeInfoBase *tib;
  sTI2TypeBaseMem mem;
} sTI2TypeBase;

typedef struct sTI2TypLib {
  int16_t ver_major;
  int16_t ver_minor;
  int32_t version;
  char *guid;
  uint32_t lcid1;
  uint32_t lcid2;
  uint32_t flags;
  uint32_t setFlags;
  char *helpstring;
  char *helpfile;
  int32_t helpstringctx;
  int32_t helpctx;
  char *name;
  int32_t dispatch;
  size_t nr_typinfos;
  size_t nr_impinfos;
  uint32_t *typinfos_hash;
  sTITyps ti2_typs;
  sTI2TypeBase *typb;
} sTI2TypLib;

sTI2TypLib *TI2_typlib_init (unsigned char *dta, size_t len);
void TI2_typlib_dest (sTI2TypLib *tl);
void TI2_typlib_idl (FILE *fp, sTI2TypLib *tl);
const char *getCallConvName (int32_t cc);
void printValue(FILE *fp, sTITyps *typs, uint32_t val);
char *getTypeBOrImpRef (sTITyps *dptr, uint32_t off, const char *var);

#endif
