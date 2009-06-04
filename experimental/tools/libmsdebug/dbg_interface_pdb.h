#ifndef _DBG_INTERFACE_PDB_HXX
#define  _DBG_INTERFACE_PDB_HXX

#include "dbg_interface.h"
#include "dbg_pdb_info.h"

extern sDbgInterface interface_pdb2; /* pdb 2.0 */
extern sDbgInterface interface_pdb7; /* pdb 7.0 */

struct sPdbSymbols;

typedef struct sDbgInterfacePDB {
  sDbgInterface common;
  sDbgMemFile **files;
  uint32_t streams;
  sPdbInfo *info; /* Stream #1  */
  struct sPdbSymbols *syms;
} sDbgInterfacePDB;

#endif
