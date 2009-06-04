#ifndef _DBG_PDB_SYMBOLS_HXX
#define _DBG_PDB_SYMBOLS_HXX

#include <stdint.h>
#include "dbg_memfile.h"
#include "dbg_interface_pdb.h"

typedef struct sPdbStreamSymbolsV1
{
  uint16_t hash1_file;
  uint16_t hash2_file;
  uint16_t gsym_file;
  uint16_t pad;
  uint32_t module_size;
  uint32_t offset_size;
  uint32_t hash_size;
  uint32_t srcmodule_size;
} sPdbStreamSymbolsV1;

typedef struct sPdbStreamSymbolsV2
{
  uint32_t signature;
  uint32_t version;
  uint32_t extended_format;
  uint16_t hash1_file;
  uint16_t hash1_unknown;
  uint16_t hash2_file;
  uint16_t hash2_unknown;
  uint16_t gsym_file;
  uint16_t gsym_unknown;
  uint32_t module_size;
  uint32_t offset_size;
  uint32_t hash_size;
  uint32_t srcmodule_size;
  uint32_t pdbimport_size;
  uint32_t unknown1_size;
  uint32_t unknown2_size;
  uint32_t unknown3_size;
  uint32_t resvd[2];
} sPdbStreamSymbolsV2;

#define DBG_PDB_SYMBOLV2_MAGIC	0xffffffffU

typedef enum ePdbSymbolsTypes {
  ePdbSymbols_v1 = 0,
  ePdbSymbols_v2 = 1,
  ePdbSymbols_max
} ePdbSymbolsTypes;

typedef struct sPdbSymbols
{
  ePdbSymbolsTypes kind;
  const char *kind_name;
  size_t cb_size;
  sDbgMemFile *memfile;
  int (*probe)(const struct sDbgMemFile *);
  int (*load)(struct sPdbSymbols *);
  int (*update)(struct sPdbSymbols *);
  int (*release)(struct sPdbSymbols *);
  sDbgMemFile *(*dump)(struct sPdbSymbols *s, sDbgMemFile *t);
  
  /* Local members.  */
  sDbgInterfacePDB *base;
  int stream_idx;
  uint32_t signature;
  uint32_t version;
  uint32_t extended_format;
  uint32_t hash1_file;
  uint32_t hash2_file;
  uint32_t gsym_file;
  uint32_t module_size;
  uint32_t offset_size;
  uint32_t hash_size;
  uint32_t srcmodule_size;
  uint32_t pdbimport_size;
  uint32_t unknown1_size;
  uint32_t unknown2_size;
  uint32_t unknown3_size;
  uint32_t reserved[2];
} sPdbSymbols;

sPdbSymbols *dbg_symbols_load (sDbgMemFile *f, sDbgInterfacePDB *base, int stream_idx);
void dbg_symbol_release (sPdbSymbols *s);

#endif
