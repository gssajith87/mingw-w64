#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include "dbg_pdb_symbols.h"

static int dbg_symbols_probe (sDbgMemFile *f);
static size_t sym_files_count (unsigned char *ptr, uint32_t size, uint32_t ext);
static size_t sym_files_getelemsize (unsigned char *ptr, uint32_t size, uint32_t ext);
static sPdbSymbolFile *sym_file_new (unsigned char *ptr, uint32_t ext, sPdbSymbols *s);
static size_t sym_sectioninfo_count (unsigned char *dptr, size_t max_size);
static uint32_t sym_sectioninfo_version (unsigned char *dptr, size_t max_size);
static sPdbSectionInfo *sym_sectioninfo_read (unsigned char *dptr, size_t max_size, size_t cnt);

static sDbgMemFile *sym_file_dump (sPdbSymbolFile *sf,sDbgMemFile *t);

static int sym_release (sPdbSymbols *s);
static int sym1_probe (const sDbgMemFile *f);
static int sym2_probe (const sDbgMemFile *f);
static int sym1_load (sPdbSymbols *s);
static int sym2_load (sPdbSymbols *s);
static int sym1_update (sPdbSymbols *s);
static int sym2_update (sPdbSymbols *s);
static sDbgMemFile *sym_dump (sPdbSymbols *s, sDbgMemFile *t);

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

static sDbgMemFile *sym_dump (sPdbSymbols *s, sDbgMemFile *t)
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
          "  file(s): Hash1=%x, Hash2=%x, GlobalSyms:%x\n"
          "  size(s): Module=%u, SectionInfo=%u, SectionMap=%u, SrcModule=%u\n",
          s->stream_idx, sy1->hash1_file, sy1->hash2_file, sy1->gsym_file,
          sy1->module_size, sy1->sectioninfo_size, sy1->sectionmap_size, sy1->srcmodule_size);
      }
      break;
    case ePdbSymbols_v2:
      {
        sPdbStreamSymbolsV2 *sy1 = (sPdbStreamSymbolsV2 *) s->memfile->data;
        dbg_memfile_printf (ret,
          "Symbols Version %u (ext=0x%x) (Stream #%u)\n"
          "  file(s): Hash1=%u, Version DLL> 0x%04x, Hash2=%u Version DLL-Build 0x%04x, GlobalSyms:%u (0x%x)\n"
          "  size(s): Module=%u, SectionInfo=%u, SectionMap=%u, SrcModule=%u, Imports=%u\n"
          "           Unk1=%u, Unk2=%u, Unk3=%u\n"
          "  flag: 0x%x, MachineID:0x%x, reserved[1]={0x%x}\n",
          sy1->version, sy1->extended_format, s->stream_idx,
          sy1->hash1_file, sy1->verPdbDLL,
          sy1->hash2_file, sy1->verPdbDLLBuild,
          sy1->gsym_file, sy1->gsym_unknown,
          sy1->module_size, sy1->sectioninfo_size, sy1->sectionmap_size, sy1->srcmodule_size,
          sy1->pdbimport_size, sy1->unknown1_size, sy1->unknown2_size, sy1->unknown3_size,
          sy1->flags, sy1->machine,
          sy1->resvd[0]);
      }
      break;
    default:
       dbg_memfile_printf (ret, "Unknown symbol stream\n");
       break;
    }
  if (s->sym_files)
    {
      size_t i;
      dbg_memfile_printf (ret, "   Contains %u symbol_file(s)\n", (uint32_t) s->sym_files_count);
      for (i = 0; i < s->sym_files_count; i++)
        {
          if (s->sym_files[i])
            (* s->sym_files[i]->dump) (s->sym_files[i], ret);
        }
    }
  if (s->sectioninfo_stream)
    dbg_memfile_dump_in (ret, s->sectioninfo_stream);
  if (s->sectionmap_stream)
    dbg_memfile_dump_in (ret, s->sectionmap_stream);
  if (s->srcmodule_stream)
    {
      uint16_t *hdr = (uint16_t *) s->srcmodule_stream->data;
      uint16_t *tab1,*tab2;
      uint32_t *tab3;
      char *strs, *start = (char *) s->srcmodule_stream->data;
      size_t check = s->srcmodule_stream->size;
      size_t text_size;

      do {
        size_t len1, len2;
        if (check < 4)
          break;
        check -= 4;
        tab1 = &hdr[2];
        len1 = (size_t) hdr[0] * sizeof(uint16_t);
        len2 = (size_t) hdr[1] * sizeof(uint32_t);
        if (check < (len1 * 2))
          break;
        tab2 = &tab1[hdr[0]];
        tab3 = (uint32_t *) &tab2[hdr[0]];
        check -= len1 * 2;
        if (check < len2)
          break;
        check -= len2;
        strs = (char *) &tab3[hdr[1]];
        text_size = check;
        check = 0;
      } while (0);
      if (check)
        dbg_memfile_dump_in (ret, s->srcmodule_stream);
      else
        {
          uint16_t i;
          dbg_memfile_printf (ret, "Source Module dump:\n"
            "  uint16_t tab1[%u] = {\n", hdr[0]);
          for (i = 0; i < hdr[0];)
            {
              uint16_t k;
              dbg_memfile_printf (ret, "    ");
              for (k=0;k<8 && i < hdr[0]; k++, i++)
                {
                  dbg_memfile_printf (ret, "%u,", tab1[i]);
                }
              dbg_memfile_printf (ret, "\n");
            }
          dbg_memfile_printf (ret, "  };\n  uint16_t tab2[%u] = {\n", hdr[0]);
          for (i = 0; i < hdr[0];)
            {
              uint16_t k;
              dbg_memfile_printf (ret, "    ");
              for (k=0;k<8 && i < hdr[0]; k++, i++)
                {
                  dbg_memfile_printf (ret, "%u,", tab2[i]);
                }
              dbg_memfile_printf (ret, "\n");
            }
          dbg_memfile_printf (ret, "  };\n  uint32_t tab3[%u] = { /* Offsets in string table */ \n", hdr[1]);
          for (i = 0; i < hdr[1];)
            {
              uint16_t k;
              dbg_memfile_printf (ret, "    ");
              for (k=0;k<16 && i < hdr[1]; k++, i++)
                {
                  dbg_memfile_printf (ret, "0x%x,", tab3[i]);
                }
              dbg_memfile_printf (ret, "\n");
            }
          dbg_memfile_printf (ret, "  };\n  const char *strs[] = {\n");
          i = 0;
          start = strs;
          while (text_size > 0)
            {
              size_t len = strlen (strs) + 1;
	      dbg_memfile_printf (ret, "  /* 0x%x */ \"%s\", /* %u */\n",
                (uint32_t) ((size_t) (strs - start)), strs, i++);
              if (text_size < len)
                break;
              text_size -= len;
              strs += len;
            }
              
          dbg_memfile_printf (ret, "  };\n");
        }
    }
  if (s->pdbimport_stream)
    dbg_memfile_dump_in (ret, s->pdbimport_stream);
  if (s->unknown1_stream)
    dbg_memfile_dump_in (ret, s->unknown1_stream);
  if (s->unknown2_stream)
    dbg_memfile_dump_in (ret, s->unknown2_stream);
  if (s->unknown3_stream)
    dbg_memfile_dump_in (ret, s->unknown3_stream);
  return ret;
}

static int sym2_load (sPdbSymbols *s)
{
  const sPdbStreamSymbolsV2 *sym;
  unsigned char *dptr;
  if (!s)
    return -1;
  sym = (sPdbStreamSymbolsV2 *) s->memfile->data;
  dptr = & s->memfile->data[sizeof (sPdbStreamSymbolsV2)];
  if (DbgInterfacePDB_streams (s->base) > sym->gsym_file)
    DbgInterfacePDB_file_kind (s->base, sym->gsym_file) = "Global Symbol stream";
  if (DbgInterfacePDB_streams (s->base) > sym->hash1_file)
    DbgInterfacePDB_file_kind (s->base, sym->hash1_file) = "Hash1 stream";
  if (DbgInterfacePDB_streams (s->base) > sym->hash2_file)
    DbgInterfacePDB_file_kind (s->base, sym->hash2_file) = "Hash2 stream";
  if (sym->module_size != 0)
    {
      size_t cnt;
      sPdbSymbolFile **h;

      s->module_stream = dbg_memfile_create ("Section info stream", sym->module_size);
      dbg_memfile_write (s->module_stream, 0, dptr, sym->module_size);

      cnt = sym_files_count (dptr, sym->module_size, sym->extended_format);
      h = (sPdbSymbolFile **) malloc (sizeof (sPdbSymbolFile *) * cnt);
      if (h)
        {
          unsigned char *d = dptr;
          size_t i;
          for (i = 0;i < cnt; i++)
            {
              h[i] = sym_file_new (d, sym->extended_format, s);
              d += ((sym_files_getelemsize (d, 0xffff, sym->extended_format) + 3) & ~3);
            }
          s->sym_files = h;
          s->sym_files_count = cnt;
        }
      dbg_memfile_release (s->module_stream);
      s->module_stream = NULL;
      dptr += sym->module_size;
    }
  if (sym->sectioninfo_size != 0)
    {
      size_t cnt;
      s->sectioninfo_stream = dbg_memfile_create ("Section info stream", sym->sectioninfo_size);
      dbg_memfile_write (s->sectioninfo_stream, 0, dptr, sym->sectioninfo_size);

      cnt = sym_sectioninfo_count (dptr, sym->sectioninfo_size);
      if (cnt != 0xffffffff)
        {
          fprintf (stderr, "Found %u section info element(s)\n", (uint32_t) cnt);
          s->sym_section_info = sym_sectioninfo_read (dptr, sym->sectioninfo_size, cnt);
          if (s->sym_section_info)
            {
              dbg_memfile_release (s->sectioninfo_stream);
              s->sectioninfo_stream = NULL;
            }
        }
      dptr += sym->sectioninfo_size;
    }
  if (sym->sectionmap_size != 0)
    {
      s->sectionmap_stream = dbg_memfile_create ("Symbol section map stream", sym->sectionmap_size);
      dbg_memfile_write (s->sectionmap_stream, 0, dptr, sym->sectionmap_size);
      dptr += sym->sectionmap_size;
    }
  if (sym->srcmodule_size != 0)
    {
      s->srcmodule_stream = dbg_memfile_create ("Symbol source module stream", sym->srcmodule_size);
      dbg_memfile_write (s->srcmodule_stream, 0, dptr, sym->srcmodule_size);
      dptr += sym->srcmodule_size;
    }
  if (sym->pdbimport_size != 0)
    {
      s->pdbimport_stream = dbg_memfile_create ("Symbol PDB import stream", sym->pdbimport_size);
      dbg_memfile_write (s->pdbimport_stream, 0, dptr, sym->pdbimport_size);
      dptr += sym->pdbimport_size;
    }
  if (sym->unknown1_size != 0)
    {
      s->unknown1_stream = dbg_memfile_create ("Symbol unknown1 stream", sym->unknown1_size);
      dbg_memfile_write (s->unknown1_stream, 0, dptr, sym->unknown1_size);
      dptr += sym->unknown1_size;
    }
  if (sym->unknown2_size != 0)
    {
      s->unknown2_stream = dbg_memfile_create ("Symbol unknown2 stream", sym->unknown2_size);
      dbg_memfile_write (s->unknown2_stream, 0, dptr, sym->unknown2_size);
      dptr += sym->unknown2_size;
    }
  if (sym->unknown3_size != 0)
    {
      s->unknown3_stream = dbg_memfile_create ("Symbol unknown3 stream", sym->unknown3_size);
      dbg_memfile_write (s->unknown3_stream, 0, dptr, sym->unknown3_size);
      dptr += sym->unknown3_size;
    }
  return 0;
}

static int sym1_load (sPdbSymbols *s)
{
  const sPdbStreamSymbolsV1 *sym;
  unsigned char *dptr;

  if (!s)
    return -1;
  sym = (sPdbStreamSymbolsV1 *) s->memfile->data;
  dptr = & s->memfile->data[sizeof (sPdbStreamSymbolsV1)];
  if (DbgInterfacePDB_streams (s->base) > sym->gsym_file)
    DbgInterfacePDB_file_kind (s->base, sym->gsym_file) = "Global Symbol stream";
  if (DbgInterfacePDB_streams (s->base) > sym->hash1_file)
    DbgInterfacePDB_file_kind (s->base, sym->hash1_file) = "Hash1 stream";
  if (DbgInterfacePDB_streams (s->base) > sym->hash2_file)
    DbgInterfacePDB_file_kind (s->base, sym->hash2_file) = "Hash2 stream";
  if (sym->module_size != 0)
    {
      size_t cnt = sym_files_count (dptr, sym->module_size, 0);
      sPdbSymbolFile **h = (sPdbSymbolFile **) malloc (sizeof (sPdbSymbolFile *) * cnt);
      if (h)
        {
          unsigned char *d = dptr;
          size_t i;
          for (i = 0;i < cnt; i++)
            {
              h[i] = sym_file_new (d, 0, s);
              d += ((sym_files_getelemsize (d, 0xffff, 0) + 3) & ~3);
            }
          s->sym_files = h;
          s->sym_files_count = cnt;
        }
      dptr += sym->module_size;
    }
  if (sym->sectioninfo_size != 0)
    {
      size_t cnt;
      s->sectioninfo_stream = dbg_memfile_create ("Section info stream", sym->sectioninfo_size);
      dbg_memfile_write (s->sectioninfo_stream, 0, dptr, sym->sectioninfo_size);

      cnt = sym_sectioninfo_count (dptr, sym->sectioninfo_size);
      if (cnt != 0xffffffff)
        {
          fprintf (stderr, "Found %u section info element(s)\n", (uint32_t) cnt);
          s->sym_section_info = sym_sectioninfo_read (dptr, sym->sectioninfo_size, cnt);
          if (s->sym_section_info)
            {
              dbg_memfile_release (s->sectioninfo_stream);
              s->sectioninfo_stream = NULL;
            }
        }
      dptr += sym->sectioninfo_size;
    }
  if (sym->sectionmap_size != 0)
    {
      s->sectionmap_stream = dbg_memfile_create ("Symbol section map stream", sym->sectionmap_size);
      dbg_memfile_write (s->sectionmap_stream, 0, dptr, sym->sectionmap_size);
      dptr += sym->sectionmap_size;
    }
  if (sym->srcmodule_size != 0)
    {
      s->srcmodule_stream = dbg_memfile_create ("Symbol hash stream", sym->srcmodule_size);
      dbg_memfile_write (s->srcmodule_stream, 0, dptr, sym->srcmodule_size);
      dptr += sym->srcmodule_size;
    }
  
  return 0;
}

static sDbgMemFile *sym_file_dump (sPdbSymbolFile *sf,sDbgMemFile *t)
{
  sDbgMemFile *ret = t;
  if (t == NULL)
    ret = dbg_memfile_create_text ("sym_file_dump");
  if (!sf)
    {
      dbg_memfile_printf (ret, "Invalid symbol\n");
      return ret;
    }
  if (sf->version == 1)
    {
      dbg_memfile_printf (ret,
        "SymbolV1: Unknown1=%x, Addr:0x%04x:0x%08x [0x%x]\n"
        "   Characteristics: 0x%x index:%u\n"
        "  flags:%x, file:%u [symbol_size:0x%x lineno_size:0x%x]\n"
        "  unknown2:%x, # of src files:%u, attribute:0x%x\n"
        "  name[0]='%s'\n"
        "  name[1]='%s'\n", 
        sf->v1->unknown1,
        sf->v1->range.segment,sf->v1->range.offset,sf->v1->range.size,
        sf->v1->range.characteristics,sf->v1->range.index,
        sf->v1->flag, sf->v1->file, sf->v1->symbol_size, sf->v1->lineno_size,
        sf->v1->unknown2,sf->v1->nSrcFiles,sf->v1->attribute,
        sf->name[0],sf->name[1]);
    }
  else if (sf->version == 2)
    {
      dbg_memfile_printf (ret,
        "SymbolV2: Unknown1=%x, Addr:0x%04x:0x%08x [0x%x]\n"
        "   Characteristics: 0x%x index:%u TimeStamp:0x%x, Unknown:0x%x\n"
        "  flags:%x, file:%u [symbol_size:0x%x lineno_size:0x%x]\n"
        "  unknown2:%x, # of src files:%u, attribute:0x%x [0x%x:0x%x]\n"
        "  name[0]='%s'\n"
        "  name[1]='%s'\n", 
        sf->v2->unknown1,
        sf->v2->range.segment,sf->v1->range.offset,sf->v2->range.size,
        sf->v2->range.characteristics,sf->v2->range.index,
        sf->v2->range.timestamp, sf->v2->range.unknown,
        sf->v2->flag, sf->v2->file, sf->v2->symbol_size, sf->v2->lineno_size,
        sf->v2->unknown2,sf->v2->nSrcFiles,sf->v2->attribute,
        sf->v2->reserved[0], sf->v2->reserved[1],
        sf->name[0],sf->name[1]);
    }
  else
    dbg_memfile_printf (ret, "Unknown sym_file version:%u\n", sf->version);
  return ret;
}

static sPdbSymbolFile *sym_file_new (unsigned char *ptr, uint32_t ext, sPdbSymbols *s)
{
  size_t name_off, len;
  sPdbSymbolFile *ret;
  len = sym_files_getelemsize (ptr, 0xffff, ext);

  ret = (sPdbSymbolFile *) malloc (sizeof (sPdbSymbolFile) + len);
  memset (ret, 0, sizeof (sPdbSymbolFile));
  ret->dump = sym_file_dump;
  if (ext)
    {
      sPdbSymbolFileV2 *psf = (sPdbSymbolFileV2 *) ptr;
      name_off = sizeof (sPdbSymbolFileV2) - 1;
      if (psf->unknown1 == 1) name_off -= 4;
      
      ret->version = 2;
      if (DbgInterfacePDB_streams (s->base) > psf->file)
        DbgInterfacePDB_file_kind (s->base, psf->file) = "Symbol/Lineno stream";
    }
  else
    {
      sPdbSymbolFileV1 *psf = (sPdbSymbolFileV1 *) ptr;
      name_off = sizeof (sPdbSymbolFileV1) - 1;
      if (psf->unknown1 == 1) name_off -= 4;
      if (DbgInterfacePDB_streams (s->base) > psf->file)
        DbgInterfacePDB_file_kind (s->base, psf->file) = "Symbol/Lineno stream";

      ret->version = 1;
    }
  ret->v2 = (sPdbSymbolFileV2 *) &((unsigned char *)ret)[sizeof (sPdbSymbolFile)];
  memcpy (ret->v2, ptr, len);
  ret->name[0] = &((char*) ret->v2)[name_off];
  name_off += strlen (ret->name[0]) + 1;
  ret->name[1] = &((char*) ret->v2)[name_off];
  return ret;
}

static size_t sym_files_getelemsize (unsigned char *ptr, uint32_t size, uint32_t ext)
{
  size_t len;

  if (size < 4)
    return 0;
  if (!ext)
    {
      sPdbSymbolFileV1 *v1 = (sPdbSymbolFileV1 *) ptr;
      len = sizeof (sPdbSymbolFileV1) - 1;
      if (v1->unknown1 == 1) len -= 4;
    }
  else
    {
      sPdbSymbolFileV2 *v1 = (sPdbSymbolFileV2 *) ptr;
      len = sizeof (sPdbSymbolFileV2) - 1;
      if (v1->unknown1 == 1) len -= 4;
    }
  if ((len + 2) > size)
    return 0;
  len += strlen ((char *) &ptr[len]) + 1;
  len += strlen ((char *) &ptr[len]) + 1;
  if (len > size)
    return 0;
  return len;
}

static size_t sym_files_count (unsigned char *ptr, uint32_t size, uint32_t ext)
{
  size_t ret = 0;
  unsigned char *pd = ptr + size;
 
  if (!ptr || !size)
    return 0;
  while (ptr < pd)
    {
      size_t len = sym_files_getelemsize (ptr, size, ext);

      ret += 1;
      len = (len + 3) & ~3;
      ptr += len;
      size -= len;
    }
  return ret;
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
  len += (size_t) sym->sectioninfo_size;
  len += (size_t) sym->sectionmap_size;
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
  len += (size_t) sym->sectioninfo_size;
  len += (size_t) sym->sectionmap_size;
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
  size_t i;
  if (!s)
    return 0;
  if (s->sym_files)
    {
      for (i = 0;i < s->sym_files_count; i++)
	{
	  if (s->sym_files[i] != NULL)
	    free (s->sym_files[i]);
	  s->sym_files[i] = NULL;
	}
      free (s->sym_files);
    }
  if (s->sym_section_info)
    {
      free (s->sym_section_info);
      s->sym_section_info = NULL;
    }
  s->sym_files = NULL;
  s->sym_files_count = 0;

  dbg_memfile_release (s->module_stream);
  dbg_memfile_release (s->sectioninfo_stream);
  dbg_memfile_release (s->sectionmap_stream);
  dbg_memfile_release (s->srcmodule_stream);
  dbg_memfile_release (s->pdbimport_stream);
  dbg_memfile_release (s->unknown1_stream);
  dbg_memfile_release (s->unknown2_stream);
  dbg_memfile_release (s->unknown3_stream);
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

static uint32_t sym_sectioninfo_version (unsigned char *dptr, size_t max_size)
{
  uint32_t version;
  if (max_size < 4)
    return 0;
  version = *((uint32_t *)dptr);
  max_size -= 4;
  switch (version)
    {
    case DBG_PDB_STREAM_VERSION_V2:
      if ((max_size % sizeof (sPdbStreamSectionInfoV2)) == 0)
        return 2;
      fprintf (stderr,"SectionInfo Version %u != V2\n", version);
      break;
    default:
      break;
    }
  max_size -= 4;
  if ((max_size % sizeof (sPdbStreamSectionInfoV1)) != 0 && (max_size % sizeof (sPdbStreamSectionInfoV2)) == 0)
    {
      fprintf (stderr, "SectionInfo V2 with new version ident %u\n", version);
      return 2;
    }
  if ((max_size % sizeof (sPdbStreamSectionInfoV1)) == 0)
    return 1;
  fprintf (stderr, "SectionInfo V? with version ident %u\n", version);
  return 3;
}

static size_t sym_sectioninfo_count (unsigned char *dptr, size_t max_size)
{
  switch (sym_sectioninfo_version (dptr, max_size))
    {
      case 0:
        return 0xffffffff;
      case 1:
        max_size -= 4;
        return (max_size / sizeof (sPdbStreamSectionInfoV1));
      case 2:
        max_size -= 4;
        return (max_size / sizeof (sPdbStreamSectionInfoV2));
    }
  return 0xffffffff;
}

static sPdbSectionInfo *sym_sectioninfo_read (unsigned char *dptr, size_t max_size, size_t cnt)
{
  sPdbSectionInfo *ret;
  sPdbStreamSectionInfoV1 *v1;
  sPdbStreamSectionInfoV2 *v2;
  size_t i;

  ret = (sPdbSectionInfo *) malloc (sizeof (sPdbSectionInfo) + cnt * sizeof (sPdbSectionInfoElement));
  if (!ret)
    return NULL;
  ret->version = sym_sectioninfo_version (dptr, max_size);
  ret->count = cnt;
  ret->signature = *((uint32_t *) dptr);
  dptr += 4;
  v1 = (sPdbStreamSectionInfoV1 *) dptr;
  v2 = (sPdbStreamSectionInfoV2 *) dptr;

  for (i = 0; i < cnt; i++)
    {
      if (ret->version == 1)
        {
          memcpy (&ret->elm[i], &v1[i], sizeof (sPdbStreamSectionInfoV1));
          ret->elm[i].dataCRC = 0;
          ret->elm[i].relocCRC = 0;
        }
      else
        {
          memcpy (&ret->elm[i], &v2[i], sizeof (sPdbStreamSectionInfoV2));
        }
    }
  return ret;
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
  DbgInterfacePDB_file_kind (base, stream_idx) = "symbols stream";
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

