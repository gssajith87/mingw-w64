#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

#include "m_token.h"
#include "m_ms.h"

#ifdef __CYGWIN__
#define MY_LL  "ll"
#else
#define MY_LL  "I64"
#endif

uMToken *
gen_tok (enum eMToken kind, enum eMSToken subkind, size_t addend)
{
  uMToken *ret;
  switch (kind)
    {
    case eMToken_value:
      addend += sizeof (sMToken_value);
      break;
    case eMToken_name:
      addend += sizeof (sMToken_name);
      break;
    case eMToken_dim:
      addend += sizeof (sMToken_dim);
      break;
    case eMToken_unary:
      addend += sizeof (sMToken_Unary);
      break;
    case eMToken_binary:
      addend += sizeof (sMToken_binary);
      break;
    default:
      abort ();
    }
  addend += (addend + 15) & ~15;
  ret = (uMToken *) malloc (addend);
  if (!ret)
    abort ();
  memset (ret, 0, addend);

  MTOKEN_KIND (ret) = kind;
  MTOKEN_SUBKIND (ret) = subkind;

  return ret;
}

static void
dump_tok1 (FILE *fp, uMToken *p)
{
  if (!p)
    return;
  switch (MTOKEN_KIND (p))
    {
      case eMToken_value:
        fprintf (fp, "'value:%d: ", MTOKEN_SUBKIND (p));
        if (MTOKEN_VALUE_SIGNED (p))
          {
            fprintf(fp, "%"MY_LL "dLL", MTOKEN_VALUE (p));
          }
        else
          {
            fprintf(fp, "0x%"MY_LL"xULL", MTOKEN_VALUE (p));
          }
        fprintf (fp,"'");
        break;
      case eMToken_name:
        fprintf (fp,"'name:%d %s'", MTOKEN_SUBKIND (p), MTOKEN_NAME (p));
        break;
      case eMToken_dim:
        fprintf (fp,"'dim:%d %s", MTOKEN_SUBKIND (p), MTOKEN_DIM_NEGATE (p) ? "-" : "");
        dump_tok (fp, MTOKEN_DIM_VALUE (p));
        if (MTOKEN_DIM_NTTP (p))
          {
            fprintf (fp," ");
            dump_tok (fp, MTOKEN_DIM_NTTP (p));
          }
        fprintf (fp,"'");
        break;
      case eMToken_unary:
        fprintf (fp,"'unary:%d ", MTOKEN_SUBKIND (p));
        dump_tok (fp, MTOKEN_UNARY (p));
        fprintf (fp, "'");
        break;
      case eMToken_binary:
        fprintf (fp,"'binary:%d ", MTOKEN_SUBKIND (p));
        dump_tok (fp, MTOKEN_BINARY_LEFT (p));
        fprintf (fp," ");
        dump_tok (fp, MTOKEN_BINARY_RIGHT (p));
        fprintf (fp, "'");
        break;
      default:
        fprintf (fp,"'kind(%d/%d):", MTOKEN_KIND (p), MTOKEN_SUBKIND(p));
        abort ();
    }
}

void
dump_tok (FILE *fp, uMToken *p)
{
  if (!p)
    return;
  fprintf (fp, "'[");

  while (p)
    {
      dump_tok1 (fp, p);
      p = MTOKEN_CHAIN (p);
      if (p) fprintf (fp,",");
    }
  fprintf (fp,"]'");
}

uMToken *
chain_tok (uMToken *l, uMToken *add)
{
  uMToken *p = l;
  if (!l)
    return add;
  if (!add)
    return l;
  while (MTOKEN_CHAIN (p))
    p = MTOKEN_CHAIN (p);
  MTOKEN_CHAIN (p) = add;

  return l;
}

uMToken *
release_tok (uMToken *tok)
{
  uMToken *ret = NULL;
  
  while (tok != NULL)
    {
      ret = MTOKEN_CHAIN (tok);
      free (tok);
      tok = ret;
    }
  return NULL;
}

uMToken *
gen_value (enum eMSToken skind, uint64_t val, int is_signed, int size)
{
  uMToken *ret = gen_tok (eMToken_value, skind, 0);
  MTOKEN_VALUE (ret) = val;
  MTOKEN_VALUE_SIGNED (ret) = is_signed;
  MTOKEN_VALUE_SIZE (ret) = size;
  
  return ret;
}

uMToken *
gen_name (enum eMSToken skind, const char *name)
{
  uMToken *ret;
  
  if (!name)
    name = "";
  ret = gen_tok (eMToken_name, skind, strlen (name) + 1);
  strcpy (MTOKEN_NAME (ret), name);

  return ret;
}

uMToken *
gen_dim (enum eMSToken skind, uint64_t val, const char *non_tt_param, int fSigned, int fNegate)
{
  uMToken *ret = gen_tok (eMToken_dim, skind, 0);
  
  MTOKEN_DIM_VALUE(ret) = gen_value (eMST_val, val, fSigned, 8);
  if (non_tt_param)
    MTOKEN_DIM_NTTP(ret) = gen_name (eMST_nttp, non_tt_param);
  MTOKEN_DIM_NEGATE(ret) = fNegate;
  return ret;
}

uMToken *
gen_unary (enum eMSToken skind, uMToken *un)
{
  uMToken *ret = gen_tok (eMToken_unary, skind, 0);
  MTOKEN_UNARY (ret) = un;
  return ret;
}

uMToken *
gen_binary (enum eMSToken skind, uMToken *l, uMToken *r)
{
  uMToken *ret = gen_tok (eMToken_binary, skind, 0);
  MTOKEN_BINARY_LEFT (ret) = l;
  MTOKEN_BINARY_RIGHT (ret) = r;
  return ret;
}

static void
print_decl1 (FILE *fp, uMToken *r)
{
  while (r != NULL)
    {
      switch (MTOKEN_KIND(r))
      {
        case eMToken_name:
	  switch (MTOKEN_SUBKIND (r))
	  {
	  case eMST_unmangled:
	  case eMST_vftable: case eMST_vbtable: case eMST_vcall:
	    fprintf (fp, "%s", MTOKEN_NAME (r)); break;
	  case eMST_name:
	  case eMST_nttp: case eMST_rtti:
	  case eMST_cv: case eMST_type:
	  case eMST_opname:
	    fprintf (fp, "%s", MTOKEN_NAME (r)); break;
	  case eMST_colon:
	    fprintf (fp, "%s:", MTOKEN_NAME (r)); break;
	  default:
	    fprintf (fp, "%d:%s", MTOKEN_SUBKIND(r), MTOKEN_NAME (r));
	    break;
	  }
	  break;
	case eMToken_value:
	  switch (MTOKEN_SUBKIND (r))
	    {
	      default:
		fprintf (fp, "v%d:", MTOKEN_SUBKIND (r));
	      case eMST_gcarray:
		fprintf (fp,"__gc[");
	      case eMST_val:
		if (MTOKEN_VALUE_SIGNED (r))
		  {
		    if ((MTOKEN_VALUE (r) >> 32) != 0)
		      fprintf (fp, "0x%lx%08lx", (unsigned long) (MTOKEN_VALUE (r) >> 32), (unsigned long) MTOKEN_VALUE (r));
		    else
		      fprintf (fp,"0x%lx", (unsigned long) MTOKEN_VALUE (r));
		    fprintf (fp, "U");
		  }
		else
		  {
		    fprintf (fp,"%"MY_LL"d", (long long) MTOKEN_VALUE (r));
		  }
		if (MTOKEN_VALUE_SIZE (r) == 8) fprintf (fp, "LL");
		else if (MTOKEN_VALUE_SIZE (r) == 4) fprintf (fp,"L");
		if (MTOKEN_SUBKIND (r) == eMST_gcarray)
		  fprintf (fp,"]");
		break;
	    }
	  break;
	case eMToken_dim:
	  switch (MTOKEN_SUBKIND (r))
	    {
	      default:
		fprintf(fp,"d%d:\n", MTOKEN_SUBKIND (r));
	      case eMST_dim:
		if(MTOKEN_DIM_NEGATE(r)) fprintf (fp, "-");
		if (MTOKEN_DIM_NTTP (r))
		  print_decl1 (fp, MTOKEN_DIM_NTTP (r));
		if (MTOKEN_DIM_VALUE (r))
		  print_decl1 (fp, MTOKEN_DIM_VALUE (r));
		break;
	    }
	  break;
	case eMToken_unary:
	  switch (MTOKEN_SUBKIND (r))
	  {
	  case eMST_slashed:
	    fprintf (fp,"/");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,"/");
	    break;
	  case eMST_array:
	    fprintf (fp,"[");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,"]");
	    break;
	  case eMST_ltgt:
	    fprintf (fp,"<");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,">");
	    break;
	  case eMST_frame:
	    fprintf (fp,"{");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,"}");
	    break;
	  case eMST_rframe:
	    fprintf (fp,"(");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,")");
	    break;
	  case eMST_lexical_frame:
	    fprintf (fp,"'");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    fprintf (fp,"'");
	    break;
	  case eMST_throw:
	    fprintf (fp,"throw ");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    break;
	  case eMST_destructor:
	    fprintf (fp,"~");
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    break;
	  case eMST_element: case eMST_template_argument_list:
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    if (MTOKEN_CHAIN (r) != NULL)
	      fprintf (fp, ",");
	    break;
	  case eMST_oper: case eMST_scope:
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    break;
	  default:
	    fprintf (fp,"%d:",MTOKEN_SUBKIND (r));
	    print_decl1 (fp, MTOKEN_UNARY (r));
	    break;
	  }
	  break;
	case eMToken_binary:
	  switch (MTOKEN_SUBKIND (r))
	  {
	  default:
	    fprintf (fp,"b:%d:", MTOKEN_SUBKIND (r));
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp," ");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_coloncolon:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp,"::");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_assign:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp,"=");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    fprintf (fp,"}");
	    break;
	  case eMST_templateparam: case eMST_nonetypetemplateparam:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_exp:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp,"e");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_combine: case eMST_ecsu:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp," ");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_based:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp," ");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  case eMST_initfield:
	    print_decl1 (fp, MTOKEN_BINARY_LEFT (r));
	    fprintf (fp," ");
	    print_decl1 (fp, MTOKEN_BINARY_RIGHT (r));
	    break;
	  }
	  break;
	default:
	  break;
      }
      r = MTOKEN_CHAIN (r);
    }
}

void
print_decl (FILE *fp, uMToken *r)
{
  if (r)
    print_decl1(fp, r);
  fprintf (fp,"\n");
}

#if defined (TEST)

static const char *szTest[]= {
	"??_C@_0BL@CNOONJFP@?$GAplacement?5delete?5closure?8?$AA@",
	"??_C@_07LFCOJCAC@__int64?$AA@",
	"?outputString@UnDecorator@@0PADA",
	"?outputString@UnDecorator@@1PADA",
	"?outputString@UnDecorator@@2PADA",
	"?outputString@UnDecorator@@3PADA",
	"?outputString@UnDecorator@@4PADA",
	"?outputString@UnDecorator@@5PADA",
	"?outputString@UnDecorator@@6PADA",
	"?outputString@UnDecorator@@7PADA",
	"?outputString@UnDecorator@@8PADA",
	"?outputString@UnDecorator@@9PADA",
	"??_5DName@@QAEAAV0@ABV0@@Z",
	"??_7pDNameNode@@6B@",
	"??_7exception@@6B@",
	"??_Ebad_cast@@UAEPAXI@Z",
	"??_Fbad_cast@@QAEXXZ",
	"??_Gbad_cast@@UAEPAXI@Z",
	"??_M@YGXPAXIHP6EX0@Z@Z",
	"??_R1A@?0A@A@exception@@8",
	"??_R2exception@@8","??_R3exception@@8",
	"??_R0?AVexception@@@8","??_R4exception@@6B@",
	"??0Block@HeapManager@@QAE@XZ",
	"??0DNameNode@@IAE@XZ",
	"??0__non_rtti_object@@QAE@ABV0@@Z",
	"??1bad_typeid@@UAE@XZ",
	"??2@YAPAXIAAVHeapManager@@H@Z",
	"??3@YAXPAX@Z",
	"??4DName@@QAEAAV0@ABV0@@Z",
	"??4DName@@QAEAAV0@W4DNameStatus@@@Z",
	"??4DName@@QAEAAV0@D@Z",
	"??4DName@@QAEAAV0@PBD@Z",
	"??YReplicator@@QAEAAV0@ABVDName@@@Z",
	"??H@YA?AVDName@@W4DNameStatus@@ABV0@@Z",
	"??H@YA?AVDName@@PBDABV0@@Z",
	"__CallSettingFrame@12",
	"??3@YAXPAX@Z",
	"??_Etype_info@@UAEPAXI@Z",
	"??_Gtype_info@@UAEPAXI@Z",
	"??1type_info@@UAE@XZ",
	"??_R1A@?0A@A@type_info@@8",
	"??_R2type_info@@8",
	"??_R0?AVtype_info@@@8",
	"??_R4type_info@@6B@",
	"??_7type_info@@6B@",
	"??_Gtype_info@@UAEPAXI@Z",
	"??8type_info@@QBEHABV0@@Z",
/*	"@foo@bar@$bctr$q", borland */
	NULL
};

int main()
{
  int i;
  uMToken *h;
  for (i = 0; szTest[i]!=NULL; i++)
  {
    h = decode_ms_name (szTest[i]);
    print_decl (stderr, h);
    release_tok (h);
  }
  return 0;
}
#endif
