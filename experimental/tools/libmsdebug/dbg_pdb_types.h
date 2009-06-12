#ifndef _DBG_PDB_TYPES_HXX
#define _DBG_PDB_TYPES_HXX

#include "stdint.h"
#include "dbg_memfile.h"
#include "dbg_codeview.h"

#pragma pack(push,1)

typedef struct sDbgPdbTypeOffCb
{
  uint32_t off;
  uint32_t cb;
} sDbgPdbTypeOffCb;

typedef struct sDbgPdbTypeHash
{
  uint16_t sn;            // stream #
  uint16_t snPad;         // padding
  uint32_t cbHashKey;
  uint32_t cHashBuckets;
  sDbgPdbTypeOffCb offcbHashVals;
  sDbgPdbTypeOffCb offcbTiOff;
  sDbgPdbTypeOffCb offcbHashAdj;
} sDbgPdbTypeHash;

/* Stream header.  */
typedef struct sDbgPdbTypeHeader
{
  uint32_t version;     /* implementation version  */
  uint32_t cbHdr;       /* header size  */
  uint32_t tiMin;       /* type index base  (0x1000..0xFFFFFF)  */
  uint32_t tiMac;       /* type index limit (0x1000..0xFFFFFF)  */
  uint32_t cbGprec;     /* size of follow-up data  */
  sDbgPdbTypeHash tpiHash;
} sDbgPdbTypeHeader;

#pragma pack(pop)

typedef struct sPdbTypes {
  int kind;
  const char *kind_name;
  size_t cb_size;
  sDbgMemFile *memfile;
  int (*probe)(const struct sDbgMemFile *);
  int (*load)(struct sPdbTypes *);
  int (*update)(struct sPdbTypes *);
  int (*release)(struct sPdbTypes *);
  sDbgMemFile *(*dump)(struct sPdbTypes *, sDbgMemFile *);
  
  /* Local members.  */
  struct sDbgInterfacePDB *base;
  uint32_t version;
  uint32_t tiMin, tiMac;
  sDbgMemFile *hash;
  sDbgMemFile *Gprec;
  sDbgCV *types;
  sDbgPdbTypeHash tpiHash;
} sPdbTypes;

sPdbTypes *dbg_pdb_types_create (sDbgMemFile *d, struct sDbgInterfacePDB *base);
void dbg_pdb_types_release (sPdbTypes *p);
sDbgMemFile *dbg_pdb_types_dump (sPdbTypes *p, sDbgMemFile *t);

#endif
