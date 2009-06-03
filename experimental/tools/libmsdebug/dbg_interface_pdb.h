#ifndef _DBG_INTERFACE_PDB_HXX
#define  _DBG_INTERFACE_PDB_HXX

#include "dbg_interface.h"

extern sDbgInterface interface_pdb2; /* pdb 2.0 */
extern sDbgInterface interface_pdb7; /* pdb 7.0 */

typedef struct sDbgInterfacePDB2 {
  sDbgInterface common;
} sDbgInterfacePDB2;

typedef struct sDbgInterfacePDB7 {
  sDbgInterface common;
} sDbgInterfacePDB7;

#endif
