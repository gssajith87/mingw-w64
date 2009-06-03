#ifndef _DBG_INTERFACE_HXX
#define _DBG_INTERFACE_HXX

#include "dbg_memfile.h"

typedef enum eInterfaceType
{
  eInterface_error = -1,
  eInterface_unknown = 0,
  eInterface_pdb2 = 1,
  eInterface_pdb7 = 2,
  eInterface_max
} eInterfaceType;

typedef struct sSymbolInterface
{
  int kind;
  size_t elems;
  unsigned char **data;
} sSymbolInterface;

typedef struct sSymbolSearchInterface
{
  int kind;
  size_t size;
  unsigned char *data;
} sSymbolSearchInterface;

typedef struct sDbgInterface
{
  eInterfaceType file_type;
  const char *file_type_name;
  sDbgMemFile *memfile;
  size_t cb_size;
  int (*probe)(const sDbgMemFile *);
  int (*load)(struct sDbgInterface *pDCtx);
  int (*update)(struct sDbgInterface *pDCtx);
  int (*release)(struct sDbgInterface *pDCtx);
  sDbgMemFile *(*dump)(struct sDbgInterface *pDCtx);
  sSymbolInterface *(*search)(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match);
  sDbgMemFile *(*dump_symbol)(struct sDbgInterface *pDCtx, sSymbolInterface *pSym);
} sDbgInterface;

eInterfaceType probe_file (const char *filename);
sDbgInterface *open_file (const char *filename);

#endif
