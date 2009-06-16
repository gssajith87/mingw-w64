#ifndef _DBG_CV_LF_HXX
#define _DBG_CV_LF_HXX

#pragma pack (push, 1)

typedef struct CV_Line_t {
  uint32_t offset;
  uint32_t linenumStart;
  uint32_t deltaLineEnd;
  uint32_t fStatement;
} CV_Line_t;

typedef struct CV_Column_t {
  uint16_t offColumnStart;
  uint16_t offColumnEnd;
} CV_Column_t;

typedef enum eCV_access {
  CV_private = 1,
  CV_protected = 2,
  CV_public = 3,
} eCV_access;

typedef enum eCV_call {
  CV_CALL_NEAR_C = 0,
  CV_CALL_FAR_C = 1,
  CV_CALL_NEAR_PASCAL = 2,
  CV_CALL_FAR_PASCAL = 3,
  CV_CALL_NEAR_FAST = 4,
  CV_CALL_FAR_FAST = 5,
  CV_CALL_SKIPPED = 6,
  CV_CALL_NEAR_STD = 7,
  CV_CALL_FAR_STD = 8,
  CV_CALL_NEAR_SYS = 9,
  CV_CALL_FAR_SYS = 10,
  CV_CALL_THISCALL = 11,
  CV_CALL_MIPSCALL = 12,
  CV_CALL_GENERIC = 13,
  CV_CALL_ALPHACALL = 14,
  CV_CALL_PPCCALL = 15,
  CV_CALL_SHCALL = 16,
  CV_CALL_ARMCALL = 17,
  CV_CALL_AM33CALL = 18,
  CV_CALL_TRICALL = 19,
  CV_CALL_SH5CALL = 20,
  CV_CALL_M32RCALL = 21,
  CV_CALL_CLRCALL = 22,
  CV_CALL_RESERVED = 23
} eCV_call;
static void dump_CV_call (unsigned char call, sDbgMemFile *t);

typedef enum eCV_methodprop {
  CV_MTvanilla = 0,
  CV_MTvirtual = 1,
  CV_MTstatic = 2,
  CV_MTfriend = 3,
  CV_MTintro = 4,
  CV_MTpurevirt = 5,
  CV_MTpureintro = 6,
} eCV_methodprop;

typedef struct CV_modifier_t {
  uint16_t MOD_const : 1;
  uint16_t MOD_volatile : 1;
  uint16_t MOD_unaligned : 1;
  uint16_t MOD_unused : 13;
} CV_modifier_t;
static void dump_CV_modifier_t (CV_modifier_t *m, sDbgMemFile *t);

typedef struct CV_fldattr_t {
  uint16_t access : 2; /* eCV_access */
  uint16_t mprop : 3;  /* eCV_methodprop */
  uint16_t pseudo : 1;
  uint16_t noinherit : 1;
  uint16_t noconstruct : 1;
  uint16_t compgenx : 1;
  uint16_t sealed : 1;
  uint16_t unused : 6;
} CV_fldattr_t;
static void dump_CV_fldattr_t (CV_fldattr_t *m, sDbgMemFile *t);

typedef struct CV_funcattr_t {
  unsigned char cxxreturnudt : 1;
  unsigned char ctor : 1;
  unsigned char ctorvbase : 1;
  unsigned char unused : 5;
} CV_funcattr_t;
static void dump_CV_funcattr_t (CV_funcattr_t *m, sDbgMemFile *t);

typedef struct CV_prop_t {
  uint16_t packed : 1;
  uint16_t ctor : 1;
  uint16_t ovlops : 1;
  uint16_t isnested : 1;
  uint16_t cnested : 1;
  uint16_t opassign : 1;
  uint16_t opcast : 1;
  uint16_t fwdref : 1;
  uint16_t scoped : 1;
  uint16_t hasuniquename : 1;
  uint16_t sealed : 1;
  uint16_t hfa : 2;
  uint16_t intrinsic : 1;
  uint16_t reserved : 2;
} CV_prop_t;
static void dump_CV_prop_t (CV_prop_t *m, sDbgMemFile *t);

typedef enum eCV_vtshape {
  CV_VTNEAR = 0,
  CV_VTFAR = 1,
  CV_VTTHIN = 2,
  CV_VTAPDISP = 3,
  CV_VTFPMETA = 4,
  CV_VTNEAR32 = 5,
  CV_VTFAR32 = 6,
} eCV_vtshape;
static void dump_CV_vtshape (unsigned char vt, sDbgMemFile *t);

typedef enum eCV_sourcechksum {
  CV_SRCCHKSUM_TYPE_NONE = 0,
  CV_SRCCHKSUM_TYPE_MD5 = 1,
  CV_SRCCHKSUM_TYPE_SHA1 = 2,
} eCV_sourcechksum;

typedef enum eCV_HFA {
  CV_HFA_none = 0,
  CV_HFA_float = 1,
  CV_HFA_double = 2,
} eCV_HFA;

typedef enum eCV_ptrmode {
  CV_PTR_MODE_PTR = 0,
  CV_PTR_MODE_REF = 1,
  CV_PTR_MODE_PMEM = 2,
  CV_PTR_MODE_PMFUNC = 3,
  CV_PTR_MODE_RESERVED = 4
} eCV_ptrmode;
static void dump_CV_ptrmode (uint32_t pm, sDbgMemFile *t);

typedef enum eCV_ptrtype {
  CV_PTR_NEAR = 0,
  CV_PTR_FAR = 1,
  CV_PTR_HUGE = 2,
  CV_PTR_BASE_SEG = 3,
  CV_PTR_BASE_VAL = 4,
  CV_PTR_BASE_SEGVAL = 5,
  CV_PTR_BASE_ADDR = 6,
  CV_PTR_BASE_SEGADDR = 7,
  CV_PTR_BASE_TYPE = 8,
  CV_PTR_BASE_SELF = 9,
  CV_PTR_NEAR32 = 10,
  CV_PTR_FAR32 = 11,
  CV_PTR_64 = 12,
  CV_PTR_UNUSEDPTR = 13
} eCV_ptrtype;
static void dump_CV_ptrtype (uint32_t pt, sDbgMemFile *t);

typedef enum eCV_prmode {
  CV_TM_DIRECT = 0,
  CV_TM_NPTR = 1,
  CV_TM_FPTR = 2,
  CV_TM_HPTR = 3,
  CV_TM_NPTR32 = 4,
  CV_TM_FPTR32 = 5,
  CV_TM_NPTR64 = 6,
  CV_TM_NPTR128 = 7,
} eCV_prmode;

typedef enum eCV_type {
  CV_SPECIAL = 0,
  CV_SIGNED = 1,
  CV_UNSIGNED = 2,
  CV_BOOLEAN = 3,
  CV_REAL = 4,
  CV_COMPLEX = 5,
  CV_SPECIAL2 = 6,
  CV_INT = 7,
  CV_CVRESERVED = 15
} eCV_type;

typedef enum eCV_real {
  CV_RC_REAL32 = 0,
  CV_RC_REAL64 = 1,
  CV_RC_REAL80 = 2,
  CV_RC_REAL128 = 3,
  CV_RC_REAL48 = 4
} eCV_real;

typedef enum eCV_int {
  CV_RI_CHAR = 0, CV_RI_INT1 = 0,
  CV_RI_UCHAR = 1, CV_RI_UINT1 = 1,
  CV_RI_INT2 = 2,
  CV_RI_UINT2 = 3,
  CV_RI_INT4 = 4,
  CV_RI_UINT4 = 5,
  CV_RI_INT8 = 6,
  CV_RI_UINT8 = 7,
  CV_RI_INT16 = 8,
  CV_RI_UINT16 = 9
} eCV_int;

typedef enum eCV_integral {
  CV_IN_1BYTE = 0,
  CV_IN_2BYTE = 1,
  CV_IN_4BYTE = 2,
  CV_IN_8BYTE = 3,
  CV_IN_16BYTE = 4
} eCV_integral;
  
typedef enum eCV_special {
  CV_SP_NOTYPE = 0,
  CV_SP_ABS = 1,
  CV_SP_SEGMENT = 2,
  CV_SP_VOID = 3,
  CV_SP_CURRENCY = 4,
  CV_SP_NBASICSTR = 5,
  CV_SP_FBASICSTR = 6,
  CV_SP_NOTTRANS = 7,
  CV_SP_HRESULT = 8,
} eCV_special;

  typedef union uCV_type {
  uint32_t type;
  __extension__ struct {
    unsigned short type_spec : 4; /* eCV_real, eCV_int, eCV_integral, eCV_special */
    unsigned short type_kind : 4; /* eCV_type */
  };
} uCV_type;

typedef enum eCV_pmtype {
  CV_PMTYPE_Undef = 0,
  CV_PMTYPE_D_Single = 1,
  CV_PMTYPE_D_Multiple = 2,
  CV_PMTYPE_D_Virtual = 3,
  CV_PMTYPE_D_General = 4,
  CV_PMTYPE_F_Single = 5,
  CV_PMTYPE_F_Multiple = 6,
  CV_PMTYPE_F_Virtual = 7,
  CV_PMTYPE_F_General = 8
} eCV_pmtype;

typedef struct lfVTshape { /* LF_VTSHAPE */
  /* uint16_t leaf; */
  uint16_t count;
  unsigned char vtshape[1];
} lfVTshape;
static void dump_lfVTshape (lfVTshape *m, sDbgMemFile *t);

typedef struct lmFunc { /* LF_MFUNCTION */
  /*uint16_t leaf; */
  uint32_t rvtype;
  uint32_t classtype;
  uint32_t thistype;
  unsigned char calltype;
  CV_funcattr_t funcattr;
  uint16_t parmcount;
  uint32_t arglist;
  long thisadjust;
} lmFunc;
static void dump_lmFunc (lmFunc *m, sDbgMemFile *t);

typedef struct lfMethodList { /* LF_METHODLIST */
  /* uint16_t leaf; */
  uint32_t offset[1];
} lfMethodList;
static void dump_lfMethodList (lfMethodList *m, size_t size, sDbgMemFile *t);

typedef struct lfArgList { /* LF_ARGLIST */
  /* uint16_t leaf; */
  uint32_t count;
  uint32_t arg[0]; /* argument types */
} lfArgList;
static void dump_lfArgList (lfArgList *m, sDbgMemFile *t);

typedef struct lfIndex {
  uint16_t leaf;
  uint16_t pad;
  uint32_t index;
} lfIndex;

typedef struct lfVFuncTab { /* LF_VFUNCTAB */
  uint16_t leaf;
  uint16_t pad;
  uint32_t type;
} lfVFuncTab;

typedef struct lfProc { /* LF_PROCEDURE */
  /* uint16_t leaf; */
  uint32_t rvtype;
  unsigned char calltype;
  CV_funcattr_t funcattr;
  uint16_t parmcount;
  uint32_t arglist;
} lfProc;
static void dump_lfProc (lfProc *m, sDbgMemFile *t);

typedef struct lfModifier { /* LF_MODIFIER */
  /*uint16_t leaf; */
  uint32_t type;
  CV_modifier_t attr;
} lfModifier;
static void dump_lfModifier (lfModifier *m, sDbgMemFile *t);

typedef struct lfArray { /* LF_ARRAY */
  /* uint16_t leaf; */
  uint32_t elemtype;
  uint32_t idxtype;
  uint16_t size;
  unsigned char data[0]; /* size in bytes */
} lfArray;
static void dump_lfArray (lfArray *m, sDbgMemFile *t);

typedef struct lfBitfield { /* LF_BITFIELD */
  /* uint16_t leaf; */
  uint32_t type;
  unsigned char length;
  unsigned char position;
} lfBitfield;
static void dump_lfBitfield (lfBitfield *m, sDbgMemFile *t);

typedef struct lfPointerBody {
  uint16_t leaf;
  uint32_t utype;
} lfPointerBody;

typedef struct lfPointer { /* LF_POINTER */
  /*uint16_t leaf;*/
  uint32_t utype;
  struct lfPointerAttr {
    uint32_t ptrtype : 5;
    uint32_t ptrmode : 3;
    uint32_t isflat32 : 1;
    uint32_t isvolatile : 1;
    uint32_t isconst : 1;
    uint32_t isunaligned : 1;
    uint32_t isrestrict : 1;
    uint32_t size : 6;
    uint32_t unused : 13;
  } attr;
  union {
    struct {
      uint32_t pmclass;
      uint16_t pmenum;
    } pm;
    uint16_t bseg;
    unsigned char Sym[1];
    struct {
      uint32_t index;
      unsigned char name [1];
    } btype;
  } pbase;
} lfPointer;
static void dump_lfPointer (lfPointer *m, sDbgMemFile *t);

typedef struct lfChar {
  uint16_t leaf;
  unsigned char val;
} lfChar;

typedef struct lfShort {
  uint16_t leaf;
  short val;
} lfShort;

typedef struct lfUShort {
  uint16_t leaf;
  uint16_t val;
} lfUShort;

typedef struct lfLong {
  uint16_t leaf;
  long val;
} lfLong;

typedef struct lfULong {
  uint16_t leaf;
  uint32_t val;
} lfULong;

typedef struct lfQuad {
  uint16_t leaf;
  unsigned char val[8];
} lfQuad;

typedef struct lfUQuad {
  uint16_t leaf;
  unsigned char val[8];
} lfUQuad;

typedef struct lfClass {
  /*uint16_t leaf;*/
  uint16_t count;
  CV_prop_t property;
  uint32_t field;
  uint32_t derived;
  uint32_t vshape;
  uint16_t size;
  unsigned char data[0];
} lfClass;
static void dump_lfClass (lfClass *m, sDbgMemFile *t);

typedef struct lfStruct { /* LF_STRUCTURE */
  /*uint16_t leaf; */
  uint16_t count;
  CV_prop_t property;
  uint32_t field;
  uint32_t derived;
  uint32_t vshape;
  uint16_t size;
  unsigned char data[0];
} lfStruct;
static void dump_lfStruct (lfStruct *m, sDbgMemFile *t);

typedef struct lfUnion { /* LF_UNION */
  /*uint16_t leaf;*/
  uint16_t count;
  CV_prop_t property;
  uint32_t field;
  uint16_t size;
  unsigned char data[0];
} lfUnion;
static void dump_lfUnion (lfUnion *m, sDbgMemFile *t);

typedef struct lfEnum { /* LF_ENUMERATE */
  /* uint16_t leaf; */
  uint16_t count;
  CV_prop_t property;
  uint32_t utype;
  uint32_t field;
  unsigned char name[1];
} lfEnum;
static void dump_lfEnum (lfEnum *m, sDbgMemFile *t);

typedef struct lfBClass { /* LF_BCLASS */
  /*uint16_t leaf;*/
  CV_fldattr_t attr;
  uint32_t index;
  unsigned char offset[0];
} lfBClass;
static void dump_lfBClass (lfBClass *m, sDbgMemFile *t);

typedef struct lfVBClass {
  uint16_t leaf;
  CV_fldattr_t attr;
  uint32_t index;
  uint32_t vbptr;
  unsigned char vboff[0];
} lfVBClass;

typedef struct lfMember {
  uint16_t leaf;
  CV_fldattr_t attr;
  uint32_t index;
  unsigned char offset[0];
} lfMember;

typedef struct lfSTMember { /* LF_STMEMBER */
  /*uint16_t leaf;*/
  CV_fldattr_t attr;
  uint32_t index;
  unsigned char name[1];
} lfSTMember;
static void dump_lfSTMember (lfSTMember *m, sDbgMemFile *t);

typedef struct lfMethod { /* LF_METHOD */
  uint16_t leaf;
  uint16_t count;
  uint32_t mList;
  unsigned char name[1];
} lfMethod;

typedef struct lfNestType { /* LF_NESTTYPE */
  /* uint16_t leaf; */
  uint16_t pad;
  uint32_t index;
  unsigned char name[1];
} lfNestType;
static void dump_lfNestType (lfNestType *m, sDbgMemFile *t);

typedef struct lfOneMethod { /* LF_ONEMETHOD */
  /* uint16_t leaf; */
  CV_fldattr_t attr;
  uint32_t index;
  uint32_t vbaseoff[0];
} lfOneMethod;
static void dump_lfOneMethod (lfOneMethod *m, sDbgMemFile *x);

typedef struct lfFieldList { /* LF_FIELDLIST */
  /* uint16_t leaf; */
  char data[1];
} lfFieldList;
static void dump_lfFieldList (lfFieldList *m, size_t size, sDbgMemFile *t);

typedef struct lfEnumFieldList {
  uint16_t leaf;
  CV_fldattr_t attr;
  unsigned char value[1];
} lfEnumFieldList;

typedef struct lfMemberFL {
  uint16_t leaf;
  CV_fldattr_t attr;
  uint32_t index;
  uint16_t offset;
  char name[1];
} lfMemberFL;

typedef struct lfOneMethodFL {
  uint16_t leaf; /* LF_ONEMETHOD */
  CV_fldattr_t attr;
  uint32_t index;
  uint32_t vbaseoff[0];
} lfOneMethodFL;

typedef struct lfNestTypeFL { /* LF_NESTTYPE */
   uint16_t leaf;
  uint16_t pad;
  uint32_t index;
  unsigned char name[1];
} lfNestTypeFL;

typedef struct lfSTMemberFL {
  uint16_t leaf;
  CV_fldattr_t attr;
  uint32_t index;
  char name[1];
} lfSTMemberFL;

typedef struct lfBClassFL {
  uint16_t leaf; /* LF_BCLASS */
  uint16_t pad;
  uint32_t utype;
  uint16_t off; /* ??? */
} lfBClassFL; /* TODO */

typedef union lfEasy {
  uint16_t leaf;
  lfEnumFieldList enumFL;
  lfMemberFL memberFL; /* LF_MEMBER lfMember */
  lfOneMethodFL oneMethodFL;
  lfNestTypeFL nestTypeFL;
  lfSTMemberFL stMemberFL;
  lfMethod methodFL;
  lfBClassFL bClassFL;
  lfVFuncTab vfunctabFL;
} lfEasy;

typedef struct _GUID {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  unsigned char data4[8];
} _GUID;

typedef struct lfTypeServer2 { /* LF_TYPESERVER2 */
  uint16_t leaf;
  struct _GUID sig70;
  uint32_t age;
  unsigned char name[0];
} lfTypeServer2;

typedef struct lfPreComp { /* LF_PRECOMP */
  uint16_t leaf;
  uint32_t start;
  uint32_t count;
  uint32_t signature;
  unsigned char name[0];
} lfPreComp;

#define LF_MODIFIER_16t 0x1
#define LF_MODIFIER 0x1001
#define LF_POINTER_16t	0x2
#define LF_ARRAY_16t	0x3
#define LF_CLASS_16t	0x4
#define LF_STRUCTURE_16t 0x5
#define LF_UNION_16t	0x6
#define LF_ENUM_16t	0x7
#define LF_PROCEDURE_16t 0x8
#define LF_MFUNCTION_16t 0x9
#define LF_VTSHAPE 0xa
#define LF_COBOL0_16t 0xb
#define LF_COBOL1     0xc
#define LF_BARRAY_16t 0xd
#define LF_LABEL 0xe
#define LF_NULL 0xf
#define LF_NOTTRAN 0x10
#define LF_DIMARRAY_16t 0x11
#define LF_VFTPATH_16t 0x12
#define LF_PRECOMP_16t 0x13
#define LF_ENDPRECOMP 0x14
#define LF_OEM_16t 0x15
#define LF_TYPESERVER_ST 0x16

typedef enum eDbgCVLeaf {
  LF_SKIP_16t = 0x200,
  LF_ARGLIST_16t = 0x201,
  LF_DEFARG_16t = 0x202,
  LF_LIST = 0x203,
  LF_FIELDLIST_16t = 0x204,
  LF_DERIVED_16t = 0x205,
  LF_BITFIELD_16t = 0x206,
  LF_METHODLIST_16t = 0x207,
  LF_DIMCONU_16t = 0x208,
  LF_DIMCONLU_16t = 0x209,
  LF_DIMVARU_16t = 0x20A,
  LF_DIMVARLU_16t = 0x20B,
  LF_REFSYM = 0x20C,

  LF_BCLASS_16t = 0x400,
  LF_VBCLASS_16t = 0x401,
  LF_IVBCLASS_16t = 0x402,
  LF_ENUMERATE_ST = 0x403,
  LF_FRIENDFCN_16t = 0x404,
  LF_INDEX_16t = 0x405,
  LF_MEMBER_16t = 0x406,
  LF_STMEMBER_16t = 0x407,
  LF_METHOD_16t = 0x408,
  LF_NESTTYPE_16t = 0x409,
  LF_VFUNCTAB_16t = 0x40A,
  LF_FRIENDCLS_16t = 0x40B,
  LF_ONEMETHOD_16t = 0x40C,
  LF_VFUNCOFF_16t = 0x40D,

  LF_TI16_MAX = 0x1000,
  LF_POINTER = 0x1002,
  LF_ARRAY_ST = 0x1003,
  LF_CLASS_ST = 0x1004,
  LF_STRUCTURE_ST = 0x1005,
  LF_UNION_ST = 0x1006,
  LF_ENUM_ST = 0x1007,
  LF_PROCEDURE = 0x1008,
  LF_MFUNCTION = 0x1009,
  LF_COBOL0 = 0x100A,
  LF_BARRAY = 0x100B,
  LF_DIMARRAY_ST = 0x100C,
  LF_VFTPATH = 0x100D,
  LF_PRECOMP_ST = 0x100E,
  LF_OEM = 0x100F,
  LF_ALIAS_ST = 0x1010,
  LF_OEM2 = 0x1011,

  LF_SKIP = 0x1200,
  LF_ARGLIST = 0x1201,
  LF_DEFARG_ST = 0x1202,
  LF_FIELDLIST = 0x1203,
  LF_DERIVED = 0x1204,
  LF_BITFIELD = 0x1205,
  LF_METHODLIST = 0x1206,
  LF_DIMCONU = 0x1207,
  LF_DIMCONLU = 0x1208,
  LF_DIMVARU = 0x1209,
  LF_DIMVARLU = 0x120A,

  LF_BCLASS = 0x1400,
  LF_VBCLASS = 0x1401,
  LF_IVBCLASS = 0x1402,
  LF_FRIENDFCN_ST = 0x1403,
  LF_INDEX = 0x1404,
  LF_MEMBER_ST = 0x1405,
  LF_STMEMBER_ST = 0x1406,
  LF_METHOD_ST = 0x1407,
  LF_NESTTYPE_ST = 0x1408,
  LF_VFUNCTAB = 0x1409,
  LF_FRIENDCLS = 0x140A,
  LF_ONEMETHOD_ST = 0x140B,
  LF_VFUNCOFF = 0x140C,
  LF_NESTTYPEEX_ST = 0x140D,
  LF_MEMBERMODIFY_ST = 0x140E,
  LF_MANAGED_ST = 0x140F,

  LF_ST_MAX = 0x1500,
  LF_TYPESERVER = 0x1501,
  LF_ENUMERATE = 0x1502,
  LF_ARRAY = 0x1503,
  LF_CLASS = 0x1504,
  LF_STRUCTURE = 0x1505,
  LF_UNION = 0x1506,
  LF_ENUM = 0x1507,
  LF_DIMARRAY = 0x1508,
  LF_PRECOMP = 0x1509,
  LF_ALIAS = 0x150A,
  LF_DEFARG = 0x150B,
  LF_FRIENDFCN = 0x150C,
  LF_MEMBER = 0x150D,
  LF_STMEMBER = 0x150E,
  LF_METHOD = 0x150F,
  LF_NESTTYPE = 0x1510,
  LF_ONEMETHOD = 0x1511,
  LF_NESTTYPEEX = 0x1512,
  LF_MEMBERMODIFY = 0x1513,
  LF_MANAGED = 0x1514,
  LF_TYPESERVER2 = 0x1515,

  LF_NUMERIC = 0x8000,
  LF_CHAR = 0x8000,
  LF_SHORT = 0x8001,
  LF_USHORT = 0x8002,
  LF_LONG = 0x8003,
  LF_ULONG = 0x8004,
  LF_REAL32 = 0x8005,
  LF_REAL64 = 0x8006,
  LF_REAL80 = 0x8007,
  LF_REAL128 = 0x8008,
  LF_QUADWORD = 0x8009,
  LF_UQUADWORD = 0x800A,
  LF_REAL48 = 0x800B,
  LF_COMPLEX32 = 0x800C,
  LF_COMPLEX64 = 0x800D,
  LF_COMPLEX80 = 0x800E,
  LF_COMPLEX128 = 0x800F,
  LF_VARSTRING = 0x8010,
  /* If BigInt support.  */
  LF_OCTWORD = 0x8017,
  LF_UOCTWORD = 0x8018,
  LF_DECIMAL = 0x8019,
  LF_DATE = 0x801A,
  LF_UTF8STRING = 0x801B,

  LF_PAD0 = 0xF0,
  LF_PAD1 = 0xF1,
  LF_PAD2 = 0xF2,
  LF_PAD3 = 0xF3,
  LF_PAD4 = 0xF4,
  LF_PAD5 = 0xF5,
  LF_PAD6 = 0xF6,
  LF_PAD7 = 0xF7,
  LF_PAD8 = 0xF8,
  LF_PAD9 = 0xF9,
  LF_PAD10 = 0xFA,
  LF_PAD11 = 0xFB,
  LF_PAD12 = 0xFC,
  LF_PAD13 = 0xFD,
  LF_PAD14 = 0xFE,
  LF_PAD15 = 0xFF,
  eDbgCVLeaf_max
} eDbgCVLeaf;

/* Misc */
typedef struct Scpx8_t {
  float S_re;
  float S_im;
} Scpx8_t;

typedef struct PchHd_s {
  unsigned char signature[12];
  uint32_t version;
  uint32_t sizecheck;
  char buildTimeStamp[20];
} PchHd_s;
typedef struct PchHD_s_pchILsizes {
  long ilsLSym;
  long ilsGSym;
  long ilsExp;
  long ilsInit;
  long ilsDB;
  long I_sbrfp;
} PchHD_s_pchILsizes;
typedef struct PchILsizes {
  long ilsLSym;
  long  ilsGSym;
  long ilsExp;
  long  ilsInit;
  long  ilsDB;
  long  I_sbrfp;
  PchHD_s_pchILsizes ILSizes;
  long ILPos;
  long DirsSize;
  long DirsPos;
  long HeapDumpPos;
  long p_PchSegCount;
  int PchMaxSegCount;
} PchILsizes;

#pragma pack(pop)

#endif
