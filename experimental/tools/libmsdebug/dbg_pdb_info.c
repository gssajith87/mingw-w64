#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_pdb_info.h"

sPdbInfo *
dbg_readPdbInfo (const sDbgMemFile *f)
{
  const sPdbStreamInfo *sinfo;
  sPdbInfo *ret = NULL;
  if (!f || f->size < sizeof (sPdbStreamInfo))
    return NULL;
  sinfo = (const sPdbStreamInfo *) f->data;
  ret = (sPdbInfo *) malloc (sizeof (sPdbInfo) + f->size - sizeof (sPdbStreamInfo));
  ret->name = &((char *) f->data)[sizeof (sPdbStreamInfo)];
  ret->unknown = (uint32_t *) (ret->name + sinfo->cb_name);
  ret->version = sinfo->version;
  ret->timestamp = sinfo->timestamp;
  ret->age = sinfo->age;
  memcpy (ret->guid, sinfo->guid, 16);
  ret->cb_name = sinfo->cb_name;
  memcpy (ret->name, (const char *) &sinfo[1], sinfo->cb_name);
  ret->c_unknown = (f->size - sizeof (sPdbStreamInfo) - sinfo->cb_name) / sizeof (uint32_t);
  memcpy (ret->unknown, ((const char *) &sinfo[1])+ sinfo->cb_name, (f->size - sizeof (sPdbStreamInfo) - sinfo->cb_name));
  return ret;
}

int dbg_writePdbInfo (sDbgMemFile *f, size_t off, const sPdbInfo *info)
{
  if (!f)
    return -1;
  if (!info)
    return 0;
  dbg_memfile_write (f, off, (unsigned char *) &info->version, sizeof (uint32_t)); off += sizeof (uint32_t);
  dbg_memfile_write (f, off, (unsigned char *) &info->timestamp, sizeof (uint32_t)); off += sizeof (uint32_t);
  dbg_memfile_write (f, off, (unsigned char *) &info->age, sizeof (uint32_t)); off += sizeof (uint32_t);
  dbg_memfile_write (f, off, (unsigned char *) info->guid, 16); off += 16;
  dbg_memfile_write (f, off, (unsigned char *) &info->cb_name, sizeof (uint32_t)); off += sizeof (uint32_t);
  dbg_memfile_write (f, off, (unsigned char *) info->name, info->cb_name); off += info->cb_name;
  dbg_memfile_write (f, off, (unsigned char *) info->unknown, info->c_unknown * sizeof (uint32_t));
  return 0;
}

int dbg_dumpPdbInfo (sDbgMemFile *t, const sPdbInfo *info)
{
  uint32_t i;
  dbg_memfile_printf (t, "Info Stream:\n"
    "  Version: %u, TimeStamp: 0x%08x, Age: %u, name[%u] = \"", info->version, info->timestamp, info->age, info->cb_name);
  for (i=0;i<info->cb_name;i++)
  {
    if (info->name[i] < 0x20)
      dbg_memfile_printf (t, "\\%o", info->name[i]);
    else if (info->name[i] == '"' || info->name[i]=='\\')
      dbg_memfile_printf (t, "\\%c", info->name[i]);
    else
      dbg_memfile_printf (t, "%c", info->name[i]);
  }
  dbg_memfile_printf (t, "\"\n  unknown[%u] = {", info->c_unknown);
  for (i=0;i<info->c_unknown;i++)
  {
    dbg_memfile_printf (t, "%s0x%x",(i==0 ? "" : ", "), info->unknown[i]);
  }
  dbg_memfile_printf (t, "}\n");
  return 0;
}
