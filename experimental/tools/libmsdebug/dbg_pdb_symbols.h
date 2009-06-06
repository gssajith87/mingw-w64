#ifndef _DBG_PDB_SYMBOLS_HXX
#define _DBG_PDB_SYMBOLS_HXX

#include <stdint.h>
#include "dbg_memfile.h"
#include "dbg_interface_pdb.h"
#include "dbg_codeview.h"

#pragma pack(push, 1)

typedef struct sPdbStreamSymbolsV1
{
  uint16_t hash1_file; /* GS */
  uint16_t hash2_file; /* PS */
  uint16_t gsym_file;  /* SymRec */
  uint16_t pad;
  uint32_t module_size;
  uint32_t sectioninfo_size; /* SC */
  uint32_t sectionmap_size;
  uint32_t srcmodule_size; /* File info */
} sPdbStreamSymbolsV1;

typedef struct sPdbStreamSymbolsV2
{
  uint32_t signature;
  uint32_t version;
  uint32_t extended_format; /* Age */
  uint16_t hash1_file; /* GS */
  uint16_t verPdbDLL;
  uint16_t hash2_file; /* PS */
  uint16_t verPdbDLLBuild;
  uint16_t gsym_file; /* SymRec */
  uint16_t gsym_unknown;
  uint32_t module_size;
  uint32_t sectioninfo_size; /* SC */
  uint32_t sectionmap_size; /* SecMap */
  uint32_t srcmodule_size; /* File Information */
  uint32_t pdbimport_size; /* TS map */
  uint32_t unknown1_size;  /* iMFC */
  uint32_t unknown2_size;  /* Debug header */
  uint32_t unknown3_size;  /* EC info */
  uint16_t flags;
  uint16_t machine;
  uint32_t resvd[1];
} sPdbStreamSymbolsV2;

#define DBG_PDB_STREAM_VERSION_V2	4046371373U

typedef struct sPdbStreamSectionInfoV1
{
  uint16_t isect;
  uint16_t reserved1;
  uint32_t off;
  uint32_t cbSectionSize;
  uint32_t characteristics;
  uint16_t imod;
  uint16_t reserved2;
} sPdbStreamSectionInfoV1;

typedef struct sPdbStreamSectionInfoV2
{
  uint16_t isect;
  uint16_t reserved1;
  uint32_t off;
  uint32_t cbSectionSize;
  uint32_t characteristics;
  uint16_t imod;
  uint16_t reserved2;
  uint32_t dataCRC;
  uint32_t relocCRC;
} sPdbStreamSectionInfoV2;

typedef struct sPdbSectionInfoElement
{
  uint16_t isect;
  uint16_t reserved1;
  uint32_t off;
  uint32_t cbSectionSize;
  uint32_t characteristics;
  uint16_t imod;
  uint16_t reserved2;
  uint32_t dataCRC;
  uint32_t relocCRC;
} sPdbSectionInfoElement;

typedef struct sPdbSectionInfo
{
  uint32_t signature;
  int version;
  size_t count;
  sPdbSectionInfoElement elm[1];
} sPdbSectionInfo;

typedef struct sPdbStreamSectionMapElement {
  uint16_t id; /* 0x10d, 0x109, 0x10b, 0x208, 0x413 */
  uint16_t unknown1; /* for 0x413 ends here */
  uint16_t unknown2;
  uint16_t unknown3;
  uint32_t unknown4; /* mostly -1 */
  uint32_t unknown5;
  uint32_t unknown6;  /* offset */
  /* Optional uint32_t unknown7; if id == 0x208 */
} sPdbStreamSectionMapElement;

#define DBG_PDB_SYMBOLV2_MAGIC	0xffffffffU

typedef struct sPdbSymbolRangeV1
{
  uint16_t segment;
  uint16_t pad1;
  uint32_t offset;
  uint32_t size;
  uint32_t characteristics;
  uint16_t index;
  uint16_t pad2;
} sPdbSymbolRangeV1;

typedef struct sPdbSymbolFileV1
{
  uint32_t unknown1;
  sPdbSymbolRangeV1 range;
  uint16_t flag;
  uint16_t file;
  uint32_t symbol_size;
  uint32_t lineno_size;
  uint32_t unknown2;
  uint32_t nSrcFiles;
  uint32_t attribute;
  char filename[1];
} sPdbSymbolFileV1;

typedef struct sPdbSymbolRangeV2
{
  uint16_t segment;
  uint16_t pad1;
  uint32_t offset;
  uint32_t size;
  uint32_t characteristics;
  uint16_t index;
  uint16_t pad2;
  uint32_t timestamp;
  uint32_t unknown;
} sPdbSymbolRangeV2;

typedef struct sPdbSymbolFileV2
{
  uint32_t unknown1;
  sPdbSymbolRangeV2 range;
  uint16_t flag;
  uint16_t file;
  uint32_t symbol_size;
  uint32_t lineno_size;
  uint32_t unknown2;
  uint32_t nSrcFiles;
  uint32_t attribute;
  uint32_t reserved[2];
  char filename[1];
} sPdbSymbolFileV2;

#pragma pack(pop)

typedef struct sPdbSymbolFile
{
  int version;
  __extension__ union {
    sPdbSymbolFileV1 *v1;
    sPdbSymbolFileV2 *v2;
  };
  char *name[2];
  sDbgMemFile *(*dump)(struct sPdbSymbolFile *,sDbgMemFile *);
} sPdbSymbolFile;

typedef struct sPdbSymbolSrcModules {
  size_t hash_size;
  size_t symbol_size;
  uint16_t *hash_off;
  uint16_t *hash_len;
  uint32_t *str_off;
  size_t strs_size;
  char *strs;
} sPdbSymbolSrcModules;


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
  sPdbSymbolFile **sym_files;
  size_t sym_files_count;
  sPdbSectionInfo *sym_section_info;
  sDbgMemFile *module_stream;
  sDbgMemFile *sectioninfo_stream;
  sDbgMemFile *sectionmap_stream;
  sDbgMemFile *srcmodule_stream;
  sPdbSymbolSrcModules *srcmodules;
  sDbgMemFile *pdbimport_stream;
  sDbgMemFile *unknown1_stream;
  sDbgMemFile *unknown2_stream;
  sDbgMemFile *unknown3_stream;
  sDbgCV *gsyms;
} sPdbSymbols;

sPdbSymbols *dbg_symbols_load (sDbgMemFile *f, sDbgInterfacePDB *base, int stream_idx);
void dbg_symbol_release (sPdbSymbols *s);

/*
Dump of 'Symbol unknown2 stream':
0x00000000: FE EF FE EF 01 00 00 00 52 0C 00 00 00 72 75 6E - ........R....run
0x00000010: 74 69 6D 65 2D 70 0B 00 20 00 00 00 23 91 00 00 - time-p.. ...#...

0x00000000: FE EF FE EF 01 00 00 00 01 00 00 00 00 01 00 00
0x00000010: 00 00 00 00 00 00 00 00 BC F4 00 00 23 00 00 00
uint32_t signature; // 0xeffeeffe
uint32_t version; // always 1
uint32_t unk_size; // 0xc52, 1,
char [12];
uint32_t unk2_size; // 0x20, 0xf4bc
uint32_t unk3_size; // 0x9123, 0x23
*/
#endif
