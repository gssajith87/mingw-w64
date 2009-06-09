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
static sDbgMemFile *cv_dump_modifier (sDbgCVtag *cv, sDbgMemFile *x);
static sDbgMemFile *cv_dump_s_constant (sDbgCVtag *cv, sDbgMemFile *x);

static int cv_default_update (sDbgCVtag *cv, sDbgMemFile *to);
static int cv_update_dta (sDbgCVtag *cv, sDbgMemFile *to);
static int cv_fill (sDbgCVtag *cv, sDbgCVCommon *cm);
static size_t dbg_CVtag_getsize (unsigned char *dta, size_t max);

typedef struct sDbtTags {
  uint32_t tag;
  const char *tag_name;
  const char *fmt;
  const char **names;
} sDbgTags;

static const char *sz_procref[] = { "sumName", "ibSym", "iMod", "name", "pad" };
static const char *sz_pub32[] = { "Flags","Addr","name","pad" };
static const char *sz_gdata32[] = { "TypeIdx", "Addr", "name", "pad" };
static const char *sz_unknown[] = { "unknown" };

static sDbgTags stSYMs[] = {
  { DBG_CV_S_PROCREF, "S_PROCREF", "uuwsp", sz_procref },
  { DGB_CV_S_PUB32, "S_PUB32", "uAsp", sz_pub32 },
  { DBG_CV_S_GDATA32, "S_GDATA32", "uAsp", sz_gdata32 },
  { 0, "SYM_UNKNOWN", "x", sz_unknown }
};

static sDbgTags *find_tag_sym (uint32_t tag);
static sDbgMemFile *dump_tag_element_sym (uint32_t tag, unsigned char *dta, size_t len, sDbgMemFile *ret);
static size_t get_tag_element_size (unsigned char *dta, size_t off, size_t size, char fmt);
static size_t get_tag_element_off (unsigned char *dta, const char *fmt, int count, size_t size);
static sDbgTags *find_tag_sym (uint32_t tag);
static int get_tag_element_count (const sDbgTags *p);
static int get_tag_element_name_idx (const sDbgTags *p, const char *name);

static sDbgMemFile *dump_tag_element_sym (uint32_t tag, unsigned char *dta, size_t len, sDbgMemFile *x)
{
  sDbgTags *h = find_tag_sym (tag);
  sDbgMemFile *ret = (x ? x : dbg_memfile_create_text ("Sym tag"));
  if (h->tag == 0)
    {
      dbg_memfile_printf (ret, "  SymTag (0x%x):", tag);
      while (len > 0)
        {
	  dbg_memfile_printf (ret, " %02X", *dta);
	  dta++;
	  len--;
        }
      dbg_memfile_printf (ret, "\n");
    }
  else
    {
      const char *fmt = h->fmt;
      size_t l, doff = 0;
      int el = 0;
      dbg_memfile_printf (ret, "  SymTag %s:", h->tag_name);
      while(*fmt != 0)
        {
	  l = get_tag_element_size (dta, doff,len,*fmt);
	  switch (*fmt)
	  {
	  case 'w':
	    dbg_memfile_printf (ret, " %s:%u", h->names[el], *((uint16_t *) &dta[doff]));
	    break;
	  case 'u':
	    dbg_memfile_printf (ret, " %s:%u", h->names[el], *((uint32_t *) &dta[doff]));
	    break;
	  case 's':
	    dbg_memfile_printf (ret, " %s:\"%s\"", h->names[el], (char *) &dta[doff]);
	    break;
	  case 'A':
	    dbg_memfile_printf (ret, " %s:0x%x:0x%x", h->names[el], *((uint16_t *) &dta[doff + 4]), *((uint32_t *) &dta[doff]));
	    break;
	  case 'p':
	    if (!l) break;
	    dbg_memfile_printf (ret, " pad:");
	    {
	      size_t ll = 0;
	      for (ll =  0; ll < l; ll++)
		{
		  dbg_memfile_printf (ret, " %02x", dta[doff+ll]);
		}
	    }
	  }
	  fmt++;
	  el++;
	  doff += l;
        }
      dbg_memfile_printf (ret, "\n");
    }
  return ret;
}

static int get_tag_element_name_idx (const sDbgTags *p, const char *name)
{
  size_t nlen = strlen (name);
  size_t l = strlen (p->fmt);
  while (l>0)
  {
    --l;
    if (!strcmp (p->names[l], name))
      return (int) l;
  }
  return -1;
}

static int get_tag_element_count (const sDbgTags *p)
{
  return (int) strlen (p->fmt);
}

static size_t get_tag_element_off (unsigned char *dta, const char *fmt, int count, size_t size)
{
  size_t off = 0;
  size_t l = 0;
  if (!count)
    return off;
  do {
    off += l;
    l = get_tag_element_size (dta, off, size, *fmt);
    dta += l;
    size -= l;
    count--;
  } while (count != 0 && *fmt != 0);
  return off;
}

static size_t get_tag_element_size (unsigned char *dta, size_t off, size_t size, char fmt)
{
  switch (fmt)
  {
  case 'u': return sizeof (uint32_t);
  case 'w': return sizeof (uint16_t);
  case 's': return strlen ((char*) &dta[off]) + 1;
  case 'p': return size - off;
  case 'A': return sizeof (uint32_t) + sizeof (uint16_t);
  default:
    abort ();
  }
  return 0;
}

static sDbgTags *find_tag_sym (uint32_t tag)
{
  int i = 0;
  while (stSYMs[i].tag != 0 && stSYMs[i].tag != tag)
    i++;
  return &stSYMs[i];
}

sDbgCV *dbg_CV_create (unsigned char *dta, size_t max, int be_syms)
{
  unsigned char *d = dta;
  size_t max2 = max, count = 0;
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
      ret->tag[count] = dbg_CVtag_create (dta, max, be_syms);
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

sDbgCVtag *dbg_CVtag_create (unsigned char *dta, size_t max, int be_syms)
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
  ret->be_syms = be_syms;
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
  else
    {
      sDbgTags *dt = NULL;
      if (cv->be_syms)
	dt = find_tag_sym (cv->leaf);
  /*    else $$$$
	dt = find_tag_typ (cv->leaf); */
      if (dt && cv->be_syms)
	dump_tag_element_sym (cv->leaf, cv->dta, cv->length, ret);

    }
  return ret;
}

static int cv_update_dta (sDbgCVtag *cv, sDbgMemFile *to)
{
  uint16_t lw[2];
  if (!cv || !to || cv->unknown_leaf == NULL)
    return -1;
  lw[0] = (uint16_t) (cv->length + 2);
  lw[1] = (uint16_t) cv->leaf;
  dbg_memfile_write (to, to->size, (unsigned char *)lw, 4);
  return dbg_memfile_write (to, to->size, cv->dta, cv->length);
}

static int cv_default_update (sDbgCVtag *cv, sDbgMemFile *to)
{
  if (!cv || !to || cv->unknown_leaf == NULL)
    return -1;
  return dbg_memfile_write (to, to->size, cv->unknown_leaf->data, cv->unknown_leaf->size);
}

static sDbgMemFile *cv_dump_modifier (sDbgCVtag *cv, sDbgMemFile *x)
{
  sDbgMemFile *ret = x != NULL ? x : dbg_memfile_create_text ("cv_type");
  dbg_memfile_printf (ret, "  LF_MODIFIER: FollowUpType: 0x%x Flags:0x%x\n", cv->ui_dta[0], cv->ui_dta[1]);
  return ret;
}

static sDbgMemFile *cv_dump_s_constant (sDbgCVtag *cv, sDbgMemFile *x)
{
  sDbgMemFile *ret = x != NULL ? x : dbg_memfile_create_text ("cv_sym");
  dbg_memfile_printf (ret, "  S_CONSTANT: TypeIndex: %u, Value: 0x%x, \"%s\"\n",
    cv->s_constant->type_index, cv->s_constant->value,
    cv->s_constant->name);
  return ret;
}

static int cv_fill (sDbgCVtag *cv, sDbgCVCommon *cm)
{
  uint32_t *dw = (uint32_t *) cm->data;
  if (!cm)
    return -1;
  cv->length = cm->dSize - 2;
  if (cv->be_syms)
    {
      switch (cm->leaf)
	{
        case DBG_CV_S_CONSTANT: cv->dump = cv_dump_s_constant; break;
        case DGB_CV_S_PUB32: break;
	case DBG_CV_S_GDATA32:  break;
	case DBG_CV_S_PROCREF: break;
	default:
	  return -1;
        }
    }
  else
  {
    switch (cm->leaf)
      {
      case LF_MODIFIER: cv->dump = cv_dump_modifier;  break;
      default:
	return -1;
      }
  }
  cv->dta = (unsigned char *) malloc (cv->length + 1);
  if (!cv->dta)
    return -1;
  cv->update = cv_update_dta;
  memcpy (cv->dta, dw, cv->length);
  return 0;
}

void dbg_CVtag_release (sDbgCVtag *cv)
{
  if (!cv)
    return;
  if (cv->unknown_leaf)
    dbg_memfile_release (cv->unknown_leaf);
  if (cv->dta)
    free (cv->dta);
  free (cv);
}
