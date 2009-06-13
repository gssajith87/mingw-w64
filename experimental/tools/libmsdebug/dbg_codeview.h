#ifndef _DBG_CODEVIEW_HXX
#define _DBG_CODEVIEW_HXX

#include "stdint.h"
#include "dbg_memfile.h"

#define DBG_CV_S_COMPILE  0x1
#define DBG_CV_S_END 0x6
#define DBG_CV_S_FRAMEPROC  0x1012
#define DBG_CV_S_OBJNAME  0x1101
#define DBG_CV_S_THUNK32  0x1102
#define DBG_CV_S_BLOCK32  0x1103
#define DBG_CV_S_WITH32   0x1104
#define DBG_CV_S_LABEL32  0x1105
#define DBG_CV_S_REGISTER 0x1106
#define DBG_CV_S_CONSTANT 0x1107
#define DBG_CV_S_UDT 0x1108
#define DBG_CV_S_BPREL32 0x110b
#define DBG_CV_S_LDATA32 0x110c
#define DBG_CV_S_GDATA32 0x110d
#define DGB_CV_S_PUB32  0x110e
#define DBG_CV_S_LPROC32 0x110f
#define DBG_CV_S_GPROC32 0x1110
#define DBG_CV_S_COMPILE2 0x1116
#define DBG_CV_S_LMANDATA 0x111C
#define DBG_CV_S_GMANDATA 0x111D
#define DBG_CV_S_MANSLOT 0x1120
#define DBG_CV_S_PROCREF 0x1125
#define DBG_CV_S_LPROCREF 0x1127
#define DBG_CV_S_TOKENREF 0x1129
#define DBG_CV_S_GMANPROC 0x112a
#define DBG_CV_S_LMANPROC 0x112b
#define DBG_CV_S_SECTION32 0x1136
#define DBG_CV_S_SECTIONINFO32 0x1137
#define DBG_CV_S_MSUNK1 0x1139
#define DBG_CV_S_MSUNK2 0x113a
#define DBG_CV_S_COMPILER 0x113c
#define DBG_CV_S_BUILDCMD 0x113d

#include "dbg_cv_lf.h"

typedef struct sDbgCVtag {
  uint32_t leaf;
  int (*update)(struct sDbgCVtag *, sDbgMemFile *);
  sDbgMemFile *(*dump)(struct sDbgCVtag *, sDbgMemFile *);
  sDbgMemFile *unknown_leaf;

  int be_syms;
  uint32_t length; /* dta length */
  __extension__ union {
    unsigned char *dta;
    uint16_t *us_dta;
    uint32_t *ui_dta;
  };
} sDbgCVtag;

sDbgCVtag *dbg_CVtag_create (unsigned char *dta, size_t max, int be_syms);
void dbg_CVtag_release (sDbgCVtag *);
sDbgMemFile *dbg_CVtag_dump (sDbgCVtag *cv,sDbgMemFile *x);
int dbg_CVtag_update (sDbgCVtag *cv, sDbgMemFile *f);

typedef struct sDbgCV {
  size_t count;
  sDbgCVtag **tag;
} sDbgCV;

sDbgCV *dbg_CV_create (unsigned char *dta, size_t max, int be_syms);
void dbg_CV_release (sDbgCV *);
sDbgMemFile *dbg_CV_dump (sDbgCV *cv, sDbgMemFile *x);
int dbg_CV_update (sDbgCV *cv, sDbgMemFile *f);

#endif
