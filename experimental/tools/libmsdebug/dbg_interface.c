#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_interface.h"
#include "dbg_interface_pdb.h"

static eInterfaceType probe_file1 (sDbgMemFile *pDFile);

static const sDbgInterface interface_unknown = {
  eInterface_unknown, "binary file",
  NULL, sizeof (sDbgInterface),
  unknown_probe, /* probe */
  unknown_load,
  unknown_update,
  unknown_release,
  unknown_dump,
  unknown_search,
  unknown_dump_symbol
};

static const sDbgInterface *dbg_interfaces[eInterface_max] = {
  &interface_unknown,
  &interface_pdb2, /* pdb 2.0 */
  &interface_pdb7, /* pdb 7.0 */
};

eInterfaceType
dbg_probe_file (const char *filename)
{
  sDbgMemFile *pDFile = dbg_memfile_open (filename);
  eInterfaceType ret;

  ret = probe_file1 (pDFile);
  dbg_memfile_release (pDFile);

  return ret;
}

static eInterfaceType
probe_file1 (sDbgMemFile *pDFile)
{
  int i;
  if (!pDFile)
    return eInterface_error;
  for (i = 1; i < (int) eInterface_max; i++)
    {
      if (dbg_interfaces[i] != NULL && (*dbg_interfaces[i]->probe)(pDFile) == 0)
           return dbg_interfaces[i]->file_type;
    }
  return eInterface_unknown;
}

/* Unknown file support.  */
int
unknown_probe (const sDbgMemFile *pDFile __attribute__ ((unused)) )
{
  return 0;
}

int
unknown_load (sDbgInterface *pDCtx)
{
  if (pDCtx && pDCtx->memfile)
    return 0;
  return -1;
}

int
unknown_release (sDbgInterface *pDCtx)
{
  if (!pDCtx)
    return -1;
  return 0;
}

int
unknown_update (sDbgInterface *pDCtx)
{
  if (!pDCtx)
    return -1;
  return 0;
}

sDbgMemFile *
unknown_dump (sDbgInterface *pDCtx)
{
  sDbgMemFile *ret;
  if (!pDCtx || pDCtx->memfile == NULL)
    return NULL;
  fprintf (stderr," File type ,%s':\n", pDCtx->file_type_name);
  ret = dbg_memfile_dump (pDCtx->memfile);
  return ret;
}

sSymbolInterface *
unknown_search(struct sDbgInterface *pDCtx, sSymbolSearchInterface *match)
{
  if (!pDCtx || !match)
    return NULL;
  return NULL;
}

sDbgMemFile *
unknown_dump_symbol(struct sDbgInterface *pDCtx, sSymbolInterface *pSym)
{
  if (!pDCtx || !pSym)
    return NULL;
  return NULL;
}

/* Public accessors.  */
sDbgInterface *
dbg_open_file (const char *filename)
{
  sDbgInterface *ret;
  const sDbgInterface *pInter = NULL;
  sDbgMemFile *pDFile = dbg_memfile_open (filename);
  eInterfaceType t;

  if (!pDFile)
    return NULL;

  t = probe_file1 (pDFile);
  pInter = dbg_interfaces[t];
  if (!pInter)
    {
      dbg_memfile_release (pDFile);
      return NULL;
    }
  ret = (sDbgInterface *) malloc (pInter->cb_size);
  if (!ret)
    {
      dbg_memfile_release (pDFile);
      return NULL;
    }
  memset (ret, 0, pInter->cb_size);
  memcpy (ret, pInter, sizeof (sDbgInterface));
  ret->memfile = pDFile;
  if (ret->load)
    (* ret->load)(ret);
  return ret;
}

int 
dbg_release_interface (sDbgInterface *pDCtx)
{
  int ret = 0;
  if (!pDCtx)
    return 0;
  if (pDCtx->release)
    ret = (* pDCtx->release) (pDCtx);
  if (pDCtx->memfile)
    dbg_memfile_release (pDCtx->memfile);
  free (pDCtx);
  return 0;
  
}

int main (int argc,char **argv)
{
  sDbgInterface *in;
  
  if (argc <= 1)
    return;
  in = dbg_open_file (argv[1]);
  if (!in)
    printf ("Can't open ,%s'\n", argv[1]);
  else
    {
      sDbgMemFile *h = (* in->dump)(in);
      if (h) printf ("%s\n", h->data);
      dbg_memfile_release (h);
      dbg_release_interface (in);
    }
    
}
