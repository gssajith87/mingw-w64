#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_interface_pdb.h"
#include "dbg_pdb.h"
#include "dbg_pdb_symbols.h"

/* Prototypes.  */
static sPdbRoot2 *pdb2Root (sPdbHeader2 *pph, uint32_t *pStreams, uint32_t *pStreamBytes, int *pfUnused);
static sPdbRoot7 *pdb7Root (sPdbHeader7 *pph, uint32_t *pStreams, uint32_t *pStreamBytes, int *pfUnused);
static void *pdb2FileRead (sPdbHeader2 *pph, uint32_t streamBytes, void *pages, int *pfUnused);
static void *pdb7FileRead (sPdbHeader7 *pph, uint32_t streamBytes, void *pages, int *pfUnused);
static uint32_t pdb2FilePages (sPdbHeader2 *pph, uint32_t streamBytes, uint32_t *pPageBytes, int *pfUnused);
static uint32_t pdb7FilePages (sPdbHeader7 *pph, uint32_t streamBytes, uint32_t *pPageBytes, int *pfUnused);
static int pdb2FileUnused (sPdbHeader2 *pph, uint32_t streamBytes, uint32_t *pPageBytes);
static int pdb7FileUnused (sPdbHeader7 *pph, uint32_t streamBytes, uint32_t *pPageBytes);

/* Interface functions.  */
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
  NULL, sizeof (sDbgInterfacePDB),
  pdb2_probe, /* probe */
  pdb2_load,
  pdb2_update,
  pdb2_release,
  pdb2_dump,
  pdb2_search,
  pdb2_dump_symbol
};

sDbgInterface interface_pdb7 = {
  eInterface_pdb7, "PDB Version 7.0",
  NULL, sizeof (sDbgInterfacePDB),
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
        {
          const sPdbHeader2 *hdr = (const sPdbHeader2 *) pDFile->data;
          if (((size_t)hdr->filePages * (size_t)hdr->pageBytes) == pDFile->size)
            return 0;
        }
    }
  return -1;
}

static int pdb2_load (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t streams, streamBytes;
  int fUnused = 0;
  sPdbHeader2 *hdr = (sPdbHeader2 *) pDCtx->memfile->data;
  sPdbRoot2 *root;
  root = pdb2Root (hdr, &streams, &streamBytes, &fUnused);
  if (root)
    {
      sDbgMemFile **h = (sDbgMemFile **) malloc (sizeof (sDbgMemFile *) * ((size_t) root->nstreams));
      uint32_t i, pageidx = 0;
      uint32_t off, dStreamBytes;
      diPDB->files_kind = (const char **) malloc (sizeof (const char *) * root->nstreams);
      if (!h || diPDB->files_kind == NULL)
	{
	  if (h)
	    free (h);
	  if (diPDB->files_kind)
	    free (diPDB->files_kind);
	  diPDB->files_kind = NULL;
	  free (root);
	  return -1;
	}
      memset (diPDB->files_kind, 0, sizeof (char *) * (size_t) root->nstreams);
      memset (h, 0, sizeof (sDbgMemFile *) * ((size_t) root->nstreams));
      diPDB->files_kind[0] = "root stream";
      diPDB->files_kind[1] = "info stream";
      for (i = 0; i < root->nstreams; i++)
	{
	  void *pdata;
	  fUnused = 0;
	  dStreamBytes = root->streams[i].streamBytes;
	  off = sizeof (sPdbRoot2) + ((uint32_t) root->streams) * sizeof(sPdbStream2) + (pageidx * sizeof (uint16_t));
	  pdata = pdb2FileRead (hdr, dStreamBytes, ((unsigned char*) root) + off, &fUnused);
	  if (!fUnused)
	    {
	      sDbgMemFile *dmf = dbg_memfile_create ("stream", dStreamBytes);
	      h[i] = dmf;
	      dbg_memfile_write (dmf, 0, pdata, dStreamBytes);
	    }
	  if (pdata)
	    free (pdata);
	  pageidx += pdb2FilePages (hdr, dStreamBytes, NULL, NULL);
	}
      diPDB->streams = root->nstreams;
      diPDB->files = h;
      fprintf (stderr, " # of streams: %u\n", root->nstreams);
      free (root);
    }
  if (diPDB->files && diPDB->streams > 2)
    {
      diPDB->syms = (sPdbSymbols *) dbg_symbols_load (diPDB->files[3], diPDB, 3);
    }
  return 0;
}

static int pdb2_update (sDbgInterface *pDCtx)
{
  return unknown_update (pDCtx);
}

static int
pdb2_release (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t i;
  uint32_t streams = ((sDbgInterfacePDB *)pDCtx)->streams;
  sDbgMemFile **h = ((sDbgInterfacePDB *)pDCtx)->files;

  if (diPDB->syms)
    {
      dbg_symbol_release ((sPdbSymbols *)diPDB->syms);
      diPDB->syms = NULL;
    }
  diPDB->files = NULL;
  diPDB->streams = 0;
  for (i = 0; i < streams; i++)
    dbg_memfile_release (h[i]);
  if (diPDB->files_kind)
    free (diPDB->files_kind);
  diPDB->files_kind = NULL;
  if (h)
    free (h);
  return unknown_release (pDCtx);
}

static sDbgMemFile *pdb2_dump (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t i;
  uint32_t streams = diPDB->streams;
  sDbgMemFile **h = diPDB->files;
  sDbgMemFile *ret = dbg_memfile_create_text ("pdb2_dump");
  if (h[1])
    {
      sPdbInfo *pi = dbg_readPdbInfo (h[1]);
      if (pi)
      {
	dbg_dumpPdbInfo (ret, pi);
	free (pi);
      }
    }
  if (diPDB->syms)
    {
      (diPDB->syms->dump) (diPDB->syms, ret);
    }
  for (i = 1; i < streams; i++)
    {
      if (diPDB->files_kind && diPDB->files_kind[i] != NULL)
        {
          dbg_memfile_printf (ret, "Stream: %u with size %u of kind %s,\n", i, h[i]->size, diPDB->files_kind[i]);
          continue;
        }
      if (h[i])
	{
	  dbg_memfile_printf (ret, "Stream: %u with size %u\n", i, h[i]->size);
	  //dbg_memfile_dump_in (ret, h[i]);
	}
    }

  return ret;
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
        {
          const sPdbHeader7 *hdr = (const sPdbHeader7 *) pDFile->data;
          if (((size_t)hdr->filePages * (size_t)hdr->pageBytes) == pDFile->size)
            return 0;
        }
    }
  return -1;
}

static int pdb7_load (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t streams, streamBytes;
  int fUnused = 0;
  sPdbHeader7 *hdr = (sPdbHeader7 *) pDCtx->memfile->data;
  sPdbRoot7 *root = pdb7Root (hdr, &streams, &streamBytes, &fUnused);
  if (root)
    {
      sDbgMemFile **h = (sDbgMemFile **) malloc (sizeof (sDbgMemFile *) * ((size_t) root->nstreams));
      uint32_t i, pageidx = 0;
      uint32_t off, dStreamBytes;
      diPDB->files_kind = (const char **) malloc (sizeof (const char *) * (size_t) root->nstreams);
      if (!h || diPDB->files_kind == NULL)
	{
	  if (h)
	    free (h);
	  if (diPDB->files_kind)
	    free (diPDB->files_kind);
	  diPDB->files_kind = NULL;
	  free (root);
	  return -1;
	}
      memset (diPDB->files_kind, 0, sizeof (char *) * (size_t) root->nstreams);
      memset (h, 0, sizeof (sDbgMemFile *) * ((size_t) root->nstreams));
      diPDB->files_kind[0] = "root stream";
      diPDB->files_kind[1] = "info stream";
      for (i = 0; i < root->nstreams; i++)
	{
	  void *pdata;
	  fUnused = 0;
	  dStreamBytes = root->streamBytes [i];
	  off = sizeof (sPdbRoot7) + ((uint32_t) root->nstreams) * sizeof(uint32_t) + (pageidx * sizeof (uint32_t));
	  pdata = pdb7FileRead (hdr, dStreamBytes, ((unsigned char*) root) + off, &fUnused);
	  if (!fUnused)
	    {
	      sDbgMemFile *dmf = dbg_memfile_create ("stream", dStreamBytes);
	      h[i] = dmf;
	      dbg_memfile_write (dmf, 0, pdata, dStreamBytes);
	    }
	  if (pdata)
	    free (pdata);
	  pageidx += pdb7FilePages (hdr, dStreamBytes, NULL, NULL);
	}
      diPDB->streams = root->nstreams;
      diPDB->files = h;
      fprintf (stderr, " # of streams: %u\n", root->nstreams);
      free (root);
    }
  if (diPDB->files && diPDB->streams > 2)
    {
      diPDB->syms = dbg_symbols_load (diPDB->files[3], diPDB, 3);
    }
  return unknown_load (pDCtx);
}

static int pdb7_update (sDbgInterface *pDCtx)
{

  return unknown_update (pDCtx);
}

static int
pdb7_release (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t i;
  uint32_t streams = ((sDbgInterfacePDB *)pDCtx)->streams;
  sDbgMemFile **h = ((sDbgInterfacePDB *)pDCtx)->files;

  if (diPDB->syms)
    {
      dbg_symbol_release (diPDB->syms);
      diPDB->syms = NULL;
    }
  diPDB->files = NULL;
  diPDB->streams = 0;
  for (i = 0; i < streams; i++)
    dbg_memfile_release (h[i]);
  if (diPDB->files_kind)
    free (diPDB->files_kind);
  diPDB->files_kind = NULL;
  if (h)
    free (h);
  return unknown_release (pDCtx);
}

static sDbgMemFile *pdb7_dump (sDbgInterface *pDCtx)
{
  sDbgInterfacePDB *diPDB = (sDbgInterfacePDB *) pDCtx;
  uint32_t i;
  uint32_t streams = diPDB->streams;
  sDbgMemFile **h = diPDB->files;
  sDbgMemFile *ret = dbg_memfile_create_text ("pdb7_dump");
  if (h[1])
    {
      sPdbInfo *pi = dbg_readPdbInfo (h[1]);
      if (pi)
      {
	dbg_dumpPdbInfo (ret, pi);
	free (pi);
      }
    }
  if (diPDB->syms)
    {
      (* diPDB->syms->dump) (diPDB->syms, ret);
    }
  for (i = 0; i < streams; i++)
    {
      if (diPDB->files_kind && diPDB->files_kind[i] != NULL)
        {
          dbg_memfile_printf (ret, "Stream: %u with size %u of kind %s.\n", i, h[i]->size, diPDB->files_kind[i]);
          continue;
        }
      if (h[i])
	{
	  dbg_memfile_printf (ret, "Stream: %u with size %u\n", i, h[i]->size);
	  //dbg_memfile_dump_in (ret, h[i]);
	}
    }

  return ret;
}

static sSymbolInterface *pdb7_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match)
{
  return unknown_search (pDCtx, match);
}

static sDbgMemFile *pdb7_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym)
{
  return unknown_dump_symbol (pDCtx, pSym);
}

/* Static helper functions.  */

static sPdbRoot2 *pdb2Root (sPdbHeader2 *pph, uint32_t *pStreams, uint32_t *pStreamBytes, int *pfUnused)
{
  uint32_t indexBytes;
  void *pPages = NULL;
  uint32_t streams = 0;
  uint32_t streamBytes = 0;
  int fUnused = 0;
  sPdbRoot2 *ppr = NULL;

  streamBytes = pph->rootStream.streamBytes;
  pPages = pph->rootPages;

  if ((ppr = pdb2FileRead (pph, streamBytes, pPages, &fUnused)) != NULL)
    streams = ppr->nstreams;
  if (ppr == NULL)
    streamBytes = 0;
  *pStreams = streams;
  *pStreamBytes = streamBytes;
  *pfUnused = fUnused;
  return ppr;
}

static sPdbRoot7 *pdb7Root (sPdbHeader7 *pph, uint32_t *pStreams, uint32_t *pStreamBytes, int *pfUnused)
{
  uint32_t indexBytes;
  void *pPages = NULL;
  uint32_t streams = 0;
  uint32_t streamBytes = 0;
  int fUnused = 0;
  sPdbRoot7 *ppr = NULL;

  streamBytes = pph->rootBytes;
  pPages = pph->indexPages;

  indexBytes = pdb7FilePages (pph, streamBytes, NULL, NULL) * sizeof (uint32_t);

  if ((pPages = pdb7FileRead (pph, indexBytes,  pPages, &fUnused)) != NULL)
    {
      if ((ppr = pdb7FileRead (pph, streamBytes, pPages, &fUnused)) != NULL)
        streams = ppr->nstreams;
      free (pPages);
    }
  if (ppr == NULL)
  streamBytes = 0;
  if (pStreams != NULL)
    *pStreams = streams;
  if (pStreamBytes != NULL)
    *pStreamBytes = streamBytes;
  if (pfUnused != NULL)
    *pfUnused = fUnused;
  return ppr;
}

static void *
pdb2FileRead (sPdbHeader2 *pph, uint32_t streamBytes, void *pages, int *pfUnused)
{
  uint32_t pageBytes, dPages, i, j, n;
  int fUnused = 0;
  void *stream = NULL;

  if (pages != NULL)
    {
      dPages = pdb2FilePages (pph, streamBytes, &pageBytes, &fUnused);
      if (pageBytes)
        stream = malloc (streamBytes);
      if (stream != NULL)
	{
          n = streamBytes;
	  for (i = 0; i < dPages; i++)
	    {
	      j = ((uint16_t *) pages)[i];
	      memcpy ( &((unsigned char*)stream)[i * pageBytes], &((unsigned char *)pph)[j * pageBytes], (n < pageBytes ? n : pageBytes));
	      n -= pageBytes;
	    }
	}
    }
  if (pfUnused != NULL)
    *pfUnused = fUnused;
  return stream;
}

static void *pdb7FileRead (sPdbHeader7 *pph, uint32_t streamBytes, void *pages, int *pfUnused)
{
  uint32_t pageBytes, dPages, i, j, n;
  int fUnused = 0;
  void *stream = NULL;

  if (pages != NULL)
    {
      dPages = pdb7FilePages (pph, streamBytes, &pageBytes, &fUnused);
      n = streamBytes;
      if (pageBytes)
        stream = malloc (n);
      if (stream != NULL)
	{
	  for (i = 0; i < dPages; i++)
	    {
	      j = ((uint32_t *) pages)[i];
	      memcpy (((unsigned char *) stream) + i * pageBytes, ((unsigned char *) pph) + j * pageBytes, (n < pageBytes ? n : pageBytes));
	      n -= pageBytes;
	    }
	}
    }
  if (pfUnused != NULL)
    *pfUnused = fUnused;
  return stream;
}

static uint32_t pdb2FilePages (sPdbHeader2 *pph, uint32_t streamBytes, uint32_t *pPageBytes, int *pfUnused)
{
  uint32_t pageBytes = 0;
  int fUnused = pdb2FileUnused (pph, streamBytes, &pageBytes);
  *pPageBytes = pageBytes;
  *pfUnused = fUnused;

  return (pageBytes && streamBytes ? ((streamBytes - 1) / pageBytes) + 1 : 0);
}

static uint32_t pdb7FilePages (sPdbHeader7 *pph, uint32_t streamBytes, uint32_t *pPageBytes, int *pfUnused)
{
  uint32_t pageBytes = 0;
  int fUnused = pdb7FileUnused (pph, streamBytes, &pageBytes);

  if (pPageBytes != NULL)
    *pPageBytes = pageBytes;
  if (pfUnused != NULL)
    *pfUnused = fUnused;

  return (pageBytes && streamBytes ? ((streamBytes - 1) / pageBytes) + 1 : 0);
}

static int pdb2FileUnused (sPdbHeader2 *pph, uint32_t streamBytes, uint32_t *pPageBytes)
{
  if (streamBytes != PDB_UNUSED_16)
    {
      *pPageBytes = pph->pageBytes;
      return 0;
    }
  *pPageBytes = 0;
  return 1;
}

static int pdb7FileUnused (sPdbHeader7 *pph, uint32_t streamBytes, uint32_t *pPageBytes)
{
  if (streamBytes != PDB_UNUSED_32)
    {
      *pPageBytes = pph->pageBytes;
      return 0;
    }
  *pPageBytes = 0;
  return 1;
}
