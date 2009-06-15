static size_t dump_lfvar (unsigned char *value, sDbgMemFile *t);

static void dump_lfBClass (lfBClass *m, sDbgMemFile *t)
{
  dbg_memfile_printf (t, " LF_BCLASS(Attr:");
  dump_CV_fldattr_t (& m->attr, t);
  dbg_memfile_printf (t, ", index:%u, bclass: %s)\n",
    m->index, m->offset);
}

static void dump_lfUnion (lfUnion *m, sDbgMemFile *t)
{
  dbg_memfile_printf (t, " LF_UNION(count:%u, Prop:", m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:%u, size:%u, union %s, Undecorate:%s)\n",
    m->field, m->size, m->data, &m->data[strlen(m->data) + 1]);
}

static void dump_lfSTMember (lfSTMember *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_STMEMBER(Attr:");
  dump_CV_fldattr_t (&m->attr, t);
  dbg_memfile_printf (t, ", index:%u, %s)\n", m->index, m->name);
}

static void dump_lfNestType (lfNestType *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_NESTTYPE(pad:%u, index:%u, %s)",
    m->pad, m->index, m->name);
}

static void dump_lmFunc (lmFunc *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_MFUNCTION(returntype: %u, classtype: %u, thistype: %u, calltype: 0x%02x,",
    m->rvtype, m->classtype, m->thistype, m->calltype);
  dump_CV_funcattr_t (&m->funcattr, t);
  dbg_memfile_printf (t, ", parmcount:%u, arglist: %u,thisadjust=%ld)\n", m->parmcount, m->arglist, m->thisadjust);
}

static void dump_lfArgList (lfArgList *m, sDbgMemFile *t)
{
  uint32_t i;
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_ARGLIST(count:%u", m->count);
  if (m->count!=0)
   dbg_memfile_printf (t, ", ArgTypes[%u]={", m->count);
  for (i=0;i<m->count;i++)
    dbg_memfile_printf (t, "%s%u", i==0 ? "" : ",", m->arg[i]);
  dbg_memfile_printf (t, "%s)\n", m->count!=0 ? "}" : "");
}

static void dump_lfArray (lfArray *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_ARRAY(elemtype:%u, idxType=%u, size:%u, %s[])\n",
    m->elemtype, m->idxtype,m->size, m->data);
}

static void dump_lfClass (lfClass *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_CLASS(count:%u, Prop:",m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:%u, derived:%u, vshape:0x%x, size:%u,\n   struct %s, Undecorated: %s)\n",
    m->field, m->derived,m->vshape,m->size,
    m->data, & m->data[strlen (m->data) + 1]);
}

static void dump_lfStruct (lfStruct *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_STRUCTURE(count:%u, Prop:",m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:%u, derived:%u, vshape:0x%x, size:%u,\n   struct %s, Undecorated: %s)\n",
    m->field, m->derived,m->vshape,m->size,
    m->data, & m->data[strlen (m->data) + 1]);
}

static void dump_lfFieldList (lfFieldList *m, size_t size, sDbgMemFile *t)
{
  lfEasy *e;
  char *dta;
  if (!m || !t || !size)
    return;
  dta = m->data;
  dbg_memfile_printf (t, "  LF_FIELDLIST:\n");
  while (size > 2)
  {
    size_t l;
    e=(lfEasy *) dta;
    switch (e->leaf)
    {
    case LF_BCLASS:
      dbg_memfile_printf (t, "  eBClass pad:%u, indext:%u, offset:%u\n",
        e->bClassFL.pad, e->bClassFL.utype, e->bClassFL.off);
      l = 10;
      break;
    case LF_STMEMBER:
      dbg_memfile_printf (t, "  eSTMember pad:%u, index:%u, %s\n",
        e->stMemberFL.pad, e->stMemberFL.index, e->stMemberFL.name);
      l = strlen (e->stMemberFL.name) + 1 + 2 + 2 + 4;
      break;
    case LF_NESTTYPE:
      dbg_memfile_printf (t, "  eNestType pad:%u, index:%u, %s\n",
        e->nestTypeFL.pad, e->nestTypeFL.index, e->nestTypeFL.name);
      l = strlen (e->nestTypeFL.name) + 1 + 4 + 2 + 2;
      break;
    case LF_ENUMERATE:
      {
        size_t vs;
        unsigned char *value;
        dbg_memfile_printf (t, "  eEnum Attr:");
        dump_CV_fldattr_t (& e->enumFL.attr, t);
        l = 2 + 2;
        value = e->enumFL.value;
        dbg_memfile_printf (t, ", Value:");
        vs = dump_lfvar (value, t);
        l += vs;
        value += vs;
        dbg_memfile_printf (t, ", %s\n", value);
        l += strlen (value) + 1;
      }
      break;
    case LF_MEMBER:
      dbg_memfile_printf (t, "  eMember pad: %u, index:%u Offset:0x%x, %s\n", e->memberFL.pad, e->memberFL.index,
        e->memberFL.offset, e->memberFL.name );
      l = strlen (e->memberFL.name) + 1 + 4 + 4 + 2;
      break;
    case LF_METHOD:
      dbg_memfile_printf (t, "  eMethod count:%u, mList:%u, %s\n",
        e->methodFL.count, e->methodFL.mList, e->methodFL.name);
      l = strlen (e->methodFL.name) + 1 + 8;
      break;
    case LF_ONEMETHOD:
      if ((e->oneMethodFL.pad & 0x10) == 0) {
		dbg_memfile_printf (t, "  eOneMeth pad:%u, index:%u, %s\n",
		  e->oneMethodFL.pad, e->oneMethodFL.index, e->oneMethodFL.name);
		l = strlen (e->oneMethodFL.name) + 1 + 4 + 2 + 2;
	  } else {
		dbg_memfile_printf (t, "  eOneMeth pad:%u, index:%u, size:0x%x, %s\n",
		  e->oneMethodFL.pad, e->oneMethodFL.index, *((uint32_t *) e->oneMethodFL.name), &e->oneMethodFL.name[4]);
		l = strlen (&e->oneMethodFL.name[4]) + 1 + 4 + 2 + 2 + 2 + 4;
      }
      break;
    default:
      dbg_memfile_printf (t, "   Unknown fieldlist subtype 0x%x\n", e->leaf);
      while (size > 0)
        {
          dbg_memfile_printf (t, " %02X", (unsigned char) dta[0]);
          size--; dta++;
          if ((size & 0xf) == 0) dbg_memfile_printf (t,"\n");
       }
      return;
    }
    l = (l + 3) & ~3;
    dta += l;
    if (size < l)
      break;
    size -= l;
  }
}
static void dump_lfEnum (lfEnum *m, sDbgMemFile *t)
{
  unsigned char *n;
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_ENUM(count:%u, prop:", m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", utype:%u, field:%u, enum ",
   m->utype,m->field);
  n = &m->name[0];
  dbg_memfile_printf (t, "%s", n); n+=strlen (n) + 1;
  dbg_memfile_printf (t, ", Undecorated:%s",n);
  dbg_memfile_printf (t, ")\n");
}

static void dump_lfOneMethod (lfOneMethod *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_ONEMETHOD(Attr:");
  dump_CV_fldattr_t (& m->attr, t);
  dbg_memfile_printf (t, ", Index:%u, vbaseoff:%u)\n",m->index,m->vbaseoff[0]);
}

static void dump_lfProc (lfProc *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_PROCEDURE(returntype: %u, calltype: 0x%02x,",m->rvtype, m->calltype);
  dump_CV_funcattr_t (&m->funcattr, t);
  dbg_memfile_printf (t, ", parmcount:%u, arglist: %u)\n", m->parmcount, m->arglist);
}

static void dump_lfPointer (lfPointer *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_POINTER(type: %u, ptrtype: %u, ptrmode: %u", m->utype, m->attr.ptrtype,m->attr.ptrmode);
  if (m->attr.isflat32)
    dbg_memfile_printf (t, " flat32");
  if (m->attr.isvolatile)
    dbg_memfile_printf (t, " volatile");
  if (m->attr.isconst)
    dbg_memfile_printf (t, " const");
  if (m->attr.isunaligned)
    dbg_memfile_printf (t, " __unaligned");
  if (m->attr.isrestrict)
    dbg_memfile_printf (t, " __restricted");
  if (m->attr.size != 0)
    dbg_memfile_printf (t, " size:%u", m->attr.size);
  if (m->attr.unused != 0)
    dbg_memfile_printf (t, " /* /* attr has unknown flags: 0x%x */", m->attr.unused);
  dbg_memfile_printf (t, ")\n");
}

static void dump_lfModifier (lfModifier *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_MODIFER(type: %u, ", m->type);
  dump_CV_modifier_t (& m->attr, t);
  dbg_memfile_printf (t, ")\n");
}

static void dump_CV_prop_t (CV_prop_t *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  if (m->packed)
    dbg_memfile_printf (t, " packed");
  if (m->ctor)
    dbg_memfile_printf (t, " ctor");
  if (m->ovlops)
    dbg_memfile_printf (t, " ovlops");
  if (m->isnested)
    dbg_memfile_printf (t, " nested");
  if (m->cnested)
    dbg_memfile_printf (t, " cnested");
  if (m->opassign)
    dbg_memfile_printf (t, " opassign");
  if (m->opcast)
    dbg_memfile_printf (t, " opcast");
  if (m->fwdref)
    dbg_memfile_printf (t, " forwardref");
  if (m->scoped)
    dbg_memfile_printf (t, " scoped");
  if (m->hasuniquename)
    dbg_memfile_printf (t, " uniquename");
  if (m->sealed)
    dbg_memfile_printf (t, " sealed");
  if (m->hfa != 0)
    dbg_memfile_printf (t, " hfa: %u", m->hfa);
  if (m->intrinsic)
    dbg_memfile_printf (t, " intrinsic");
  if (m->reserved!=0)
    dbg_memfile_printf (t, " /* CV_prop_t has unknown flags 0x%x */", m->reserved);
}

static void dump_CV_funcattr_t (CV_funcattr_t *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  if (m->cxxreturnudt)
    dbg_memfile_printf (t, " cxxreturnudt");
  if (m->ctor)
    dbg_memfile_printf (t, " ctor");
  if (m->ctorvbase)
    dbg_memfile_printf (t, " ctorvbase");
  if (m->unused)
    dbg_memfile_printf (t, " /* CV_funcattr_t has unknown flags 0x%x */", m->unused);
}

static void dump_CV_fldattr_t (CV_fldattr_t *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  switch (m->access) {
  case CV_private: dbg_memfile_printf (t, " private:"); break;
  case CV_protected: dbg_memfile_printf (t, " protected:"); break;
  case CV_public: dbg_memfile_printf (t, " public:"); break;
  default:
    if (m->access != 0)
      dbg_memfile_printf (t, " access: %u", m->access);
    break;
  }
  switch (m->mprop)
  {
  case CV_MTvanilla: dbg_memfile_printf (t, " vanilla"); break;
  case CV_MTvirtual: dbg_memfile_printf (t, " virtual"); break;
  case CV_MTstatic: dbg_memfile_printf (t, " static"); break;
  case CV_MTfriend: dbg_memfile_printf (t, " friend"); break;
  case CV_MTintro: dbg_memfile_printf (t, " intro"); break;
  case CV_MTpurevirt: dbg_memfile_printf (t, " pure virtual"); break;
  case CV_MTpureintro:dbg_memfile_printf (t, " pure intro"); break;
  default:
  dbg_memfile_printf (t, " mprop: %u", m->mprop);
  break;
  }
  if (m->pseudo)
    dbg_memfile_printf (t, " pseudo");
  if (m->noinherit)
    dbg_memfile_printf (t, " noinherit");
  if (m->noconstruct)
    dbg_memfile_printf (t, " noconstruct");
  if (m->compgenx)
    dbg_memfile_printf (t, " compgenx");
  if (m->sealed)
    dbg_memfile_printf (t, " sealed");
  if (m->unused)
    dbg_memfile_printf (t, " /* CV_fldattr_t has unknown flags 0x%x */", m->unused);
}

static void dump_CV_modifier_t (CV_modifier_t *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  if (m->MOD_const)
    dbg_memfile_printf (t, " const");
  if (m->MOD_volatile)
    dbg_memfile_printf (t, " volatile");
  if (m->MOD_unaligned)
    dbg_memfile_printf (t, " __unaligned");
  if (m->MOD_unused != 0)
    dbg_memfile_printf (t, " /* CV_modifier_t has unknown flags 0x%x */", m->MOD_unused);
}

static size_t dump_lfvar (unsigned char *value, sDbgMemFile *t)
{
  size_t len = 2;
  unsigned short *us = (unsigned short *) value;
  value += 2;
  if ((us[0] & 0x8000) == 0)
    {
      if (t)
        dbg_memfile_printf (t, " %u", us[0]);
      return 2;
    }
  switch (us[0])
    {
    case LF_CHAR:
      dbg_memfile_printf (t, "(unsigned char) %u", value[0]);
      len += 1;
      break;
    case LF_SHORT:
      dbg_memfile_printf (t, "(short) %d", *((short *)value));
      len += 2;
      break;
    case LF_USHORT:
      dbg_memfile_printf (t, "(unsigned short) %u", us[1]);
      len += 2;
      break;
    case LF_LONG:
      dbg_memfile_printf (t, "(long) %d", *((int *)value));
      len += 4;
      break;
    case LF_ULONG:
      dbg_memfile_printf (t, "(unsigned long) %u", *((unsigned int *)value));
      len += 4;
      break;
    case LF_REAL32:
      dbg_memfile_printf (t, "(float) %f", *((float *)value));
      len += 4;
      break;
    case LF_REAL64:
      dbg_memfile_printf (t, "(double) %g", *((double *)value));
      len += 8;
      break;
    default:
      dbg_memfile_printf (t, "lftype=0x%x unknown", us[0]);
      break;
    }
  return len;
}
