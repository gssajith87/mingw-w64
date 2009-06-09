#ifndef _DBG_PDB_INFO_HXX
#define _DBG_PDB_INFO_HXX

#include "stdint.h"
#include "dbg_memfile.h"

#pragma pack(push,1)

typedef struct sPdbStreamInfo {
  uint32_t version;
  uint32_t timestamp;
  uint32_t age;
  unsigned char guid[16];
  uint32_t cb_name;
  /* char name[cb_name]; */
  /* uint32_t unknown.  */
} sPdbStreamInfo;

typedef struct sPdbInfo {
  uint32_t version;
  uint32_t timestamp;
  uint32_t age;
  unsigned char guid[16];
  uint32_t cb_name;
  uint32_t c_unknown;
  char *name;
  uint32_t *unknown;
} sPdbInfo;

#pragma pack(pop)

#define PDB_STREAM_INFO	1

sPdbInfo *dbg_readPdbInfo (const sDbgMemFile *f);
int dbg_writePdbInfo (sDbgMemFile *f, size_t off, const sPdbInfo *info);
int dbg_dumpPdbInfo (sDbgMemFile *t, const sPdbInfo *info);

#endif
