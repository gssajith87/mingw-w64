#ifndef _DBG_INTERFACE_PDB_HXX
#define  _DBG_INTERFACE_PDB_HXX

#include "dbg_interface.h"

extern sDbgInterface interface_pdb2; /* pdb 2.0 */
extern sDbgInterface interface_pdb7; /* pdb 7.0 */

typedef struct sDbgInterfacePDB {
  sDbgInterface common;
} sDbgInterfacePDB;


#endif
