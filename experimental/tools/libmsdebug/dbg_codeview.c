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

static const char *sz_compile[] = { "iLanguage", "Flag1", "Flag1Res", "Machine", "FE_Version","Version","Build-Version", "pad" };
static const char *sz_frameproc[] = { "cbFrame", "cbPad", "offPad", "cbSaveRegs","ExHandlerAddr","FRAMEPROCFLAGS","pad" };
static const char *sz_constant[] = { "TypeIdx", "Value", "name", "pad" };
static const char *sz_objname[] = { "Signature", "name", "pad" };
static const char *sz_thunk32[] = { "pParent","pEnd","pNext", "Addr", "len", "ord", "name", "pad" };
static const char *sz_block32[] = { "pParent", "pEnd","len","Addr","name", "pad" };
static const char *sz_udt[] = { "TypeIdx", "name", "pad" };
static const char *sz_procref[] = { "sumName", "ibSym", "iMod", "name", "pad" };
static const char *sz_pub32[] = { "Flags","Addr","name","pad" };
static const char *sz_proc32[] = { "pParent","pEnd","pNext","len","DbgStart","DbgEnd","TypeIdx","Addr","CV_PROCFLAGS","name","pad" };
static const char *sz_compile2[] = { "Unk1", "Unk2", "Unk3", "Unk4", "WUnk1", "name", "pad" };
static const char *sz_gmandata[] = { "UIndex", "Flag", "Unk3", "name", "pad" };
static const char *sz_manslot[] = { "TypeIdx", "Unk1", "Unk2", "Unk3", "name", "pad" };
static const char *sz_gdata32[] = { "TypeIdx", "Addr", "name", "pad" };
static const char *sz_tokenref[] = { "sumName", "ibSym", "iMod", "name", "pad" };
static const char *sz_gmanproc[] = { "pParent", "pEnd", "pNext", "len", "DbgStart", "DbgEnd", "token", "Addr",
  "CV_PROCFLAGS", "retReg", "name", "pad" };
static const char *sz_compiler[] = { "Unk1","Unk2","Unk3","Str1","Unk4","name", "pad" };
static const char *sz_buildcmd[] = { "cmds" };
static const char *sz_end[] = { "pad" };
static const char *sz_with32[] = { "pParent", "pEnd", "len", "Addr", "expr", "pad" };
static const char *sz_label32[] = { "Addr", "CV_PROCFLAGS", "name", "pad" };
static const char *sz_section32[] = { "Id", "Unk1","StartOff", "EndOff","Attribute","name","pad"};
static const char *sz_secitioninfo32[] = { "len", "Attribute","Addr","name", "pad" };
static const char *sz_msunk1[] = { "Offset","Index","Len", "pad" };
static const char *sz_msunk2[] = { "cbOffset", "Index", "pad" };
static const char *sz_bprel32[] = { "Offset", "TypeIdx", "name", "pad" };
static const char *sz_unknown[] = { "unknown" };

static const char *sz_register[] = { "p" };

static sDbgTags stSYMs[] = {
  { DBG_CV_S_COMPILE, "S_COMPILE", "bbwwVVvp", sz_compile },
  { DBG_CV_S_END, "S_END", "p", sz_end },
  { DBG_CV_S_FRAMEPROC, "S_FRAMEPROC","uuuuAUp", sz_frameproc },
  { DBG_CV_S_OBJNAME, "S_OBJNAME", "Usp", sz_objname },
  { DBG_CV_S_THUNK32, "S_THUNK32", "uuuAwbsp", sz_thunk32 },
  { DBG_CV_S_BLOCK32, "S_BLOCK32", "uuuAsp", sz_block32 },
  { DBG_CV_S_WITH32, "S_WITH32", "uuuAsp", sz_with32 },
  { DBG_CV_S_LABEL32, "S_LABEL32", "Absp", sz_label32 },
  { DBG_CV_S_REGISTER, "S_REGISTER", "p", sz_register },
  { DBG_CV_S_CONSTANT, "S_CONSTANT", "uwsp", sz_constant },
  { DBG_CV_S_UDT, "S_UDT", "usp", sz_udt },
  { DBG_CV_S_BPREL32, "S_BPREL32", "uusp", sz_bprel32 },
  { DBG_CV_S_LDATA32, "S_LDATA32", "uAsp", sz_gdata32 },
  { DBG_CV_S_GDATA32, "S_GDATA32", "uAsp", sz_gdata32 },
  { DGB_CV_S_PUB32, "S_PUB32", "uAsp", sz_pub32 },
  { DBG_CV_S_LPROC32, "S_LPROC32","uuuuuuuAbsp", sz_proc32 },
  { DBG_CV_S_GPROC32, "S_GPROC32","uuuuuuuAbsp", sz_proc32 },
  { DBG_CV_S_COMPILE2, "S_COMPILE2", "uuuuws", sz_compile2 },
  { DBG_CV_S_LMANDATA, "S_LMANDATA", "wUusp", sz_gmandata },
  { DBG_CV_S_GMANDATA, "S_GMANDATA", "wUusp", sz_gmandata },
  { DBG_CV_S_MANSLOT, "S_MANSLOT", "uUuusp", sz_manslot },
  { DBG_CV_S_PROCREF, "S_PROCREF", "uuwsp", sz_procref },
  { DBG_CV_S_LPROCREF, "S_LPROGREF", "uuwsp", sz_procref },
  { DBG_CV_S_TOKENREF, "S_TOKENREF", "uuwsp", sz_tokenref },
  { DBG_CV_S_GMANPROC, "S_GMANPROC", "uuuuuuUAbwsp", sz_gmanproc },
  { DBG_CV_S_LMANPROC, "S_LMANPROC", "uuuuuuUAbwsp", sz_gmanproc },
  { DBG_CV_S_SECTION32, "S_SECTION32", "wwUUUsp", sz_section32 },
  { DBG_CV_S_SECTIONINFO32, "S_SECTIONINFO", "uUAsp", sz_secitioninfo32 },
  { DBG_CV_S_MSUNK1, "S_MSUNK1", "Uuup", sz_msunk1 },
  { DBG_CV_S_MSUNK2, "S_MSUNK2", "Uup", sz_msunk2 },
  { DBG_CV_S_COMPILER, "S_COMPILER", "UWuUuUsp", sz_compiler},
  { DBG_CV_S_BUILDCMD, "S_BUILDCMD", "S", sz_buildcmd },
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
	  case 'b':
	    dbg_memfile_printf (ret, " %s:%u", h->names[el], (uint32_t) dta[doff]);
	    break;
	  case 'B':
	    dbg_memfile_printf (ret, " %s:0x%02u", h->names[el], (uint32_t) dta[doff]);
	    break;
	  case 'w':
	    dbg_memfile_printf (ret, " %s:%u", h->names[el], *((uint16_t *) &dta[doff]));
	    break;
	  case 'W':
	    dbg_memfile_printf (ret, " %s:0x%04x", h->names[el], *((uint16_t *) &dta[doff]));
	    break;
	  case 'u':
	    dbg_memfile_printf (ret, " %s:%u", h->names[el], *((uint32_t *) &dta[doff]));
	    break;
	  case 'U':
	    dbg_memfile_printf (ret, " %s:0x%08x", h->names[el], *((uint32_t *) &dta[doff]));
	    break;
	  case 's':
	    dbg_memfile_printf (ret, " %s:\"%s\"", h->names[el], (char *) &dta[doff]);
	    break;
	  case 'S':
	    {
	      int befirst = 1;
	      dbg_memfile_printf (ret, " %s:{", h->names[el]);
	      while (l != 0)
	      {
		size_t ll = strlen ((char*) &dta[doff]) + 1;
		if (l < ll)
		  break;
		dbg_memfile_printf (ret, "%s\"%s\"", (befirst ? "" : ","),(char *) &dta[doff]);
		doff += ll;
		l-= ll;
		befirst = 0;
	      }
	      dbg_memfile_printf (ret,"}\n");
	    }
	    break;
	  case 'v':
	    dbg_memfile_printf (ret, " %s:%u.%u", h->names[el], *((uint16_t *) &dta[doff]) & 0xff, (*((uint16_t *) &dta[doff]) >> 8) && 0xff);
	    break;
	  case 'V':
	    dbg_memfile_printf (ret, " %s:%u.%u", h->names[el], *((uint32_t *) &dta[doff]), *((uint32_t *) &dta[doff+4]));
	    break;
	  case 'A':
	    dbg_memfile_printf (ret, " %s:0x%x:0x%x", h->names[el], *((uint16_t *) &dta[doff + 4]), *((uint32_t *) &dta[doff]));
	    break;
	  case 'p':
	    if (!l || (((doff+l)&3) == 0 && l < 4)) break;
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
  case 'u': case 'U': return sizeof (uint32_t);
  case 'w': case 'W': return sizeof (uint16_t);
  case 'b': case 'B': return sizeof (unsigned char);
  case 'V': return sizeof (uint16_t) + sizeof (uint16_t);
  case 'v': return sizeof (uint16_t);
  case 's': return strlen ((char*) &dta[off]) + 1;
  case 'S':
    {
      size_t l = 0;
      while (l < (size - off))
      {
	size_t ll = strlen ((char*) &dta[off+l]) + 1;
	if ((l+ll) > (size - off))
	  break;
	l += ll;
      }
      return l;
    }
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
	fprintf (stderr, "*** CV create: %u %u (0x%x, 0x%x)\n", (uint32_t) max2, (uint32_t) l, *((uint32_t *) dta), *((uint32_t *) &dta[4]));
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

static int cv_fill (sDbgCVtag *cv, sDbgCVCommon *cm)
{
  uint32_t *dw = (uint32_t *) cm->data;
  if (!cm)
    return -1;
  cv->length = cm->dSize - 2;
  if (cv->be_syms)
    {
      sDbgTags * h = find_tag_sym (cm->leaf);
      if (!h || h->tag == 0)
        return -1;
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
