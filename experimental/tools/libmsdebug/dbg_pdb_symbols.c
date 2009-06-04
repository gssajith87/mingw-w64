#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include "dbg_pdb_symbols.h"

static int dbg_symbols_probe (sDbgMemFile *f);
static int sym_release (sPdbSymbols *s);
static int sym1_probe (const sDbgMemFile *f);
static int sym2_probe (const sDbgMemFile *f);
static int sym1_load (sPdbSymbols *s);
static int sym2_load (sPdbSymbols *s);
static int sym1_update (sPdbSymbols *s);
static int sym2_update (sPdbSymbols *s);
static sDbgMemFile *sym_dump(sPdbSymbols *s, sDbgMemFile *t);

static const sPdbSymbols locSymbolV1 = {
  ePdbSymbols_v1,
  "Symbols Stream V1",
  sizeof (sPdbSymbols),
  NULL,
  sym1_probe,
  sym1_load,
  sym1_update,
  sym_release,
  sym_dump,
};

static const sPdbSymbols locSymbolV2 = {
  ePdbSymbols_v2,
  "Symbols Stream V2",
  sizeof (sPdbSymbols),
  NULL,
  sym2_probe,
  sym2_load,
  sym2_update,
  sym_release,
  sym_dump,
};

static const sPdbSymbols * locSymbols[2] = {
  &locSymbolV1, &locSymbolV2
};

static int sym1_update (sPdbSymbols *s)
{
  if (!s)
    return -1;
  return 0;
}

static int sym2_update (sPdbSymbols *s)
{
  if (!s)
    return -1;
  return 0;
}

static sDbgMemFile *sym_dump(sPdbSymbols *s, sDbgMemFile *t)
{
  sDbgMemFile *ret = t;
  if (!ret)
    ret = dbg_memfile_create_text (s ? s->kind_name : "empty-symbols");
  if (!s)
    {
      dbg_memfile_printf (ret, "Empty symbol stream.\n");
      return ret;
    }
  switch (s->kind)
    {
    case ePdbSymbols_v1:
      {
        sPdbStreamSymbolsV1 *sy1 = (sPdbStreamSymbolsV1 *) s->memfile->data;
        dbg_memfile_printf (ret,
          "Symbols Version 1 (Stream #%u)\n"
          "file(s): Hash1=%x, Hash2=%x, GlobalSyms:%x\n"
          "size(s): Module=%u, Offsets=%u, Hash=%u, SrcModule=%u\n",
          s->stream_idx, sy1->hash1_file, sy1->hash2_file, sy1->gsym_file,
          sy1->module_size, sy1->offset_size, sy1->hash_size, sy1->srcmodule_size);
      }
      break;
    case ePdbSymbols_v2:
      {
        sPdbStreamSymbolsV2 *sy1 = (sPdbStreamSymbolsV2 *) s->memfile->data;
        dbg_memfile_printf (ret,
          "Symbols Version %u (ext=0x%x) (Stream #%u)\n"
          "file(s): Hash1=%x, Hash2=%x, GlobalSyms:%x\n"
          "size(s): Module=%u, Offsets=%u, Hash=%u, SrcModule=%u, Imports=%u\n"
          "         Unk1=%u, Unk2=%u, Unk3=%u\n"
          "reserved[2]={0x%x,0x%x}\n",
          sy1->version, sy1->extended_format, s->stream_idx,
          sy1->hash1_file, sy1->hash2_file, sy1->gsym_file,
          sy1->module_size, sy1->offset_size, sy1->hash_size, sy1->srcmodule_size,
          sy1->pdbimport_size, sy1->unknown1_size, sy1->unknown2_size, sy1->unknown3_size,
          sy1->resvd[0],sy1->resvd[1]);
      }
      break;
    default:
       dbg_memfile_printf (ret, "Unknown symbol stream\n");
       break;
    }
  return ret;
}

static int sym2_load (sPdbSymbols *s)
{
  if (!s)
    return -1;
  return 0;
}

static int sym1_load (sPdbSymbols *s)
{
  if (!s)
    return -1;
/*  uint16_t hash1_file;
  uint16_t hash2_file;
  uint16_t gsym_file;
  uint16_t pad;
  uint32_t module_size;
  uint32_t offset_size;
  uint32_t hash_size;
  uint32_t srcmodule_size; */
  
  return 0;
}

static int sym2_probe (const sDbgMemFile *f)
{
  const sPdbStreamSymbolsV2 *sym;
  size_t len = sizeof (sPdbStreamSymbolsV2);
  if (!f || f->size < len)
    return -1;
  sym = (const sPdbStreamSymbolsV2 *) f->data;
  if (sym->signature != DBG_PDB_SYMBOLV2_MAGIC)
    return -1;
  len += (size_t) sym->module_size;
  len += (size_t) sym->offset_size;
  len += (size_t) sym->hash_size;
  len += (size_t) sym->srcmodule_size;
  len += (size_t) sym->pdbimport_size;
  len += (size_t) sym->unknown1_size;
  len += (size_t) sym->unknown2_size;
  len += (size_t) sym->unknown3_size;
  if (f->size < len)
    {
      fprintf (stderr," Probe Symbols ... expected len 0x%x != calculated 0x%x\n", (uint32_t) f->size, (uint32_t) len);
      return -1;
    }
  if (f->size > len)
    fprintf (stderr, "Probe Symbols ... data at end of V2 0x%x\n", (uint32_t) (f->size - len));
  return 0;
}

static int sym1_probe (const sDbgMemFile *f)
{
  const sPdbStreamSymbolsV1 *sym;
  size_t len = sizeof (sPdbStreamSymbolsV1);
  if (!f || f->size < len)
    return -1;
  sym = (const sPdbStreamSymbolsV1 *) f->data;
  len += (size_t) sym->module_size;
  len += (size_t) sym->offset_size;
  len += (size_t) sym->hash_size;
  len += (size_t) sym->srcmodule_size;
  if (f->size != len)
    {
      fprintf (stderr," Probe Symbols ... expected len 0x%x != calculated 0x%x\n", (uint32_t) f->size, (uint32_t) len);
      return -1;
    }
  return 0;
}

static int sym_release (sPdbSymbols *s)
{
  return 0;
}

void dbg_symbol_release (sPdbSymbols *s)
{
  if (!s)
    return;
  if (s->release)
    (* s->release) (s);
  if (s->memfile)
    dbg_memfile_release (s->memfile);
  free (s);
}

sPdbSymbols *dbg_symbols_load (sDbgMemFile *f, sDbgInterfacePDB *base, int stream_idx)
{
  sPdbSymbols *ret = NULL;
  int t = dbg_symbols_probe (f);
  if (!f || t == -1)
    return ret;
  ret = (sPdbSymbols *) malloc (locSymbols[t]->cb_size);
  if (!ret)
    return ret;
  memcpy (ret, locSymbols[t], locSymbols[t]->cb_size);
  ret->memfile = f;
  ret->stream_idx = stream_idx;
  ret->base = base;
  if (ret->load && (* ret->load) (ret) != 0)
    {
      free (ret);
      return NULL;
    }
  dbg_memfile_retain (f);
  return ret;
}

static int dbg_symbols_probe (sDbgMemFile *f)
{
  int i;
  if (!f)
    return -1;
  for (i = ePdbSymbols_max - 1; i >= 0 ; i--)
    {
      if (locSymbols[i]->probe && (* locSymbols[i]->probe)(f) == 0)
         return locSymbols[i]->kind;
    }
  return -1;
}

