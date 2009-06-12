#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_memfile.h"
#include "dbg_interface_pdb.h"
#include "dbg_pdb_types.h"

static int st_type1_probe(const struct sDbgMemFile *);
static int st_type1_load(struct sPdbTypes *);
static int st_type1_update(struct sPdbTypes *);
static int st_type1_release(struct sPdbTypes *);
static sDbgMemFile *st_type1_dump(struct sPdbTypes *s, sDbgMemFile *t);

static sPdbTypes stTypes1 = {
  0, "type information",
  sizeof (sPdbTypes),
  NULL,
  st_type1_probe,
  st_type1_load,
  st_type1_update,
  st_type1_release,
  st_type1_dump,
};

static int st_type1_probe(const struct sDbgMemFile *f)
{
  sDbgPdbTypeHeader *hdr;
  if (!f || f->size < sizeof (sDbgPdbTypeHeader))
    return -1;
  hdr = (sDbgPdbTypeHeader *) f->data;
  if (f->size < (size_t) (hdr->cbHdr))
    return -1;
  if (f->size < (size_t) (hdr->cbHdr + hdr->cbGprec))
    return -1;
  return 0;
}

static int st_type1_load(struct sPdbTypes *f)
{
  sDbgPdbTypeHeader *hdr;
  if (st_type1_probe (f->memfile) != 0)
    return -1;
  hdr = (sDbgPdbTypeHeader *) f->memfile->data;
  f->version = hdr->version;
  f->tiMin = hdr->tiMin;
  f->tiMac = hdr->tiMac;
  if (DbgInterfacePDB_streams(f->base) > hdr->tpiHash.sn)
    {
      DbgInterfacePDB_file_kind (f->base,hdr->tpiHash.sn) = "Type information hash stream";
      f->hash = DbgInterfacePDB_file(f->base,hdr->tpiHash.sn);
      dbg_memfile_retain (f->hash);
    }
  memcpy (&f->tpiHash, &hdr->tpiHash, sizeof (sDbgPdbTypeHash));
  if (hdr->cbGprec != 0)
    {
      f->Gprec = dbg_memfile_create ("GP records", hdr->cbGprec);
      dbg_memfile_write (f->Gprec, 0, & f->memfile->data[hdr->cbHdr], hdr->cbGprec);
      f->types = dbg_CV_create (f->Gprec->data, f->Gprec->size, 0);
      if (f->types != NULL)
        {
          dbg_memfile_release (f->Gprec);
          f->Gprec = NULL;
        }
    }
  return 0;
}

static int st_type1_update(struct sPdbTypes *f)
{
  if (!f)
    return -1;
  return 0;
}

static int st_type1_release(struct sPdbTypes *f)
{
  if (f->hash)
    dbg_memfile_release (f->hash);
  if (f->Gprec)
    dbg_memfile_release (f->Gprec);
  if (f->types)
    {
      dbg_CV_release (f->types);
      f->types = NULL;
    }
  return 0;  
}

static sDbgMemFile *st_type1_dump(struct sPdbTypes *s, sDbgMemFile *t)
{
  sDbgMemFile *ret = (t ? t : dbg_memfile_create_text ("type-information"));

  dbg_memfile_printf (ret, "Type information Version %u\n"
    "  TypeIndexMin = %u, TypeIndexMac=%u\n", s->version, s->tiMin, s->tiMac);
  dbg_memfile_printf (ret,
    "  sn=%u, snPad=%u, cbHashKey=%u, cHashBuckets=%u\n"
    "  hashVals=%u[%u], TiOff=%u[%u], HashAdj=%u[%u]\n",
    s->tpiHash.sn, s->tpiHash.snPad, s->tpiHash.cbHashKey, s->tpiHash.cHashBuckets,
    s->tpiHash.offcbHashVals.off, s->tpiHash.offcbHashVals.cb,
    s->tpiHash.offcbTiOff.off, s->tpiHash.offcbTiOff.cb,
    s->tpiHash.offcbHashAdj.off, s->tpiHash.offcbHashAdj.cb);
  if (s->hash)
    dbg_memfile_dump_in (ret, s->hash);
  if (s->Gprec)
    dbg_memfile_dump_in (ret, s->Gprec);
  if (s->types)
    dbg_CV_dump (s->types, ret);
  return ret;
}

sPdbTypes *dbg_pdb_types_create (sDbgMemFile *d, struct sDbgInterfacePDB *base)
{
  sPdbTypes *ret;
  if (!d || st_type1_probe (d) != 0)
    return NULL;
  ret = (sPdbTypes *) malloc (sizeof (sPdbTypes));
  memcpy (ret, &stTypes1, sizeof (sPdbTypes));
  ret->base = base;
  ret->memfile = d;
  if (ret->load)
    (* ret->load)(ret);
  return ret;
}

void dbg_pdb_types_release (sPdbTypes *p)
{
  if (!p)
    return;
  if (p->release)
    (* p->release) (p);
  free (p);
}

sDbgMemFile *dbg_pdb_types_dump (sPdbTypes *p, sDbgMemFile *t)
{
  if (!p)
    return t;
  if (p->dump)
    t = (* p->dump) (p, t);
  return t;
}
