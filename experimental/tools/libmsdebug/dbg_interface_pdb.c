#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_interface_pdb.h"

static int pdb2_probe(const sDbgMemFile *pDFile);
static int pdb2_load (sDbgInterface *pDCtx);
static int pdb2_update (sDbgInterface *pDCtx);
static int pdb2_release (sDbgInterface *pDCtx);
static sDbgMemFile *pdb2_dump (sDbgInterface *pDCtx);
static sSymbolInterface *pdb2_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match);
static sDbgMemFile *pdb2_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym);

static int pdb7_probe(const sDbgMemFile *pDFile);
static int pdb7_load (sDbgInterface *pDCtx);
static int pdb7_update (sDbgInterface *pDCtx);
static int pdb7_release (sDbgInterface *pDCtx);
static sDbgMemFile *pdb7_dump (sDbgInterface *pDCtx);
static sSymbolInterface *pdb7_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match);
static sDbgMemFile *pdb7_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym);

sDbgInterface interface_pdb2 = {
  eInterface_pdb2, "PDB Version 2.0",
  NULL, sizeof (sDbgInterfacePDB2),
  pdb2_probe, /* probe */
  pdb2_load,
  pdb2_update,
  pdb2_release,
  pdb2_dump,
  pdb2_search,
  pdb2_dump_symbol
};

sDbgInterface interface_pdb7 = {
  eInterface_pdb2, "PDB Version 7.0",
  NULL, sizeof (sDbgInterfacePDB7),
  pdb7_probe, /* probe */
  pdb7_load,
  pdb7_update,
  pdb7_release,
  pdb7_dump,
  pdb7_search,
  pdb7_dump_symbol
};

static int pdb2_probe(const sDbgMemFile *pDFile)
{
  if (pDFile && pDFile->size >= 0x40)
    {
      if (!memcmp (pDFile->data, "Microsoft C/C++ program database 2.00\r\n\032JG\0", 0x2c))
        return 0;
    }
  return -1;
}

static int pdb2_load (sDbgInterface *pDCtx)
{
  return unknown_load (pDCtx);
}

static int pdb2_update (sDbgInterface *pDCtx)
{
  return unknown_update (pDCtx);
}

static int pdb2_release (sDbgInterface *pDCtx)
{
  return unknown_release (pDCtx);
}

static sDbgMemFile *pdb2_dump (sDbgInterface *pDCtx)
{
  return unknown_dump (pDCtx);
}

static sSymbolInterface *pdb2_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match)
{
  return unknown_search (pDCtx, match);
}

static sDbgMemFile *pdb2_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym)
{
  return unknown_dump_symbol (pDCtx, pSym);
}

static int pdb7_probe(const sDbgMemFile *pDFile)
{
  if (pDFile && pDFile->size >= 0x40)
    {
      if (!memcmp (pDFile->data, "Microsoft C/C++ MSF 7.00\r\n\032DS\0\0", 0x20))
        return 0;
    }
  return -1;
}

static int pdb7_load (sDbgInterface *pDCtx)
{
  return unknown_load (pDCtx);
}

static int pdb7_update (sDbgInterface *pDCtx)
{
  return unknown_update (pDCtx);
}

static int pdb7_release (sDbgInterface *pDCtx)
{
  return unknown_release (pDCtx);
}

static sDbgMemFile *pdb7_dump (sDbgInterface *pDCtx)
{
  return unknown_dump (pDCtx);
}

static sSymbolInterface *pdb7_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match)
{
  return unknown_search (pDCtx, match);
}

static sDbgMemFile *pdb7_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym)
{
  return unknown_dump_symbol (pDCtx, pSym);
}
