static void dump_typeid (uint32_t ty, sDbgMemFile *t);
static size_t dump_lfvar (unsigned char *value, sDbgMemFile *t);
static int has_CV_fldattr_t_VBase (CV_fldattr_t *t);

static void dump_lfVTshape (lfVTshape *m, sDbgMemFile *t)
{
  uint16_t i;
  unsigned char *d = m->vtshape;
  dbg_memfile_printf (t," LF_VTSHAPE(eCV_vtshape[%u]={", m->count);
  for (i=0;i < m->count;i++) {
    if (i!=0) dbg_memfile_printf (t, ",");
    if ((i&1)==0)
      dump_CV_vtshape (d[0]>>4, t);
    else
      {
        dump_CV_vtshape (d[0]&0xf, t);
        d++;
      }
  }
  dbg_memfile_printf(t, "})\n");
}

static void dump_CV_vtshape (unsigned char vt, sDbgMemFile *t)
{
  vt &= 0x0f;
  switch (vt) {
  case CV_VTNEAR: dbg_memfile_printf(t, "__vtnear"); break;
  case CV_VTFAR: dbg_memfile_printf(t, "__vtfar"); break;
  case CV_VTTHIN: dbg_memfile_printf(t, "__vtthin"); break;
  case CV_VTAPDISP: dbg_memfile_printf(t, "__vtapdisp"); break;
  case CV_VTFPMETA: dbg_memfile_printf(t, "__vtfpmeta"); break;
  case CV_VTNEAR32: dbg_memfile_printf(t, "__vtnear"); break;
  case CV_VTFAR32: dbg_memfile_printf(t, "__vtfar"); break;
  default:
    dbg_memfile_printf (t,"unknownVTshape%u", vt);
    break;
  }
}

static void dump_CV_ptrtype (uint32_t pt, sDbgMemFile *t)
{
  switch (pt) {
  case CV_PTR_NEAR: break;
  case CV_PTR_FAR: dbg_memfile_printf (t, " __far"); break;
  case CV_PTR_HUGE: dbg_memfile_printf (t, " __huge"); break;
  case CV_PTR_BASE_SEG: dbg_memfile_printf (t, " __baseseg"); break;
  case CV_PTR_BASE_VAL: dbg_memfile_printf (t, " __baseval"); break;
  case CV_PTR_BASE_SEGVAL:  dbg_memfile_printf (t, " __segval"); break;
  case CV_PTR_BASE_ADDR:  dbg_memfile_printf (t, " __baseaddr"); break;
  case CV_PTR_BASE_SEGADDR: dbg_memfile_printf (t, " __segaddr"); break;
  case CV_PTR_BASE_TYPE: dbg_memfile_printf (t, " __basetype"); break;
  case CV_PTR_BASE_SELF: dbg_memfile_printf (t, " __self"); break;
  case CV_PTR_NEAR32: break;
  case CV_PTR_FAR32: dbg_memfile_printf (t, " __far"); break;
  case CV_PTR_64: dbg_memfile_printf (t, " __w64"); break;
  case CV_PTR_UNUSEDPTR: dbg_memfile_printf (t, " __unusedptr"); break;
  default:
    dbg_memfile_printf (t, " __unknown%u", pt); break;
  }  
}

static void dump_CV_ptrmode (uint32_t pm, sDbgMemFile *t)
{
  switch (pm)
  {
  case CV_PTR_MODE_PTR: dbg_memfile_printf (t, " *"); break;
  case CV_PTR_MODE_REF: dbg_memfile_printf (t, " &"); break;
  case CV_PTR_MODE_PMEM: dbg_memfile_printf (t, " * /* mem */"); break;
  case CV_PTR_MODE_PMFUNC: dbg_memfile_printf (t, " (*) /* mfunc */"); break;
  case CV_PTR_MODE_RESERVED: dbg_memfile_printf (t, " * /* reserved */"); break;
  default:
    dbg_memfile_printf (t, " /* unknown ptr mode%u */*", pm); break;
  }
}

static void dump_CV_call (unsigned char call, sDbgMemFile *t)
{
  if (!t)
    return;
  switch (call)
    {
	case CV_CALL_NEAR_C:
	  dbg_memfile_printf (t, " __cdecl"); break;
	case CV_CALL_FAR_C:
	  dbg_memfile_printf (t, " __cdecl __far"); break;
	case CV_CALL_NEAR_PASCAL:
	  dbg_memfile_printf (t, " __pascal"); break;
	case CV_CALL_FAR_PASCAL:
	  dbg_memfile_printf (t, " __pascal __far"); break;
	case CV_CALL_NEAR_FAST:
	  dbg_memfile_printf (t, " __fastcall"); break;
	case CV_CALL_FAR_FAST:
	  dbg_memfile_printf (t, " __fastcall __far"); break;
	case CV_CALL_SKIPPED:
	  dbg_memfile_printf (t, " __unknown"); break;
	case CV_CALL_NEAR_STD:
	  dbg_memfile_printf (t, " __stdcall"); break;
	case CV_CALL_FAR_STD:
	  dbg_memfile_printf (t, " __stdcall __far"); break;
	case CV_CALL_NEAR_SYS:
	  dbg_memfile_printf (t, " __syscall"); break;
	case CV_CALL_FAR_SYS:
	  dbg_memfile_printf (t, " __syscall __far"); break;
	case CV_CALL_THISCALL:
	  dbg_memfile_printf (t, " __thiscall"); break;
	case CV_CALL_MIPSCALL:
	  dbg_memfile_printf (t, " __mipscall"); break;
	case CV_CALL_GENERIC:
	  dbg_memfile_printf (t, " __generic"); break;
	case CV_CALL_ALPHACALL:
	  dbg_memfile_printf (t, " __alphacall"); break;
	case CV_CALL_PPCCALL:
	  dbg_memfile_printf (t, " __ppccall"); break;
	case CV_CALL_SHCALL:
	  dbg_memfile_printf (t, " __shcall"); break;
	case CV_CALL_ARMCALL:
	  dbg_memfile_printf (t, " __armcall"); break;
	case CV_CALL_AM33CALL:
	  dbg_memfile_printf (t, " __am33call"); break;
	case CV_CALL_TRICALL:
	  dbg_memfile_printf (t, " __tricall"); break;
	case CV_CALL_SH5CALL:
	  dbg_memfile_printf (t, " __sh5call"); break;
	case CV_CALL_M32RCALL:
	  dbg_memfile_printf (t, " __m32rcall"); break;
	case  CV_CALL_CLRCALL:
	  dbg_memfile_printf (t, " __clrcall"); break;
	default:
	  dbg_memfile_printf (t, " Unknown calling convention 0x%x", call); break;
    }
}

static void dump_lfBitfield (lfBitfield *m, sDbgMemFile *t)
{
  dbg_memfile_printf (t, " LF_BITFIELD(Type:");
  dump_typeid (m->type, t);
  dbg_memfile_printf (t, ", length:%u, bitpos:%u)\n",
    m->length, m->position);
}

static void dump_lfMethodList (lfMethodList *m, size_t size, sDbgMemFile *t)
{
  uint32_t i;
  unsigned char *d = m->data;
  ct_methodlist *ml;
  dbg_memfile_printf (t, " LF_METHODLIST(\n");
  i = 0;
  while (size >= 8)
    {
      dbg_memfile_printf (t, "  %%%u: Attr:", i);
      ml = (ct_methodlist *) d;
      d += 8;
      size -=8;
      dump_CV_fldattr_t (& ml->attr, t);
      dbg_memfile_printf (t, ",Flags:%u,Index:", (uint32_t) ml->unk);
      dump_typeid (ml->index, t);
      if(has_CV_fldattr_t_VBase (& ml->attr))
        {
          dbg_memfile_printf (t, ", VBase:0x%x", ml->offset[0]);
          size -= 4;
          d+=4;
        }
      dbg_memfile_printf (t, "\n");
      i++;
    }
  if (size != 0)
    dbg_memfile_printf (t, " Remains:%u bytes)\n", (uint32_t) size);
  else
    dbg_memfile_printf (t, " )\n");
}

static void dump_lfBClass (lfBClass *m, sDbgMemFile *t)
{
  dbg_memfile_printf (t, " LF_BCLASS(Attr:");
  dump_CV_fldattr_t (& m->attr, t);
  dbg_memfile_printf (t, ", index:");
  dump_typeid (m->index, t);
  dbg_memfile_printf (t, ", bclass: %s)\n", m->offset);
}

static void dump_lfUnion (lfUnion *m, sDbgMemFile *t)
{
  dbg_memfile_printf (t, " LF_UNION(count:%u, Prop:", m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:");
  dump_typeid (m->field, t);
  dbg_memfile_printf (t, ", size:%u, union %s, Undecorate:%s)\n",
    m->size, m->data, &m->data[strlen(m->data) + 1]);
}

static void dump_lfSTMember (lfSTMember *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_STMEMBER(Attr:");
  dump_CV_fldattr_t (&m->attr, t);
  dbg_memfile_printf (t, ", index:");
  dump_typeid (m->index, t);
  dbg_memfile_printf (t, ", %s)\n", m->index, m->name);
}

static void dump_lfNestType (lfNestType *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_NESTTYPE(pad:%u, index:", m->pad);
  dump_typeid (m->index, t);
  dbg_memfile_printf (t, ", %s)\n", m->name);
}

static void dump_lmFunc (lmFunc *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_MFUNCTION(returntype:");
  dump_typeid (m->rvtype, t);
  dbg_memfile_printf (t, ", classtype:");
  dump_typeid (m->classtype, t);
  dbg_memfile_printf (t, ", thistype:");
  dump_typeid (m->thistype, t);
  dbg_memfile_printf (t, ", calltype:");
  dump_CV_call (m->calltype, t);
  dbg_memfile_printf (t, ", attr:");
  dump_CV_funcattr_t (&m->funcattr, t);
  dbg_memfile_printf (t, ", parmcount:%u, arglist:", m->parmcount);
  dump_typeid (m->arglist, t);
  dbg_memfile_printf (t, ",thisadjust=%ld)\n", m->thisadjust);
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
   {
     dbg_memfile_printf (t, "%s", i==0 ? "" : ",");
    dump_typeid (m->arg[i], t);
   }
  dbg_memfile_printf (t, "%s", m->count!=0 ? "}" : "");
  dbg_memfile_printf (t, ")\n");
}

static void dump_lfArray (lfArray *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_ARRAY(elemtype:");
  dump_typeid (m->elemtype, t);
  dbg_memfile_printf (t, ", idxType=");
  dump_typeid (m->idxtype, t);
  dbg_memfile_printf (t, ", size:%u, %s[])\n",m->size, m->data);
}

static void dump_lfClass (lfClass *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_CLASS(count:%u, Prop:",m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:");
  dump_typeid (m->field, t);
  dbg_memfile_printf (t, ", derived:");
  dump_typeid (m->derived, t);
  dbg_memfile_printf (t, ", vshape:%u, size:%u,\n   struct %s, Undecorated: %s)\n",
    m->vshape,m->size,
    m->data, & m->data[strlen (m->data) + 1]);
}

static void dump_lfStruct (lfStruct *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, "  LF_STRUCTURE(count:%u, Prop:",m->count);
  dump_CV_prop_t (& m->property, t);
  dbg_memfile_printf (t, ", field:");
  dump_typeid (m->field, t);
  dbg_memfile_printf (t, ", derived:");
  dump_typeid (m->derived, t);
  dbg_memfile_printf (t, ", vshape:%u, size:%u,\n   struct %s, Undecorated: %s)\n",
    m->vshape,m->size,
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
    case LF_VFUNCTAB:
      dbg_memfile_printf (t, "  eVFuncTab pad:%u, type:", e->vfunctabFL.pad);
      dump_typeid (e->vfunctabFL.type, t);
      dbg_memfile_printf (t, ")\n");
      l = 2 + 2 + 4;
      break;
    case LF_BCLASS:
      dbg_memfile_printf (t, "  eBClass Attr:");
      dump_CV_fldattr_t (& e->bClassFL.attr, t);
      dbg_memfile_printf (t, ", indext:");
      dump_typeid (e->bClassFL.utype, t);
      dbg_memfile_printf (t, ", offset:%u\n", e->bClassFL.off);
      l = 10;
      break;
    case LF_STMEMBER:
      dbg_memfile_printf (t, "  eSTMember Attr:");
      dump_CV_fldattr_t (& e->stMemberFL.attr, t);
      dbg_memfile_printf (t, ", Index:");
      dump_typeid (e->stMemberFL.index, t);
      dbg_memfile_printf (t, ", %s\n", e->stMemberFL.name);
      l = strlen (e->stMemberFL.name) + 1 + 2 + 2 + 4;
      break;
    case LF_NESTTYPE:
      dbg_memfile_printf (t, "  eNestType pad:%u, index:", e->nestTypeFL.pad);
      dump_typeid (e->nestTypeFL.index, t);
      dbg_memfile_printf (t, ", %s\n",e->nestTypeFL.name);
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
      dbg_memfile_printf (t, "  eMember Attr:");
      dump_CV_fldattr_t (& e->memberFL.attr, t);
      dbg_memfile_printf (t, ", index:");
      dump_typeid (e->memberFL.index, t);
      dbg_memfile_printf (t, ", Offset:0x%x, %s\n", e->memberFL.offset, e->memberFL.name);
      l = strlen (e->memberFL.name) + 1 + 4 + 4 + 2;
      break;
    case LF_METHOD:
      dbg_memfile_printf (t, "  eMethod count:%u, mList:", e->methodFL.count);
      dump_typeid (e->methodFL.mList, t);
      dbg_memfile_printf (t, ", %s\n", e->methodFL.name);
      l = strlen (e->methodFL.name) + 1 + 8;
      break;
    case LF_ONEMETHOD:
      {
        uint32_t *vboff = e->oneMethodFL.vbaseoff;
		dbg_memfile_printf (t, "  eOneMeth Attr:");
		dump_CV_fldattr_t (& e->oneMethodFL.attr, t);
		dbg_memfile_printf (t, ", Index:");
		dump_typeid (e->oneMethodFL.index, t);
		l = 8;
		if (has_CV_fldattr_t_VBase (& e->oneMethodFL.attr))
		  {
		    dbg_memfile_printf (t, ", VBase:0x%x", vboff[0]);
		    vboff++;
		    l += 4;
		  }
	    dbg_memfile_printf (t, ", %s\n", (char *) vboff);
	    l += strlen ((char*)vboff) + 1;
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
  dbg_memfile_printf (t, ", utype:");
  dump_typeid (m->utype, t);
  dbg_memfile_printf (t, ", field:");
  dump_typeid (m->field, t);
  dbg_memfile_printf (t, ", enum ");
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
  dbg_memfile_printf (t, ", Index:");
  dump_typeid (m->index, t);
  dbg_memfile_printf (t, ", vbaseoff:%u)\n",m->vbaseoff[0]);
}

static void dump_lfProc (lfProc *m, sDbgMemFile *t)
{
  char *name;
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_PROCEDURE(returntype:");
  dump_typeid (m->rvtype, t);
  dbg_memfile_printf (t, ", calltype:");
  dump_CV_call (m->calltype, t);
  dbg_memfile_printf (t, ", attr:");
  dump_CV_funcattr_t (&m->funcattr, t);
  dbg_memfile_printf (t, ", parmcount:%u, arglist:", m->parmcount);
  dump_typeid (m->arglist, t);
  dbg_memfile_printf (t, ")\n");
}

static void dump_lfPointer (lfPointer *m, sDbgMemFile *t)
{
  if (!m || !t)
    return;
  dbg_memfile_printf (t, " LF_POINTER(type:");
  dump_typeid (m->utype, t);
  dbg_memfile_printf (t, ",");
  dump_CV_ptrtype (m->attr.ptrtype, t);
  dump_CV_ptrmode (m->attr.ptrmode, t);
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
  dbg_memfile_printf (t, " LF_MODIFER(type:");
  dump_typeid (m->type, t);
  dbg_memfile_printf (t, ", ");
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
  case CV_MTvanilla: break;
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

static int has_CV_fldattr_t_VBase (CV_fldattr_t *t)
{
  switch (t->mprop)
    {
    case CV_MTintro: case CV_MTpurevirt: case CV_MTpureintro:
	  return 1;
	}
  return 0;
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

static void dump_typeid (uint32_t ty, sDbgMemFile *t)
{
  static const char *sp[9] = { "<none>","<absolute>","<segment>","void", "<currency>","basicstring","__far basicstring","<not-translated>","HRESULT" };
  const char *bsign;
  uCV_type u;
  u.type = ty;
  if (ty >= 0x100)
    {
      dbg_memfile_printf (t, "#%u", ty);
      return;
    }
  switch (u.type_kind)
  {
  case CV_SPECIAL:
    if (u.type_spec > 8) break;
    dbg_memfile_printf(t, "%s", sp[u.type_spec]); return;
  case CV_SIGNED:
    bsign="signed"; goto cv1;
  case CV_UNSIGNED:
    bsign="unsigned";
cv1:
	switch (u.type_spec) {
	case  CV_IN_1BYTE: dbg_memfile_printf (t, "%s char", bsign); return;
	case  CV_IN_2BYTE: dbg_memfile_printf (t, "%s short", bsign); return;
	case  CV_IN_4BYTE: dbg_memfile_printf (t, "%s int", bsign); return;
	case  CV_IN_8BYTE: dbg_memfile_printf (t, "%s __int64", bsign); return;
	case  CV_IN_16BYTE: dbg_memfile_printf (t, "%s __int128", bsign); return;
    default: break;
    }
    break;
  case CV_INT:
    switch (u.type_spec) {
    case CV_RI_CHAR: dbg_memfile_printf (t, "char"); return;
    case CV_RI_UCHAR: dbg_memfile_printf (t, "uchar"); return;
    case CV_RI_INT2: dbg_memfile_printf (t, "short"); return;
    case CV_RI_UINT2: dbg_memfile_printf (t, "ushort"); return;
    case CV_RI_INT4: dbg_memfile_printf (t, "int"); return;
    case CV_RI_UINT4: dbg_memfile_printf (t, "uint"); return;
    case CV_RI_INT8: dbg_memfile_printf (t, "__int64"); return;
    case CV_RI_UINT8: dbg_memfile_printf (t, "unsigned __int64"); return;
    case CV_RI_INT16: dbg_memfile_printf (t, "__int128"); return;
    case CV_RI_UINT16: dbg_memfile_printf (t, "unsigned __int128"); return;
    default: break;
    }
    break;
  case CV_REAL:
    switch (u.type_spec) {
    case CV_RC_REAL32: dbg_memfile_printf (t, "float"); return;
    case CV_RC_REAL64: dbg_memfile_printf (t, "double"); return;
    case CV_RC_REAL80: dbg_memfile_printf (t, "long double"); return;
    case CV_RC_REAL128:  dbg_memfile_printf (t, "__m128"); return;
    case CV_RC_REAL48:  dbg_memfile_printf (t, "__float48"); return;
    default:
      break;
    }
    break;
  case CV_BOOLEAN:
    if (u.type_spec == 0)
      {
        dbg_memfile_printf (t, "BOOL"); return;
      }
    break;
  case CV_COMPLEX:
  case CV_SPECIAL2:
  default:
    break;
  }
  dbg_memfile_printf (t, "#%u(0x%x)", ty, ty);
}
