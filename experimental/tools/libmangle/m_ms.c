#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

#include "m_token.h"
#include "m_ms.h"

static uMToken *m_combine (uMToken *l, uMToken *r);
static uMToken *m_type (const char *typname);
static uMToken *m_cv (const char *cv);
static uMToken *m_coloncolon (uMToken *l, uMToken *r);
static uMToken *m_element (uMToken *el);
static uMToken *m_array (uMToken *dim);
static uMToken *m_scope (uMToken *n);
static uMToken *m_oper (uMToken *n);
static uMToken *m_name (const char *str);

static uMToken *get_decorated_name (sMSCtx *c);
static uMToken *get_string_literal_type (sMSCtx *c);
static uMToken *get_symbol_name (sMSCtx *c);
static uMToken *get_zbuf_name (sMSCtx *c, int updateCache);
static uMToken *get_dimension_signed (sMSCtx *c);
static uMToken *get_dimension (sMSCtx *c,int fSigned, int fNegate);
static uMToken *extract_name (sMSCtx *c, char term);
static uMToken *get_scope (sMSCtx *c);
static uMToken *get_template_name (sMSCtx *c, int fReadTerminator);
static uMToken *get_operator_name (sMSCtx *c, int fIsTemplate, int *pfReadTemplateArguments);
static uMToken *get_template_argument_list (sMSCtx *c);
static uMToken *get_lexical_frame(sMSCtx *c);
static uMToken *get_string_encoding (sMSCtx *c, int wantBody);
static uMToken *get_template_constant (sMSCtx *c);
static uMToken *get_data_type (sMSCtx *c);
static uMToken *get_indirect_data_type(sMSCtx *c, uMToken *superType, char prType, uMToken *cvType, int thisFlag);
static uMToken *get_primary_data_type (sMSCtx *c, uMToken *superType);
static uMToken *get_based_type (sMSCtx *c);
static uMToken *get_scoped_name (sMSCtx *c);
static uMToken *get_basic_data_type (sMSCtx *c, uMToken *superName);
static uMToken *get_pointer_reference_type (sMSCtx *c, uMToken *cvType, uMToken *superType, char ptrChar);
static uMToken *get_indirect_function_type (sMSCtx *c, uMToken *superType);
static uMToken *get_pointer_reference_data_type (sMSCtx *c, uMToken *superType,int isPtr);
static uMToken *get_ECSU_data_type (sMSCtx *c);
static uMToken *get_enum_size_type (sMSCtx *c);
static uMToken *get_this_type (sMSCtx *c);
static uMToken *get_calling_convention (sMSCtx *c);
static uMToken *get_throw_types (sMSCtx *c);
static uMToken *get_argument_types (sMSCtx *c);
static uMToken *get_return_type (sMSCtx *c);
static uMToken *get_array_type (sMSCtx *c, uMToken *superType);
static uMToken *get_argument_list (sMSCtx *c);
static uMToken *compose_decl (sMSCtx *c, uMToken *symbol);
static uMToken *get_vftable_type (sMSCtx *c, uMToken *superType);
static int get_number_of_dimensions (sMSCtx *c);
static int get_encoded_type (sMSCtx *);
static uMToken *get_vdisp_map_type (sMSCtx *c, uMToken *superType);
static uMToken *get_ext_data_type (sMSCtx *c, uMToken *superType);

uMToken *
decode_ms_name (const char *name)
{
  sMSCtx ctx;
  sCached ZNameList, ArgList, TempArgList;
  uMToken *ret = NULL;
  if (!name || *name == 0)
    return NULL;
  
  memset (&ctx, 0, sizeof (ctx));
  memset (&ZNameList, 0, sizeof (ZNameList));
  memset (&ArgList, 0, sizeof (ArgList));
  memset (&TempArgList, 0, sizeof (TempArgList));
  ctx.name = name;
  ctx.end = name + strlen (name);
  ctx.pos = ctx.name;

  ctx.pZNameList = &ZNameList;
  ctx.pArgList = &ArgList;
  ctx.pTemplateArgList = &TempArgList;
  
  fprintf(stderr,"decode_ms_name: %s\n", name);

  if (name[0] == '?')
    {
      if (name[1] == '@')
        {
          SKIP_CHAR(&ctx,2);
          ret = get_decorated_name (&ctx);
          /* CV: ??? */
        }
      else if (name[1] == '$')
        {
           if (!(ret = get_template_name (&ctx, 0)))
             ret = get_decorated_name (&ctx);
        }
      else
        ret = get_decorated_name (&ctx);
    }
  else
    ret = get_decorated_name (&ctx);

  if (!ret)
    {
      ret = gen_name (eMST_unmangled, name);
    }

  return ret;
}

int
encode_ms_name (uMToken *tok)
{
  return 0;
}

static uMToken *
get_decorated_name (sMSCtx *c)
{
  uMToken *n = NULL;
  uMToken *d = NULL;
  int isudc;
  if (GET_CHAR (c) != '?')
    {
      if (GET_CHAR (c) == 0)
         c->err = 1;
      fprintf (stderr,"*** get_decorated_name %s empty\n", c->name);
      return NULL;
    }
  INC_CHAR (c);
  
  n = get_symbol_name (c);
  isudc = (n && (MTOKEN_FLAGS (n) & MTOKEN_FLAGS_UDC)) ? 1 : 0;
  if (c->err)
    return n;
  if (GET_CHAR (c) != 0 && GET_CHAR (c) != '@')
    {
      d = get_scope (c);
      if (d)
        {
	  if (c->fExplicitTemplateParams == 0)
	    n = m_coloncolon (d, n);
	  else
	    {
	      c->fExplicitTemplateParams = 0;
	      n = m_combine ( n, d);
	      if (GET_CHAR (c) != '@')
	        {
		  d = get_scope (c);
		  n = m_coloncolon (d, n);
	        }
	    }
        }
    }
  if (!n)
    return n;
  if (isudc)
    MTOKEN_FLAGS (n) |= MTOKEN_FLAGS_UDC;
  if (MTOKEN_FLAGS (n) & MTOKEN_FLAGS_NOTE)
    return n;
  if (GET_CHAR (c) != 0)
    {
      if (GET_CHAR (c) != '@')
	return NULL;
      INC_CHAR (c);
    }
  return compose_decl (c, n);
}


static uMToken *
get_symbol_name (sMSCtx *c)
{
  if (GET_CHAR (c) != '?')
    return get_zbuf_name (c, 1);
  if (c->pos[1] == '$')
    return get_template_name (c, 1);
  INC_CHAR (c);
  return get_operator_name (c, 0, NULL);
}

static uMToken *
get_zbuf_name (sMSCtx *c, int updateCache)
{
  const char *ntmp;
  uMToken *dim, *ret = NULL, *n = NULL;
  
  if (GET_CHAR(c) >= '0' && GET_CHAR (c) <= '9')
    {
      ret = c->pZNameList->arr[GET_CHAR (c) - '0'];
      INC_CHAR (c);
      return ret;
    }
  if (GET_CHAR (c) == '?')
    {
      n = get_template_name (c, 0);
      if (GET_CHAR (c) == '@')
        INC_CHAR (c);
      if (updateCache && c->pZNameList->count < 10)
        {
          c->pZNameList->arr[c->pZNameList->count] = n;
          c->pZNameList->count += 1;
        }
      return n;
    }
  ntmp="template-parameter-";
  if (!strncmp(c->pos,"template-parameter-",19))
    SKIP_CHAR (c,19);
  else
    {
      ntmp="generic-type-";
      if (!strncmp(c->pos, "generic-type-", 13))
        SKIP_CHAR (c,13);
      else
        {
          n = extract_name (c, '@');
          if (updateCache && c->pZNameList->count < 10)
            {
              c->pZNameList->arr[c->pZNameList->count] = n;
              c->pZNameList->count += 1;
            }
          return n;
        }
    }
  dim=get_dimension_signed (c);
  n=chain_tok (gen_name (eMST_templargname, ntmp), dim);
  if (updateCache && c->pZNameList->count < 10)
    {
      c->pZNameList->arr[c->pZNameList->count] = n;
      c->pZNameList->count += 1;
    }
  return n;
}

static uMToken *
get_dimension_signed (sMSCtx *c)
{
   if (GET_CHAR (c) == 0)
     {
       c->err=1;
       return NULL;
     }
   if (GET_CHAR (c) != '?')
     return get_dimension (c, 0, 0);
   INC_CHAR (c);
   return get_dimension (c, 0, 1/* be negative*/);
}

static uMToken *
get_dimension (sMSCtx *c, int fSigned, int fNegate)
{
  const char *non_tt_param=NULL;
  uint64_t v_r = 0ULL, v1;
  
  if (GET_CHAR (c) == 'Q')
    {
      INC_CHAR (c);
      non_tt_param="'non-type-template-parameter";
    }
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return NULL;
    }
  if (GET_CHAR (c) >= '0' && GET_CHAR (c) <= '9')
    {
      uint64_t v = (uint64_t) ((GET_CHAR (c)-'0') + 1);
      INC_CHAR (c);
      return gen_dim (eMST_dim,v, non_tt_param, fSigned, fNegate);
    }

  while (GET_CHAR (c) != '@')
    {
      if (GET_CHAR (c) == 0)
        {
          c->err = 2;
          return NULL;
        }
      if (GET_CHAR (c) < 'A' || GET_CHAR (c) > 'P')
        {
          c->err = 1;
          return NULL;
        }
      v1=(uint64_t) (GET_CHAR (c) - 'A');
      v_r = v_r*10ULL + v1;
      INC_CHAR (c);
    }
  if (GET_CHAR (c) !='@')
    {
      c->err = 1;
      return NULL;
    }
  INC_CHAR (c);
  return gen_dim (eMST_dim,v_r, non_tt_param, fSigned, fNegate);
}

static uMToken *
extract_name (sMSCtx *c, char term)
{
  uMToken *ret;
  char *txt;
  size_t len;
  const char *sv = c->pos;
  while (GET_CHAR (c) != 0 && GET_CHAR (c) != term)
    {
      INC_CHAR (c);
    }
  if (GET_CHAR (c) != '@')
    {
      c->err = 1;
      return NULL;
    }
  len = (size_t) (c->pos - sv);
  txt = (char *) malloc (len + 1);
  memcpy (txt, sv, len);
  txt[len] = 0;
  INC_CHAR (c);
  ret = m_name (txt);
  free (txt);
  return ret;
}

static uMToken *
get_scope (sMSCtx *c)
{
  uMToken *n = NULL;

  while (1)
  {
    if (GET_CHAR (c) == 0 || GET_CHAR (c) == '@')
      break;
    if (c->fExplicitTemplateParams != 0 && !c->fGetTemplateArgumentList)
      return n;
    if (GET_CHAR (c) == '?')
      {
        INC_CHAR (c);
        if (GET_CHAR (c) == '$')
          {
            DEC_CHAR (c);
	    n = m_coloncolon (get_zbuf_name (c, 1), n);
          }
        else if (GET_CHAR (c) == '%' || GET_CHAR (c) == 'A')
          {
            while (GET_CHAR (c) != '@')
              INC_CHAR (c);
            INC_CHAR (c);
            n = m_coloncolon (m_name ("anonymous_namespace"), n);
          }
        else if (GET_CHAR (c) == '?')
          {
            if (c->pos[1] == '_' && c->pos[2] == '?')
              {
                INC_CHAR (c);
		n = m_coloncolon (get_operator_name (c, 0,NULL), n);
                if (GET_CHAR (c) == '@')
                  INC_CHAR (c);
              }
            else
	      {
		n = m_coloncolon (gen_unary (eMST_slashed, get_decorated_name (c)), n);
	      }
          }
        else if (GET_CHAR (c) == 'I')
          {
            INC_CHAR (c);
	    n = m_coloncolon (m_array (get_zbuf_name (c, 1)), n);
          }
        else
	  n = m_coloncolon (get_lexical_frame (c), n);
      }
    else
      n = m_coloncolon (get_zbuf_name (c, 1), n);
  }
  if (n)
    n = m_scope (n);
  if (GET_CHAR (c))
    {
      if (GET_CHAR (c) == '@')
        return n;
    }
  else
    {
      c->err = 2;
      return n;
    }
    return n;
}

static uMToken *
get_template_name (sMSCtx *c, int fReadTerminator)
{
  sCached rep1;
  sCached rep2;
  sCached rep3;
  sCached *svZName,*svArgList,*svTempArgList;
  uMToken *n = NULL;
  int fFlag = 0;
  
  if (GET_CHAR (c) !='?' || c->pos[1] != '$')
    return NULL;
  memset (&rep1, 0, sizeof (rep1));
  memset (&rep2, 0, sizeof (rep2));
  memset (&rep3, 0, sizeof (rep3));
  
  svTempArgList = c->pTemplateArgList;
  svArgList = c->pArgList;
  svZName = c->pZNameList;
  
  SKIP_CHAR(c,2);
  
  c->pArgList=&rep1;
  c->pZNameList=&rep2;
  c->pTemplateArgList=&rep3;

  if (GET_CHAR (c) == '?')
    {
      INC_CHAR (c);
      n = get_operator_name (c, 1, &fFlag);
    }
  else
    n = get_zbuf_name (c, 1);
  if (!n)
    c->fExplicitTemplateParams = 1;
  if (!fFlag)
    {
      n = get_template_argument_list (c);
      n = gen_unary (eMST_ltgt, n);
      if (fReadTerminator)
        INC_CHAR (c);
    }
  c->pArgList = svArgList;
  c->pZNameList = svZName;
  c->pTemplateArgList = svTempArgList;
  return n;
}

static uMToken *
get_operator_name (sMSCtx *c, int fIsTemplate, int *pfReadTemplateArguments)
{
  const char *svName;
  char ch = GET_CHAR (c);
  uMToken *n = NULL,*h = NULL;
  
  if (!ch)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  switch(ch)
    {
      case '0': case '1':
        if (fIsTemplate)
          {
            h = gen_unary (eMST_ltgt, get_template_argument_list (c));
            if (pfReadTemplateArguments)
              *pfReadTemplateArguments = 1;
            ch = GET_CHAR (c);
            if (ch == 0)
              return m_oper (h);
            INC_CHAR (c);
          }
        svName = c->pos;
        n = get_zbuf_name (c, 0);
        c->pos = svName;
        if (n && ch == '1')
          n=gen_unary (eMST_destructor, n);
        n = chain_tok (n, h);
        return m_oper (n);
      case '2':
        return m_oper (gen_name (eMST_opname, "operator new"));
      case '3':
        return m_oper (gen_name (eMST_opname, "operator delete"));
      case '4':
        return m_oper (gen_name (eMST_opname, "operator ="));
      case '5':
        return m_oper (gen_name (eMST_opname, "operator >>"));
      case '6':
        return m_oper (gen_name (eMST_opname, "operator <<"));
      case '7':
        return m_oper (gen_name (eMST_opname, "operator !"));
      case '8':
        return m_oper (gen_name (eMST_opname, "operator =="));
      case '9':
        return m_oper (gen_name (eMST_opname, "operator !="));
      case 'A':
        return m_oper (gen_name (eMST_opname, "operator []"));
      case 'B':
        n = gen_name (eMST_opname,  "operator");
        MTOKEN_FLAGS(n) |= MTOKEN_FLAGS_UDC;
        n = m_oper (n);
        MTOKEN_FLAGS(n) |= MTOKEN_FLAGS_UDC;
        return n;
      case 'C':
        return m_oper (gen_name (eMST_opname, "operator ->"));
      case 'D':
        return m_oper (gen_name (eMST_opname, "operator *"));
      case 'E':
        return m_oper (gen_name (eMST_opname, "operator ++"));
      case 'F':
        return m_oper (gen_name (eMST_opname, "operator --"));
      case 'G':
        return m_oper (gen_name (eMST_opname, "operator -"));
      case 'H':
        return m_oper (gen_name (eMST_opname, "operator +"));
      case 'I':
        return m_oper (gen_name (eMST_opname, "operator &"));
      case 'J':
        return m_oper (gen_name (eMST_opname, "operator ->*"));
      case 'K':
        return m_oper (gen_name (eMST_opname, "operator /"));
      case 'L':
        return m_oper (gen_name (eMST_opname, "operator %"));
      case 'M':
        return m_oper (gen_name (eMST_opname, "operator <"));
      case 'N':
        return m_oper (gen_name (eMST_opname, "operator <="));
      case 'O':
        return m_oper (gen_name (eMST_opname, "operator >"));
      case 'P':
        return m_oper (gen_name (eMST_opname, "operator >="));
      case 'Q':
        return m_oper (gen_name (eMST_opname, "operator ,"));
      case 'R':
        return m_oper (gen_name (eMST_opname, "operator ()"));
      case 'S':
        return m_oper (gen_name (eMST_opname, "operator ~"));
      case 'T':
        return m_oper (gen_name (eMST_opname, "operator ^"));
      case 'U':
        return m_oper (gen_name (eMST_opname, "operator |"));
      case 'V':
        return m_oper (gen_name (eMST_opname, "operator &&"));
      case 'W':
        return m_oper (gen_name (eMST_opname, "operator ||"));
      case 'X':
        return m_oper (gen_name (eMST_opname, "operator *="));
      case 'Y':
        return m_oper (gen_name (eMST_opname, "operator +="));
      case 'Z':
        return m_oper (gen_name (eMST_opname, "operator -="));
      case '_':
        break;
      default:
        fprintf (stderr, " *** get_operator_name unknown '%c'\n", ch);
        return NULL;
    }
  ch = GET_CHAR (c);
  if (! ch)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  switch(ch)
    {
      case '_':
        ch = GET_CHAR (c);
        INC_CHAR (c);
        switch (ch)
          {
            case 'A':
              return m_oper (gen_name (eMST_opname, "__man_vec_ctor"));
            case 'B':
              return m_oper (gen_name (eMST_opname, "__man_vec_dtor"));
            case 'C':
              return m_oper (gen_name (eMST_opname, "__ehvec_copy_ctor"));
            case 'D':
              return m_oper (gen_name (eMST_opname, "__ehvec_copy_ctor_vb"));
          }
        fprintf (stderr, " *** get_operator_name unknown '__%c'\n", ch);
        return NULL;

      case '0':
        return m_oper (gen_name (eMST_opname, "operator /="));
      case '1':
        return m_oper (gen_name (eMST_opname, "operator %="));
      case '2':
        return m_oper (gen_name (eMST_opname, "operator >>="));
      case '3':
        return m_oper (gen_name (eMST_opname, "operator <<="));
      case '4':
        return m_oper (gen_name (eMST_opname, "operator &="));
      case '5':
        return m_oper (gen_name (eMST_opname, "operator |="));
      case '6':
        return m_oper (gen_name (eMST_opname, "operator ^="));
      case '7':
        return m_oper (gen_name (eMST_vftable, "$vftable"));
      case '8':
        return m_oper (gen_name (eMST_vbtable, "$vbtable"));
      case '9':
        return m_oper (gen_name (eMST_vcall, "vcall"));
      case 'A':
        return m_oper (gen_name (eMST_opname,"typeof"));
      case 'B':
        return m_oper (gen_name (eMST_opname,"local_static_guard"));
      case 'C':
        n = get_string_encoding (c, 1);
        MTOKEN_FLAGS(n) |= MTOKEN_FLAGS_NOTE;
        return n;
      case 'D':
        return m_oper (gen_name (eMST_opname,"vbase_destructor"));
      case 'E':
        return m_oper (gen_name (eMST_opname,"__vecDelDtor"));
      case 'F':
        return m_oper (gen_name (eMST_opname,"__dflt_ctor_closure"));
      case 'G':
        return m_oper (gen_name (eMST_opname, "__delDtor"));
      case 'H':
        return m_oper (gen_name (eMST_opname, "__vec_ctor"));
      case 'I':
        return m_oper (gen_name (eMST_opname, "__vec_dtor"));
      case 'J':
        return m_oper (gen_name (eMST_opname, "__vec_ctor_vb"));
      case 'K':
        return m_oper (gen_name (eMST_opname, "$vdispmap"));
      case 'L':
        return m_oper (gen_name (eMST_opname, "__ehvec_ctor"));
      case 'M':
        return m_oper (gen_name (eMST_opname, "__ehvec_dtor"));
      case 'N':
        return m_oper (m_name ("__ehvec_ctor_vb"));
      case 'O':
        return m_oper (gen_name (eMST_opname, "__copy_ctor_closure"));
      case 'P':
        return gen_unary (eMST_udt_returning, get_operator_name (c, 0, NULL));
      case 'Q':
        return m_oper (gen_name (eMST_opname,  "operator 'EH'"));
      case 'R':
        ch = GET_CHAR (c);
        INC_CHAR (c);
        switch (ch)
          {
            case '0':
              h = gen_name (eMST_rtti,"$type_descriptor");
              return m_oper (m_combine (get_data_type (c) , h));
            case '1':
              h = gen_name (eMST_rtti, "base_class_descriptor");
              n = m_element (get_dimension_signed (c));
              n = chain_tok (n, m_element (get_dimension_signed (c)));
              n = chain_tok (n, m_element (get_dimension_signed (c)));
              n = chain_tok (n, m_element (get_dimension (c, 0, 0)));
	      n = gen_unary (eMST_frame, n);
              return m_oper (gen_binary (eMST_assign, h, n));
            case '2':
              return m_oper (gen_name (eMST_rtti,"base_class_array"));
            case '3':
	      return m_oper (gen_name (eMST_rtti,"class_hierarchy_descriptor"));
            case '4':
              return m_oper (gen_name (eMST_rtti,"complete_object_locator"));
          }
        DEC_CHAR (c);
        fprintf (stderr, " *** Unkown RTTI %c\n", ch);
        c->err = 2;
        return NULL;
      case 'S':
        return m_oper (gen_name (eMST_opname, "$locvftable"));
      case 'T':
        return m_oper (gen_name (eMST_opname, "__local_vftable_ctor_closure"));
      case 'U':
        n = gen_name (eMST_opname, "operator new[]");
        return m_oper (n);
      case 'V':
        n = gen_name (eMST_opname,  "operator delete[]");
        return m_oper (n);
      case 'W': /* omni callsig ??? */
      default:
        fprintf (stderr, " *** get_operator_name unknown '_%c'\n", ch);
        return NULL;
      case 'X':
        return m_oper (gen_name (eMST_opname,  "__placement_delete_closure"));
      case 'Y':
        return m_oper (gen_name (eMST_opname,  "__placement_arrayDelete_closure"));
      case '?':
        break;
    }
  ch = GET_CHAR (c);
  if (!ch)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  switch(ch)
    {
      case '0':
	m_combine (m_name ("using namespace"), get_string_encoding (c, 0));
        MTOKEN_FLAGS (n) |= MTOKEN_FLAGS_NOTE;
        return n;
    }
  fprintf (stderr, " *** get_operator_name unknown '__?%c'\n", ch);
  return NULL;
}

static uMToken *
get_template_argument_list (sMSCtx *c)
{
  uMToken *n = NULL;
  uMToken *h = NULL;
  int idx;
  int beFirst=1;
  c->fGetTemplateArgumentList = 1;
  do
    {
      if (GET_CHAR (c) == 0 || GET_CHAR (c) == '@')
        break;
      idx = (int) (GET_CHAR (c) - '0');
      if (GET_CHAR (c) >= '0' && GET_CHAR (c) <= '9')
        {
          h = c->pTemplateArgList->arr[idx];
          INC_CHAR (c);
        }
      else
        {
          const char *svPos = c->pos;
          if (GET_CHAR (c) =='X')
            {
              INC_CHAR (c);
              h = m_type ("void");
            }
          else if (GET_CHAR (c) == '$' && c->pos[1] != '$')
            {
              INC_CHAR (c);
              h = get_template_constant (c);
            }
          else if (GET_CHAR (c) == '?')
            {
              uMToken *sdim = get_dimension_signed (c);
              h = gen_binary (eMST_templateparam, m_name ("template-parameter"), sdim);
            }
          else
            h = get_primary_data_type (c, NULL);
          if ((int)(c->pos-svPos)>1 &&
              c->pTemplateArgList->count < 10)
            {
              c->pTemplateArgList->arr[c->pTemplateArgList->count] = h;
              c->pTemplateArgList->count += 1;
            }
        }
      h = m_element (h);
      if (beFirst)
        {
          n = h;
          beFirst = 0;
        }
      else
        {
          n = chain_tok (n, h);
        }
    }
  while (c->err == 0);
  c->fGetTemplateArgumentList = 0;
  if (n)
    n = gen_unary (eMST_template_argument_list, n);
  return n;
}

static uMToken *
get_lexical_frame (sMSCtx *c)
{
  return gen_unary (eMST_lexical_frame, get_dimension (c, 0, 0));
}

static uMToken *
get_string_encoding (sMSCtx *c, int wantBody)
{
  uMToken *length = NULL;
  uMToken *crc = NULL, *h = NULL;
  uMToken *typ = NULL;
  const char *svName;
  size_t len;
  char *hp;

  if (GET_CHAR (c) != '@') return NULL;
  INC_CHAR (c);
  typ = get_string_literal_type (c);
  length = get_dimension (c, 0, 0);
  crc = get_dimension (c, 0, 0);
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return NULL;
    }
  svName = c->pos;
  while (GET_CHAR (c) != 0)
    {
      if (GET_CHAR (c) == '@')
        break;
      INC_CHAR (c);
  }
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return NULL;
    }
  len = (size_t) (c->pos - svName);
  hp = (char *) malloc (len + 1);
  memcpy (hp, svName, len);
  hp[len] = 0;
  INC_CHAR (c);
  h = m_name (hp);
  free (hp);
  if (wantBody)
    h = m_combine (typ, m_combine(h, m_array (length)));
  return h;
}

static uMToken *
get_template_constant (sMSCtx *c)
{
  char ch;
  uMToken *n = NULL;
  uMToken *exp;

  ch = GET_CHAR(c);
  if (!ch)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  if (ch =='E')
    return get_decorated_name (c);
  if (ch > 'E' && ch <= 'J')
    {
      if (ch >= 'H' && ch <= 'J')
        {
          exp = m_element (get_decorated_name (c));
          if (!n) n = exp;
          else chain_tok (n, exp);
        }
      switch(ch)
        {
          case 'G': case 'J':
            exp = m_element (get_dimension_signed (c));
	    if (!n) n = exp;
	    else chain_tok (n, exp);
          case 'F': case 'I':
            exp = m_element (get_dimension_signed (c));
	    if (!n) n = exp;
	    else chain_tok (n, exp);
          case 'H':
            exp = m_element (get_dimension_signed (c));
	    if (!n) n = exp;
	    else chain_tok (n, exp);
            break;
        }
      return gen_unary (eMST_frame, n);
    }
  if (ch == 'Q' || ch == 'D')
    {
      n = get_dimension_signed (c);
      if (ch == 'D')
        return gen_binary (eMST_templateparam, m_name ("template-parameter"), n);
      return gen_binary (eMST_nonetypetemplateparam, m_name ("none-type-template-parameter"), n);
    }
  if (ch == '0')
    return get_dimension_signed (c);
  if (ch == '1')
    {
      if (GET_CHAR (c) != '@')
        return m_combine (m_cv ("&"), get_decorated_name (c));
      INC_CHAR (c);
      return m_name ("NULL");
    }
  if (ch != '2')
    {
      fprintf (stderr, " *** get_template_constant unknown '%c'\n", ch);
      return NULL;
    }
  n = get_dimension_signed (c);
  exp = get_dimension_signed (c);
  return gen_binary (eMST_exp, n, exp);
}

static uMToken *
get_data_type (sMSCtx *c)
{
  uMToken *n = NULL;
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return n;
    }
  if (GET_CHAR (c) == '?')
    {
      INC_CHAR (c);
      n = get_indirect_data_type (c, n, (char)0, NULL, 0);
      return get_primary_data_type (c, n);
    }
  if (GET_CHAR (c) != 'X')
    return get_primary_data_type (c, n);
  INC_CHAR (c);
  return m_combine (m_type ("void"), n);
}

static uMToken *
get_indirect_data_type (sMSCtx *c, uMToken *superType, char prType, uMToken *cvType, int thisFlag)
{
  uMToken *n = NULL, *n1 = NULL, *n2 = NULL;
  int state;

  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      if (thisFlag != 0)
        return NULL;
      if (!superType)
        {
          if (!cvType)
            return NULL;
          return cvType;
        }
      if (MTOKEN_FLAGS (superType) & MTOKEN_FLAGS_PTRREF)
        return superType;
      if (!cvType)
        return superType;
      return m_combine (cvType, superType);
    }
  if (GET_CHAR (c) == '$')
    {
      INC_CHAR (c);
      if (GET_CHAR (c) == 'A')
        {
          n = m_cv ("__gc");
          INC_CHAR (c);
        }
      else if (GET_CHAR (c) == 'B')
        {
          n = m_cv ("__pin");
          INC_CHAR (c);
        }
      else
        {
          state = (int)(GET_CHAR (c) - '3')*16;
          INC_CHAR (c);
          state += (int)GET_CHAR (c);
          INC_CHAR (c);
          n = gen_value (eMST_gcarray, (uint64_t) state, 0, 4);
          if (superType)
            {
              if (!(MTOKEN_FLAGS (superType) & MTOKEN_FLAGS_ARRAY))
                superType = gen_unary (eMST_rframe, superType);
              n=m_combine (superType, n);
            }
          INC_CHAR (c);
          return n;
        }
    }
  state = (GET_CHAR (c) - (GET_CHAR (c) < 'A' ? 0x16 : 0x41));
  while (1)
    {
      if (state == 4)
        n1 = m_combine (n1, m_cv ("__ptr64"));
      else if (state == 5)
	n2 = m_combine (n2, m_cv ("__unaligned"));
      else if (state != 8)
        {
	  uMToken *ret = NULL;
          INC_CHAR (c);
          if (state > 31)
	    return NULL;
	  if (prType == '*')
	    ret = m_cv ("*");
	  else if (prType == '&')
	    ret = m_cv ("&");

	  ret = m_combine (n ,ret);
	  ret = m_combine (ret, n1);
	  ret = m_combine (n2, ret);
          if ((state & 0x10) != 0)
            {
              if (thisFlag != 0)
		return NULL;
              if (prType)
                {
                  if (GET_CHAR (c) == 0)
		    {
		      c->err = 2;
		      return ret;
		    }
                  else
		    {
		      if (ret)
			ret = gen_binary (eMST_coloncolon , get_scope (c), ret);
		      else
			ret = get_scope (c);
		    }
                  if (GET_CHAR (c) == 0) c->err = 2;
                  else
                    {
		      char ch = GET_CHAR (c);
                      INC_CHAR (c);
                      if (ch != '@')
			return NULL;
                    }
                }
              else if (GET_CHAR (c) == 0)
		c->err = 2;
              else
                {
                  ret = get_scope (c);
                  if (GET_CHAR (c) != 0)
                    {
		      char ch = GET_CHAR (c);
                      INC_CHAR (c);
                      if (ch != '@')
			return NULL;
                    }
                  else
		    c->err = 2;
                }
            }
          if ((state&0xc)==0xc)
            {
              if (thisFlag != 0)
		return NULL;
              ret = m_combine (get_based_type (c), ret);
            }
          if ((state & 2) != 0)
	    ret = m_combine (m_cv ("volatile"), ret);
          if ((state & 1) != 0)
	    ret = m_combine (m_cv ("const"), ret);
          if (thisFlag != 0)
            {
	      if (!ret)
		ret = m_name ("");
	      MTOKEN_FLAGS(ret) |= MTOKEN_FLAGS_PTRREF;
              return ret;
            }
          if (!superType)
            {
              if (cvType)
		ret = m_combine (ret, cvType);
	      if (!ret)
		ret = m_name ("");
              MTOKEN_FLAGS(ret) |= MTOKEN_FLAGS_PTRREF;
              return ret;
            }
          if (MTOKEN_FLAGS(superType) & MTOKEN_FLAGS_PTRREF)
            {
              if (cvType)
                {
		  ret = m_combine (ret, cvType);
		  ret = m_combine (ret, superType);
                  MTOKEN_FLAGS(ret) |= MTOKEN_FLAGS_PTRREF;
                  return ret;
                }
            }
          if (!(MTOKEN_FLAGS(superType)&MTOKEN_FLAGS_ARRAY))
	    ret = m_combine (ret, superType);
          else
	    ret = superType;
          MTOKEN_FLAGS(ret) |= MTOKEN_FLAGS_PTRREF;
          return ret;
        }
      else
        {
          if (!n1)
            n1 = m_cv ("__restrict");
          else
            n1 = m_combine (n1, m_cv ("__restrict"));
        }
      INC_CHAR (c);
      state=GET_CHAR (c)-(GET_CHAR (c) < 'A' ? 0x16 : 0x41);
    }
}

static uMToken *
get_primary_data_type (sMSCtx *c, uMToken *superType)
{
  uMToken *superName = NULL;
  uMToken *cvType = NULL;
  switch(GET_CHAR (c))
    {
      case 0:
	c->err = 2;
	return superType;
      case 'B':
	cvType = m_cv ("volatile");
	/* fall through */
      case 'A':
	superName = superType;
	if (!superName)
	  superName = m_name ("");
	MTOKEN_FLAGS (superName) |= MTOKEN_FLAGS_PTRREF;
	INC_CHAR (c);
	return get_pointer_reference_type (c, cvType, superName, '&');
      case '$':
	if (c->pos[1] == '$')
	  {
	    SKIP_CHAR (c, 2);
	    break;
	  }
	if (c->pos[1] == 0)
	  {
	    c->err = 2;
	    return NULL;
	  }
	fprintf (stderr, " *** get_primary_data_type '$%c' unknown\n", c->pos[1]);
	return NULL;
      default:
	return get_basic_data_type (c, superType);
    }
  switch(GET_CHAR (c))
    {
      case 0:
	c->err = 2;
	return superType;
      case 'A':
	INC_CHAR (c);
	return get_indirect_function_type (c, superType);
      case 'B':
	INC_CHAR (c);
	return get_pointer_reference_data_type (c, superType, 1);
      case 'C':
	INC_CHAR (c);
	return get_basic_data_type (c, get_indirect_data_type (c, superType, (char)0, superName, 0));
    }
  fprintf (stderr, " *** get_primary_data_type '$$%c' unknown\n", GET_CHAR (c));
  return NULL;
}

static uMToken *
get_based_type (sMSCtx *c)
{
  uMToken *n = m_cv ("__based");
  uMToken *p = NULL;
  char ch;

  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return gen_binary (eMST_based, n, NULL);
    }
  ch = GET_CHAR (c);
  INC_CHAR (c);
  switch(ch)
    {
      case '0':
	p = m_type ("void");
	break;
      case '2':
	p = get_scoped_name (c);
	break;
      case '5':
	fprintf (stderr, " *** get_based_type unknown '%c'\n", ch);
	return NULL;
      default:
	fprintf (stderr, " *** get_based_type unknown '%c' (ignored)\n", ch);
	break;
    }
  return gen_binary (eMST_based, n, p);
}

static uMToken *
get_scoped_name (sMSCtx *c)
{
  uMToken *n = NULL;
  n = get_zbuf_name (c, 1);
  if (n && GET_CHAR (c) != 0)
    {
      if (GET_CHAR (c) =='@')
        {
	  INC_CHAR (c);
	  return n;
        }
      n = m_coloncolon (get_scope (c), n);
    }
  if (GET_CHAR (c) == '@')
    {
      INC_CHAR (c);
      return n;
    }
  if (GET_CHAR (c) != 0)
      return n;
  c->err = 2;
  return n;
}

static uMToken *
get_basic_data_type (sMSCtx *c, uMToken *superName)
{
  uMToken *bTyp = NULL;
  uMToken *cvName = NULL;
  uMToken *arType = NULL;
  uMToken *tmp = NULL;
  char svChar,svChar1;
  int flags;

  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return superName;
    }
  svChar1 = GET_CHAR (c);
  INC_CHAR (c);
  flags=~0;
  switch (svChar1)
    {
     case 'M':
       bTyp = m_type ("float");
       break;
     case 'C':
       bTyp = m_type ("signed char");
       break;
     case 'D':
       bTyp = m_type ("char");
       break;
     case 'E':
       bTyp = m_type ("unsigned char");
       break;
     case 'F':
       bTyp = m_type ("short");
       break;
     case 'G':
       bTyp = m_type ("unsigned short");
       break;
     case 'H':
       bTyp = m_type ("int");
       break;
     case 'I':
       bTyp = m_type ("unsigned int");
       break;
     case 'J':
       bTyp = m_type ("long");
       break;
     case 'K':
       bTyp = m_type ("unsigned long");
       break;
     case 'N':
       bTyp = m_type ("double");
       break;
     case 'O':
       bTyp = m_type ("long double");
       break;
     case 'P':
       return get_pointer_reference_type (c, bTyp, superName, '*');
     case 'Q':
       if (!superName)
	 bTyp = m_cv ("const");
       return get_pointer_reference_type (c, bTyp, superName, '*');
     case 'R':
       if (!superName)
	 bTyp = m_cv ("volatile");
       return get_pointer_reference_type (c, bTyp, superName, '*');
     case 'S':
       if (!superName)
         {
	   bTyp = m_cv ("const");
	   bTyp = m_combine (bTyp, m_cv ("volatile"));
         }
       return get_pointer_reference_type (c, bTyp, superName, '*');
     case '_':
       svChar = GET_CHAR (c);
       INC_CHAR (c);
       switch(svChar)
         {
           case 'N':
	     bTyp = m_type ("bool");
	     break;
	   case 'O':
	     if (!superName)
	       superName = m_name ("");
	     cvName=superName;
	     MTOKEN_FLAGS (cvName) |= MTOKEN_FLAGS_ARRAY;
	     arType = get_pointer_reference_type (c, bTyp, cvName, 0);
	     if (!(MTOKEN_FLAGS (arType)&MTOKEN_FLAGS_ARRAY))
	       arType = m_combine (arType, m_array (NULL));
	     return arType;
	   case 'W':
	     bTyp = m_type ("wchar_t");
	     break;
	   case 'X':
	   case 'Y':
	     DEC_CHAR (c);
	     if (!(bTyp = get_ECSU_data_type (c)))
	       return NULL;
	     break;
	   case 'D':
	     bTyp = m_type ("__int8");
	     break;
	   case 'E':
	     bTyp = m_type ("unsigned __int8");
	     break;
	   case 'F':
	     bTyp = m_type ("__int16");
	     break;
	   case 'G':
	     bTyp = m_type ("unsigned __int16");
	     break;
	   case 'H':
	     bTyp = m_type ("__int32");
	     break;
	   case 'I':
	     bTyp = m_type ("unsigned __int32");
	     break;
	   case 'J':
	     bTyp = m_type ("__int64");
	     break;
	   case 'K':
	     bTyp = m_type ("unsigned __int64");
	     break;
	   case 'L':
	     bTyp = m_type ("__int128");
	     break;
	   case 'M':
	     bTyp = m_type ("unsigned");
	     break;
	   case '$':
	     bTyp = get_basic_data_type (c, superName);
	     return m_combine (m_cv ("__w64"), bTyp);
	   default:
	     fprintf (stderr, " *** get_basic_data_type unknown '_%c' (ignored).\n", svChar);
	     bTyp = m_type ("UNKNOWN");
	     break;
         }
       break;
     default:
       DEC_CHAR (c);
       bTyp = get_ECSU_data_type (c);
       if (!bTyp)
	 return bTyp;
       break;
    }
  if (superName)
    bTyp = m_combine (bTyp, superName);
  return bTyp;
}

static uMToken *
get_pointer_reference_type (sMSCtx *c, uMToken *cvType, uMToken *superType, char ptrChar)
{
  uMToken *n = NULL;
  if (ptrChar == '&')
    n = m_cv ("&");
  else if (ptrChar == '*')
    n = m_cv ("*");
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      if (cvType)
        {
	  if (!n)
	    n = cvType;
	  else
	    n = m_combine (n, cvType);
        }
      if (superType)
	n = m_combine (n, superType);
      return n;
    }
  if (GET_CHAR (c) < '6' || GET_CHAR (c) > '9')
    {
      if (GET_CHAR (c) != '_')
	return get_pointer_reference_data_type (c,
	  get_indirect_data_type (c, superType, ptrChar, cvType, 0),(ptrChar=='*' ? 1 : 0));
    }
  if (cvType)
    {
      if (!superType || !(MTOKEN_FLAGS (superType)&MTOKEN_FLAGS_PTRREF))
        {
	  if (!n)
	    n = cvType;
	  else
	    n = m_combine (n, cvType);
        }
    }
  if (superType)
    {
      if (!n)
	n = superType;
      else
	n = m_combine (n, superType);
    }
  return get_indirect_function_type (c, n);
}

static uMToken *
get_indirect_function_type (sMSCtx *c, uMToken *superType)
{
  uMToken *retType = NULL;
  uMToken *n1 = NULL, *n2 = NULL;
  int flag;
  int cidx;
  char ch = GET_CHAR (c);
  if (ch == 0)
    {
      c->err = 2;
      return superType;
    }
  if (ch != '_' && (ch < '6' || ch > '9'))
    return NULL;
  cidx = (int) (ch - '6');
  INC_CHAR (c);
  if (ch == '_')
    {
      ch = GET_CHAR (c);
      if (ch == 0)
        {
	  c->err = 2;
	  return superType;
        }
      if (ch < 'A' || ch > 'D')
	return NULL;
      cidx=(int)(ch - 'A') + 4;
      INC_CHAR (c);
    }
  n2 = superType;
  flag = cidx & 2;
  if (flag)
    {
      ch = GET_CHAR (c);
      if (ch == 0)
        {
	  c->err = 2;
	  return n2;
        }
      n2 = m_coloncolon (get_scope (c), n2);
      if (GET_CHAR (c) == 0)
        {
	  c->err = 2;
	  return n2;
        }
      if (GET_CHAR (c) != '@')
	return NULL;
      INC_CHAR (c);
      n1 = get_this_type (c);
    }
  if (cidx & 4)
    n2 = m_combine (get_based_type (c), n2);
  n2 = m_combine (get_calling_convention (c), n2);
  if (superType)
    n2 = gen_unary (eMST_rframe, n2);
  retType = get_return_type (c);
  n2 = m_combine (n2, gen_unary (eMST_rframe, get_argument_types (c)));
  if (flag)
    n2 = m_combine (n2, n1);
  n2 = m_combine (n2, get_throw_types (c));
  return m_combine (retType, n2);
}

static uMToken *
get_pointer_reference_data_type (sMSCtx *c, uMToken *superType,int isPtr)
{
  uMToken *n = NULL;
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return superType;
    }
  
  if (isPtr && GET_CHAR (c) == 'X')
    {
      INC_CHAR (c);
      n = m_type ("void");
      if (superType)
	n = m_combine (n, superType);
      return n;
    }
  if (GET_CHAR (c) == 'Y')
    {
      INC_CHAR (c);
      return get_array_type (c, superType);
    }
  if (GET_CHAR (c) != '_')
    return get_basic_data_type (c, superType);
  if (c->pos[1] != 'Z')
    return get_basic_data_type (c, superType);
  SKIP_CHAR (c, 2);
  n = m_cv ("__box");
  return m_combine (n, get_basic_data_type (c, superType));
}

static uMToken *
get_ECSU_data_type (sMSCtx *c)
{
  char ch = GET_CHAR (c);
  uMToken *n = NULL;

  if (!ch)
    {
      c->err = 2;
      return m_type ("no-ecsu");
    }
  INC_CHAR (c);
  switch (ch)
    {
      default:
	fprintf (stderr, " *** get_ECSU_data_type unknown %c\n", ch);
	n = m_type ("unknown ecsu");
	break;
      case 'T':
	n = m_type ("union");
	break;
      case 'U':
	n = m_type ("struct");
	break;
      case 'V':
	n = m_type ("class");
	break;
      case 'W':
	n = m_type ("enum");
	get_enum_size_type (c);
	break;
      case 'X':
	n = m_type ("coclass");
	break;
      case 'Y':
	n = m_type ("cointerface");
	break;
    }
  return gen_binary (eMST_ecsu, n, get_scoped_name (c));
}

static uMToken *
get_string_literal_type (sMSCtx *c)
{
  uMToken *n = NULL;
  char ch = GET_CHAR (c);
  if (ch == 0)
    {
      c->err = 2;
      return NULL;
    }
  if (ch == '_')
    {
      INC_CHAR (c);
      n = m_cv ("const"); 
    }
  ch = GET_CHAR (c);
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  switch (ch)
    {
      case '0':
	return m_combine(n, m_type ("char"));
      case '1':
	return m_combine(n, m_type ("wchar_t"));
    }
  fprintf (stderr, " *** get_string_literal_type unknown '_%c'\n", ch);
  return NULL;
}

static uMToken *
get_enum_size_type (sMSCtx *c)
{
  uMToken *n = NULL;
  switch (GET_CHAR (c))
    {
      case 0:
	c->err = 2;
	return NULL;
      case '0':
	n = m_type ("char");
	break;
      case '1':
	n = m_type ("unsigned char");
	break;
      case '2':
	n = m_type ("short");
	break;
      case '3':
	n = m_type ("unsigned short");
	break;
      case '4':
	n = m_type ("int");
	break;
      case '5':
	n = m_type ("unsigned int");
	break;
      case '6':
	n = m_type ("long");
	break;
      case '7':
	n = m_type ("unsigned long");
	break;
      default:
	fprintf (stderr, " *** get_enum_size_type unknown ,%c'\n", GET_CHAR (c));
	return NULL;
    }
  INC_CHAR (c);
  return n;
}

static uMToken *
get_this_type (sMSCtx *c)
{
    return get_indirect_data_type (c, NULL, (char)0, NULL, 1);
}

static uMToken *
get_calling_convention (sMSCtx *c)
{
  char ch = GET_CHAR (c);

  if (ch == 0)
    {
      c->err = 2;
      return NULL;
    }
  INC_CHAR (c);
  switch(ch)
    {
      case 'A': case 'B':
	return m_cv ("__cdecl");
      case 'C': case 'D':
	return m_cv ("__pascal");
      case 'E': case 'F':
	return m_cv ("__thiscall");
      case 'G': case 'H':
	return m_cv ("__stdcall");
      case 'I': case 'J':
	return m_cv ("__fastcall");
      case 'K': case 'L':
	return m_cv ("");
      case 'M':
	return m_cv ("__clrcall");
    }
  fprintf (stderr, " *** get_calling_convention ,%c' unknown.\n", ch);
  return NULL;
}

static uMToken *
get_throw_types (sMSCtx *c)
{
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return gen_unary (eMST_throw, gen_unary (eMST_rframe, NULL));
    }
  if (GET_CHAR (c) == 'Z')
    {
      INC_CHAR (c);
      return m_name ("");
    }
  return gen_unary (eMST_throw, gen_unary (eMST_rframe, get_argument_types (c)));
}

static uMToken *
get_argument_types (sMSCtx *c)
{
  char ch = GET_CHAR (c);
  uMToken *n = NULL;

  if (ch == 'X')
    {
      INC_CHAR (c);
      return m_element (m_type ("void"));
    }
  if (ch == 'Z')
    {
      INC_CHAR (c);
      return m_element (m_type ("..."));
    }
  n = get_argument_list (c);
  if (!n || c->err)
    return n;
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return n;
    }
  if (GET_CHAR (c) == '@')
    {
      INC_CHAR (c);
      return n;
    }
  if (GET_CHAR (c) == 'Z')
    {
      INC_CHAR (c);
      return chain_tok (n, m_element (m_type ("...")));
    }
  fprintf (stderr, " *** get_argument_types unknown ,%c'\n", GET_CHAR (c));
  return NULL;
}

static uMToken *
get_return_type (sMSCtx *c)
{
  if (GET_CHAR (c) == '@')
    {
      INC_CHAR (c);
      return m_name ("");
    }
  return get_data_type (c);
}

static int
get_number_of_dimensions (sMSCtx *c)
{
  int ret = 0;
  if (GET_CHAR (c))
    return 0;
  if (GET_CHAR (c) >= '0' && GET_CHAR (c) <= '9')
    {
      ret = (int) (GET_CHAR (c) - '0') + 1;
      INC_CHAR (c);
      return ret;
    }
  while (GET_CHAR (c) != '@')
    {
      if (GET_CHAR (c) == 0)
	return 0;
      if (GET_CHAR (c) < 'A' || GET_CHAR (c) > 'P')
	return -1;
      ret <<= 4;
      ret += (int) (GET_CHAR (c) - 'A');
      INC_CHAR (c);
    }
  if (GET_CHAR (c) == '@')
    {
      INC_CHAR (c);
      return ret;
    }
  return -1;
}

static uMToken *
get_array_type (sMSCtx *c, uMToken *superType)
{
  uMToken *n = NULL, *h = NULL;
  int dims;

  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      if (superType)
	return m_combine (gen_unary (eMST_rframe, superType), m_array (NULL));
      return m_array (NULL);
    }
  dims = get_number_of_dimensions (c);
  if ( dims < 0)
    dims=0;
  if (!dims)
    {
      c->err = 2;
      return get_basic_data_type (c, m_array (NULL));
    }
  if (superType && (MTOKEN_FLAGS(superType)&MTOKEN_FLAGS_ARRAY))
    h = m_array (NULL);
  do {
    n = m_array (get_dimension (c, 0, 0));
    if (!h)
      h = n;
    else
      h = m_combine (h, n);
  } while (--dims != 0);
  if (superType)
    {
      if (!(MTOKEN_FLAGS(superType)&MTOKEN_FLAGS_ARRAY))
	superType = gen_unary (eMST_rframe, superType);
      h = m_combine (superType, h);
    }
  n = get_primary_data_type (c, h);
  MTOKEN_FLAGS (n) |= MTOKEN_FLAGS_ARRAY;
  return n;
}

static uMToken *
get_argument_list (sMSCtx *c)
{
  uMToken *n = NULL, *h = NULL;
  int idx;
  
  if (c->err)
    return NULL;
  do {
    h = NULL;
    if (GET_CHAR (c) == '@' || GET_CHAR (c) == 'Z')
      return n;
    if (GET_CHAR (c) == 0)
      {
	c->err = 2;
	return n;
      }
    idx= (int) (GET_CHAR (c) - '0');
    if (idx < 0 || idx > 9)
      {
	const char *svName = c->pos;
	h = get_primary_data_type (c, NULL);
	if ((size_t) (c->pos - svName)>1 && c->pArgList->count < 10)
	  {
	    c->pArgList->arr[c->pArgList->count]=h;
	    c->pArgList->count += 1;
	  }
      }
    else
      {
	INC_CHAR (c);
	h = c->pArgList->arr[idx];
      }
    h = m_element (h);
    n = chain_tok (n, h);
  } while (c->err != 2);
  return n;
}

static uMToken *
get_vdisp_map_type (sMSCtx *c, uMToken *superType)
{
  uMToken *n = superType;
  uMToken *h = get_scope (c);
  h = m_combine (m_name ("for"), h);
  h = gen_unary (eMST_frame, h);
  n = m_combine (n, h);
  if (GET_CHAR (c) =='@')
    INC_CHAR (c);
  return n;
}

static uMToken *
get_ext_data_type (sMSCtx *c, uMToken *superType)
{
  uMToken *dt = NULL,*n = NULL;
  dt = get_data_type (c);
  n = get_indirect_data_type (c, NULL, (char)0, NULL, 0);
  if (superType)
    n = m_combine (n, superType);

  return m_combine (dt, n);
}

static uMToken *getVCallThunkType(sMSCtx *c)
{
  if (GET_CHAR (c) == 0)
    {
      c->err = 2;
      return NULL;
    }
  if (GET_CHAR (c) != 'A')
    {
      fprintf (stderr, " *** getVCallThunkType unknown '%c'\n", GET_CHAR (c));
      return NULL;
    }
  INC_CHAR (c);
  return m_cv ("{flat}");
}

static uMToken *
get_vftable_type (sMSCtx *c, uMToken *superType)
{
  uMToken *n = superType;
  if (c->err || GET_CHAR (c) == 0)
    {
      c->err = 2;
      return n;
    }
  n = m_combine (get_indirect_data_type (c, NULL, (char)0, NULL, 0), n);
  if (c->err == 2 || !n)
    return n;
  if (GET_CHAR (c) != '@')
    {
      n = m_combine (n, m_name ("{for "));
      while (c->err == 0)
        {
	  if (GET_CHAR (c) ==0 || GET_CHAR (c) =='@')
	    break;
	  n = m_combine (n, gen_unary (eMST_lexical_frame, get_scope (c)));
	  if (GET_CHAR (c) == '@')
	    INC_CHAR (c);
	  if (c->err == 0 && GET_CHAR (c) != '@')
	    n = m_combine (n, m_name ("s "));
        }
      if (c->err == 0)
        {
	  if (GET_CHAR (c) == 0)
	    c->err = 2;
	  n = m_combine (n, m_name ("}"));
        }
      if (GET_CHAR (c) != '@')
	return n;
    }
  INC_CHAR (c);
  return n;
}

static uMToken *
compose_decl (sMSCtx *c, uMToken *symbol)
{
  uMToken *n = NULL;
  int et = get_encoded_type (c);
  int nIsUDC = (symbol && (MTOKEN_FLAGS (symbol) & MTOKEN_FLAGS_UDC)) ? 1 : 0;
  if (et==0xffff)
    return NULL;
  if (et==0xfffe)
    {
      c->err = 2;
      return symbol;
    }
  if (et==0xfffd)
    return symbol;
  if ((et&0x8000)==0)
    {
      n = symbol;
      if ((et&0x7c00)==0x6800)
	return get_vftable_type (c, n);
      if ((et&0x7c00)==0x7000)
	return get_vftable_type (c, n);
      if ((et&0x7c00)==0x6000)
        {
	  uMToken *ll = m_element (get_dimension (c, 0, 0));
	  ll = gen_unary (eMST_frame, ll);
	  return m_combine (n, ll);
        }
      if ((et&0x7c00)==0x7c00)
	return get_vdisp_map_type (c, n);
      if ((et&0x7c00)==0x7800)
	return n;
      n = get_ext_data_type (c, n);
      if ((et&0x6000)!=0)
        {
	  if ((et&0x1000))
	    n = m_combine (gen_name (eMST_colon, "[thunk]"), n);
	  return n;
        }
      n = m_combine (m_cv ("static"), n);
      if ((et&0x700) == 0x400 || (et&0x700) == 0x500)
	n = m_combine (m_cv ("virtual"), n);
      switch ((et&0x1800))
        {
          case 0x800:
	    n = m_combine (gen_name (eMST_colon, "private"), n);
	    break;
	  case 0x1000:
	    n = m_combine (gen_name (eMST_colon, "protected"), n);
	    break;
	  case 0x0:
	    n = m_combine (gen_name (eMST_colon, "public"), n);
	    break;
        }
      if ((et&0x400))
	n = m_combine (gen_name (eMST_colon, "[thunk]"), n);
      return n;
    }
  if ((et&0x1f00)==0x1000 || (et&0x1f00)==0x1400)
    {
      n = symbol;
      if ((et&0x6000)!=0 || (et&0x7f00)==0x1400)
	n = m_combine (n, m_name ("local_static_destructor_helper"));
      n = get_ext_data_type (c, n);
      symbol = NULL;
   }
  else if ((et&0x1f00)==0x1500 || (et&0x1f00)==0x1600)
    {
      n = symbol;
      symbol = NULL;
      if ((et&0x1f00)==0x1500) 
        n = m_combine (n, m_name ("template_static_data_member_constructor_helper"));
      else if ((et&0x1f00)==0x1600)
	n = m_combine (n, m_name ("template_static_data_member_destructor_helper"));
    }
  else
    {
      if ((et&0x4000)!=0)
	n = get_based_type (c);
      if ((et&0x1800)==0x1800)
        {
	  uMToken *hh = NULL;
	  hh = m_element (get_dimension (c, 0, 0));
	  hh = chain_tok (hh, m_element (getVCallThunkType (c)));
	  n = m_combine (symbol,
	    gen_unary (eMST_frame, hh));
	  n = m_combine (get_calling_convention (c), n);
        }
      else
        {
	  uMToken *h = NULL;
	  uMToken *n1 = NULL;
	  uMToken *n2 = NULL;
	  uMToken *n3 = NULL;
	  if ((et&0x1000)!=0 || (et&0x1c00)==0xc00)
	    {
	      if ((et&0x1f00)==0xd00)
		n1 = get_dimension (c, 1, 0);
	      n2 = get_dimension (c, 1, 0);
	    }
	  if (((et&0x1800)==0x800) && (et&0x700)!=0x200)
	    n3 = get_this_type (c);
	  n = m_combine (get_calling_convention (c), n);
	  if (symbol)
	    n = m_combine (n, symbol);

	  if (nIsUDC)
	    n = m_combine (n, get_return_type (c));
	  h = get_return_type (c);
	  if (((et&0x1800)!=0x800 ? (et&0x1000)!=0 : (et&0x400)!=0))
	    {
	      if (((et&0x1800)==0x800) && (et&0x700)==0x500)
	        {
		  n2 = chain_tok (
		    m_element (n1),
		    m_element (n2));
		  n2 = gen_unary (eMST_frame, n2);
		  n = m_combine (n, gen_binary (eMST_initfield,
		    m_name ("vtordisp"),
		    n2));
	        }
	      else
	        {
		  n2 = gen_unary (eMST_frame, m_element (n2));
		  n = m_combine (n, gen_binary (eMST_initfield,
		    m_name ("adjustor"),
		    n2));
	        }
	    }
	  n = m_combine (n, gen_unary (eMST_rframe , get_argument_types (c)));
	  if (((et&0x1800)==0x800) && (et&0x700)!=0x200)
	    n = m_combine (n, n3);
	  n = m_combine (n, get_throw_types (c));
	  if (h)
	    n = m_combine (h, n);
        }
    }
  if ((et&0x1800)!=0x800) {
    if ((et&0x1000))
      n = m_combine (gen_name (eMST_colon, "[thunk]"), n);
    return n;
  }
  switch ((et&0x700))
    {
      case 0x200:
	n = m_combine (m_cv ("static"), n);
	break;
      case 0x100:
      case 0x400:
      case 0x500:
	n = m_combine (m_cv ("virtual"), n);
	break;
    }
  switch ((et&0xc0))
    {
      case 0x40:
	n = m_combine (gen_name (eMST_colon, "private"), n);
	break;
      case 0x80:
	n = m_combine (gen_name (eMST_colon, "protected"), n);
	break;
      case 0x0:
	n = m_combine (gen_name (eMST_colon, "public"), n);
	break;
    }
  if ((et&0x400))
    n = m_combine (gen_name (eMST_colon, "[thunk]"), n);
  return n;
}

static int
get_encoded_type (sMSCtx *c)
{
  int ret;

  for(;;)
    {
      ret = 0;
      if (GET_CHAR (c) == '_')
        {
	  INC_CHAR (c);
	  ret = 0x4000;
        }
      if (GET_CHAR (c) >= 'A' && GET_CHAR (c) <= 'Z')
        {
	  int chc = (int) (GET_CHAR (c) - 'A');
	  INC_CHAR (c);
	  if ((chc & 1) == 0)
	    ret |= 0x8000;
	  else
	    ret |= 0xa000;
	  if (chc >= 0x18)
	    return ret;
	  ret |= 0x800;
	  switch((chc&0x18))
	    {
	      case 0:
		ret |= 0x40;
		break;
	      case 8:
		ret |= 0x80;
		break;
	      case 0x10:
		break;
	    }
	  switch((chc&6))
	    {
	      case 0:
		return ret;
	      case 2:
		return ret|0x200;
	      case 4:
		return ret|0x100;
	      case 6:
		return ret|0x400;
	    }
	  return 0xffff;
        }
      if (GET_CHAR (c) != '$')
        {
	  INC_CHAR (c);
	  switch(c->pos[-1])
	    {
	      case '0':
		return 0x800;
	      case '1':
		return 0x1000;
	      case '2':
		return 0;
	      case '3':
		return 0x4000;
	      case '4':
		return 0x2000;
	      case '5':
		return 0x6000;
	      case '6':
		return 0x6800;
	      case '7':
		return 0x7000;
	      case '8':
		return 0x7800;
	      case '9':
		return 0xfffd;
	      case 0:
		DEC_CHAR (c);
		return 0xfffe;
	    }
	  DEC_CHAR (c);
	  return 0xffff;
        }
      INC_CHAR (c);
      switch(GET_CHAR (c))
        {
          case 'A':
	    INC_CHAR (c);
	    return ret|0x9000;
	  case 'B':
	    INC_CHAR (c);
	    return ret|0x9800;
	  case 'C':
	    INC_CHAR (c);
	    return ret|0x7c00;
	  case 'D':
	    INC_CHAR (c);
	    return ret|0x9100;
	  case 'E':
	    INC_CHAR (c);
	    return ret|0x9200;
	  case 0:
	    INC_CHAR (c);
	    return 0xfffe;
	  case '0':
	    INC_CHAR (c);
	    return ret|0x8d40;
	  case '1':
	    INC_CHAR (c);
	    return ret|0xad40;
	  case '2':
	    INC_CHAR (c);
	    return ret|0x8d80;
	  case '3':
	    INC_CHAR (c);
	    return ret|0xad80;
	  case '4':
	    INC_CHAR (c);
	    return ret|0x8d00;
	  case '5':
	    INC_CHAR (c);
	    return ret|0xad00;
	  case '$':
	    if (c->pos[1] == 'P')
	      INC_CHAR (c);
	    break;
	  default:
	    return 0xffff;
        }
      INC_CHAR (c);
      switch(GET_CHAR (c))
        {
          case 'F': case 'G': case 'H': case 'I': case 'L': case 'M':
	    INC_CHAR (c);
	    break;
	  case 'J': case 'K': case 'N': case 'O':
	    INC_CHAR (c);
	    if (GET_CHAR (c) < '0' || GET_CHAR (c) > '9')
	      {
		INC_CHAR (c);
		return 0xffff;
	      }
	    {
	      int skip = (GET_CHAR (c) - '0') + 1;
	      SKIP_CHAR (c, skip);
	    }
	    break;
	  default:
	    INC_CHAR (c);
	    return ret;
        }
    }
}

static uMToken *
m_combine (uMToken *l, uMToken *r)
{
  if (!l && !r)
    return NULL;
  if (!l)
    return r;
  if (!r)
    return l;
  return gen_binary (eMST_combine, l, r);
}

static uMToken *
m_type (const char *typname)
{
  return gen_name (eMST_type, typname);
}

static uMToken *
m_cv (const char *cv)
{
  return gen_name (eMST_cv, cv);
}

static uMToken *
m_coloncolon (uMToken *l, uMToken *r)
{
  if (!l)
    return r;
  if (!r)
    return l;
  return gen_binary (eMST_coloncolon, l, r);
}

static uMToken *
m_element (uMToken *el)
{
  return gen_unary (eMST_element, el);
}

static uMToken *
m_array (uMToken *dim)
{
  return gen_unary (eMST_array, dim);
}

static uMToken *
m_scope (uMToken *n)
{
  return gen_unary (eMST_scope, n);
}

static uMToken *
m_oper (uMToken *n)
{
  return gen_unary (eMST_oper, n);
}

static uMToken *
m_name (const char *str)
{
  return gen_name (eMST_name, str);
}
