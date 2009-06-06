#ifndef _DBG_CODEVIEW_HXX
#define _DBG_CODEVIEW_HXX

#include <stdint.h>
#include "dbg_memfile.h"

typedef struct sDbgCVtag {
  uint32_t leaf;
  int (*update)(struct sDbgCVtag *, sDbgMemFile *);
  sDbgMemFile *(*dump)(struct sDbgCVtag *, sDbgMemFile *);
  sDbgMemFile *unknown_leaf;

  uint32_t length; /* dta length */
  __extension__ union {
    unsigned char *dta;
    uint16_t *us_dta;
    uint32_t *ui_dta;
  };
} sDbgCVtag;

typedef enum eDbgCVLeaf {
  LF_MODIFIER_16t = 0x1,
  LF_POINTER_16t = 0x2,
  LF_ARRAY_16t = 0x3,
  LF_CLASS_16t = 0x4,
  LF_STRUCTURE_16t = 0x5,
  LF_UNION_16t = 0x6,
  LF_ENUM_16t = 0x7,
  LF_PROCEDURE_16t = 0x8,
  LF_MFUNCTION_16t = 0x9,
  LF_VTSHAPE = 0xA,
  LF_COBOL0_16t = 0xB,
  LF_COBOL1 = 0xC,
  LF_BARRAY_16t = 0xD,
  LF_LABEL = 0xE,
  LF_NULL = 0xF,
  LF_NOTTRAN = 0x10,
  LF_DIMARRAY_16t = 0x11,
  LF_VFTPATH_16t = 0x12,
  LF_PRECOMP_16t = 0x13,
  LF_ENDPRECOMP = 0x14,
  LF_OEM_16t = 0x15,
  LF_TYPESERVER_ST = 0x16,

  /* Only referenced from type records.  */
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
  LF_MODIFIER = 0x1001,
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

sDbgCVtag *dbg_CVtag_create (unsigned char *dta, size_t max);
void dbg_CVtag_release (sDbgCVtag *);
sDbgMemFile *dbg_CVtag_dump (sDbgCVtag *cv,sDbgMemFile *x);
int dbg_CVtag_update (sDbgCVtag *cv, sDbgMemFile *f);

typedef struct sDbgCV {
  size_t count;
  sDbgCVtag **tag;
} sDbgCV;

sDbgCV *dbg_CV_create (unsigned char *dta, size_t max);
void dbg_CV_release (sDbgCV *);
sDbgMemFile *dbg_CV_dump (sDbgCV *cv, sDbgMemFile *x);
int dbg_CV_update (sDbgCV *cv, sDbgMemFile *f);

#endif
