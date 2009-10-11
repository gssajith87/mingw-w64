#ifndef _DBG_INTERFACE_PDB_HXX
#define  _DBG_INTERFACE_PDB_HXX

#include "dbg_interface.h"
#include "dbg_pdb_info.h"
#include "dbg_pdb_types.h"

extern sDbgInterface interface_pdb2; /* pdb 2.0 */
extern sDbgInterface interface_pdb7; /* pdb 7.0 */

struct sPdbSymbols;

typedef struct sDbgInterfacePDB {
  sDbgInterface common;
  sDbgMemFile **files;
  const char **files_kind;
  uint32_t streams;
  sPdbInfo *info; /* Stream #1  */
  struct sPdbSymbols *syms;
  struct sPdbTypes *typs;
} sDbgInterfacePDB;

#define DbgInterfacePDB_streams(PTR)	((sDbgInterfacePDB *) (PTR))->streams
#define DbgInterfacePDB_file(PTR,IDX)	((sDbgInterfacePDB *) (PTR))->files[(IDX)]
#define DbgInterfacePDB_file_kind(PTR,IDX) ((sDbgInterfacePDB *) (PTR))->files_kind[(IDX)]
#endif
