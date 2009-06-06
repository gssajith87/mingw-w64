#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include "dbg_codeview.h"

typedef struct sDbgCVCommon {
  uint16_t dSize;
  uint16_t leaf;
  unsigned char data[1];
} sDbgCVCommon;

static sDbgMemFile *cv_default_dump (sDbgCVtag *cv, sDbgMemFile *x);
static int cv_default_update (sDbgCVtag *cv, sDbgMemFile *to);
static int cv_fill (sDbgCVtag *cv, sDbgCVCommon *cm);
static size_t dbg_CVtag_getsize (unsigned char *dta, size_t max);

sDbgCV *dbg_CV_create (unsigned char *dta, size_t max)
{
  unsigned char *d = dta;
  size_t max2 = max, count = 0;
  sDbgCVtag *e;
  sDbgCV *ret = NULL;
  while (max2 > 0)
    {
      size_t l = dbg_CVtag_getsize (d, max2);
      d += l;
      max2 -= l;
      if (!l)
      {
	fprintf (stderr, "*** CV create: %u %u\n", (uint32_t) max2, (uint32_t) l);
	exit(0);
	return NULL;
      }
      count++;
    }
  fprintf (stderr, "*** types: %u, remains:%u\n", (uint32_t) count, (uint32_t) max2);
  if (max2 != 0)
    return NULL;
  ret = (sDbgCV *) malloc (sizeof (sDbgCV));
  if (!ret)
    return NULL;
  ret->tag = (sDbgCVtag **) malloc (sizeof (sDbgCVtag *) * count);
  if (ret->tag == NULL)
    {
      free (ret);
      return NULL;
    }
  ret->count = count;
  for (count = 0; count < ret->count; count++)
    {
      size_t l = dbg_CVtag_getsize (dta, max);
      ret->tag[count] = dbg_CVtag_create (dta, max);
      dta += l;
      max -= l;
    }
  return ret;
}

void dbg_CV_release (sDbgCV *cv)
{
  size_t i;
  if (!cv)
    return;
  for (i = 0; i < cv->count; i++)
    {
      if (cv->tag[i] != NULL)
	dbg_CVtag_release (cv->tag[i]);
    }
  if (cv->tag)
    free (cv->tag);
  free (cv);
}

sDbgMemFile *dbg_CV_dump (sDbgCV *cv, sDbgMemFile *x)
{
  sDbgMemFile *ret = x;
  size_t i;
  if (!cv)
    return ret;
  for (i = 0; i < cv->count; i++)
    {
      if (cv->tag[i] != NULL)
	ret = dbg_CVtag_dump (cv->tag[i], ret);
    }
  return ret;
}

int dbg_CV_update (sDbgCV *cv, sDbgMemFile *f)
{
  size_t i;
  int ret = 0;
  if (!cv || !f)
    return -1;
  for (i = 0; i < cv->count; i++)
    {
      if (cv->tag[i] != NULL)
	ret |= dbg_CVtag_update (cv->tag[i], f);
    }
  return ret;
}

static size_t dbg_CVtag_getsize (unsigned char *dta, size_t max)
{
  size_t ret;
  uint16_t *sh = (uint16_t *) dta;
  if (max < 2)
    return 0;
  ret = (size_t) sh[0];
  ret += 2;
  if (max < ret)
    return 0;
  return ret;
}

sDbgCVtag *dbg_CVtag_create (unsigned char *dta, size_t max)
{
  size_t tagSize;
  sDbgCVtag *ret = NULL;
  sDbgCVCommon *cv = (sDbgCVCommon *) dta;
  tagSize = 0;
  if (max < sizeof (uint16_t))
    return NULL;
  if (max < ((size_t) cv->dSize + 2))
    return NULL;
  tagSize = (size_t) cv->dSize;
  tagSize += 2;
  ret = (sDbgCVtag *) malloc (sizeof (sDbgCVtag));
  if (!ret)
    return NULL;
  memset (ret, 0, sizeof (sDbgCVtag));
  ret->dump = cv_default_dump;
  ret->update = cv_default_update;
  ret->leaf = (uint32_t) cv->leaf;
  if (cv_fill (ret, cv) == -1)
    {
      ret->unknown_leaf = dbg_memfile_create ("cv_unknown", tagSize);
      dbg_memfile_write (ret->unknown_leaf, 0, dta, tagSize);
    }
  return ret;
}

sDbgMemFile *dbg_CVtag_dump (sDbgCVtag *cv,sDbgMemFile *x)
{
  sDbgMemFile *ret = x;
  if (!ret) ret = dbg_memfile_create_text ("CV tag");
  if (cv->dump)
    ret = (* cv->dump)(cv, ret);
  else
    dbg_memfile_printf (ret, "CVtag %p has no dump method!!!\n", cv);
  return ret;
}

int dbg_CVtag_update(sDbgCVtag *cv, sDbgMemFile *f)
{
  if (!cv)
    return 0;
  if (cv->update)
    return (* cv->update) (cv, f);
  return -1;
}

static sDbgMemFile *cv_default_dump (sDbgCVtag *cv, sDbgMemFile *x)
{
  sDbgMemFile *ret = x;
  if (!ret) ret = dbg_memfile_create_text ("CV tag");
  if (!cv)
    return ret;
  if (cv->unknown_leaf)
    dbg_memfile_dump_in (ret, cv->unknown_leaf);
  return ret;
}

static int cv_default_update (sDbgCVtag *cv, sDbgMemFile *to)
{
  if (!cv || !to || cv->unknown_leaf == NULL)
    return -1;
  return dbg_memfile_write (to, to->size, cv->unknown_leaf->data, cv->unknown_leaf->size);
}

static int cv_fill (sDbgCVtag *cv, sDbgCVCommon *cm)
{
  uint32_t *dw = (uint32_t *) cm->data;
  if (!cm)
    return -1;
  switch (cm->leaf)
    {
    case LF_MODIFIER:
      break;
    default:
      break;
    }
  return -1;
}

void dbg_CVtag_release (sDbgCVtag *cv)
{
  if (!cv)
    return;
  if (cv->unknown_leaf)
    dbg_memfile_release (cv->unknown_leaf);
  free (cv);
}
