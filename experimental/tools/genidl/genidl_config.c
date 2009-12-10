#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

typedef struct sCfgAlias {
  struct sCfgAlias *next;
  char name[1];
} sCfgAlias;

typedef struct sCfgItem {
  struct sCfgItem *next;
  char *type;
  char name[1];
} sCfgItem;

typedef struct sCfgLib {
  struct sCfgLib *next;
  sCfgAlias *alias;
  sCfgItem *item;
  char name[1];
} sCfgLib;

#define TOK_NAME  256
#define TOK_DIGIT 257
#define TOK_STRING 258
#define TOK_ALIAS 
int genidl_read_config (const char *fname);

static sCfgLib *gen_cfglib (const char *);
static sCfgLib *has_cfglib (const char *, int);
static sCfgAlias *gen_cfglib_alias (sCfgLib *, const char *);
static sCfgAlias *has_cfglib_alias (sCfgLib *, const char *);
static sCfgItem *has_cfglib_item (sCfgLib *, const char *);
static sCfgItem *gen_cfglib_item (sCfgLib *, const char *, const char *);

static int rCh (void);
static void bCh (int r);
static int pCh (void);
static int addCh (int r);
static void delCh (void);
static void clrCh (void);
static void printError (const char *fmt, ...);
static int lex (void);

static FILE *conf_fp = NULL;
static int last_ch = -1;
static int line_no = 1;
static int seen_eof = 0;
static char *l_buffer = NULL;
static size_t l_max, l_cur;

static sCfgLib *cfg_head = NULL;

static sCfgItem *
has_cfglib_item (sCfgLib *c, const char *name)
{
}

static sCfgItem *
gen_cfglib_item (sCfgLib *c, const char *name, const char *type)
{
  sCfgItem *a, *p = NULL, *e = c->item;
  a = has_cfglib_item (c, name);
  if (!a)
    {
      a = (sCfgItem *) malloc (sizeof (sCfgItem) + strlen (name) + 1);
      memset (a, 0, sizeof (sCfgItem));
      strcpy (a->name, name);
    }
  if (a->type != NULL)
    free (a->type);
  a->type = strdup (type);
  while (e != NULL)
    {
      p = e;
      e = e->next;
    }
  if (!p)
    c->item = a;
  else
    p->next = a;
  return a;
}

static sCfgAlias *
gen_cfglib_alias (sCfgLib *c, const char *name)
{
  sCfgAlias *p, *e;
  sCfgAlias *a = has_cfglib_alias (c, name);
  if (a)
    return a;
  a = (sCfgAlias *) malloc (sizeof (sCfgAlias) + strlen (name) + 1);
  memset (a, 0, sizeof (sCfgAlias));
  strcpy (a->name, name);
  p = NULL; e = c->alias;
  while (e != NULL)
    {
      p = e;
      e = e->next;
    }
  if (!p)
    c->alias = a;
  else
    p->next = a;
  return a;
}

static sCfgAlias *
has_cfglib_alias (sCfgLib *c, const char *name)
{
  sCfgAlias *a = (c ? c->alias : NULL);
  while (a != NULL)
    {
      if (!strcmp (a->name, name))
        return a;
      a = a->next;
    }
  return NULL;
}

static sCfgLib *
has_cfglib (const char *name, int withAlias)
{
  sCfgLib *r = cfg_head;
  while (r != NULL)
    {
      if (!strcmp (r->name, name))
        return r;
      if (withAlias && has_cfglib_alias (r, name) != NULL)
        return r;
      r = r->next;
    }
  return NULL;
}

static sCfgLib *
gen_cfglib (const char *name)
{
  sCfgLib *r, *p, *e;
  if ((r = has_cfglib (name, 0)) != NULL)
    return r;
  r = (sCfgLib *) malloc (sizeof (sCfgLib) + strlen (name) + 1);
  memset (r, 0, sizeof (sCfgLib));
  strcpy (r->name, name);
  p = NULL; e = cfg_head;
  while (e != NULL)
    {
      p = e; e = e->next;
    }
  if (!p) cfg_head = r;
  else p->next = r;
  return r;
}

static void
printError (const char *fmt, ...)
{
  va_list argp;
  va_start (argp, fmt);
  fprintf (stderr, "configfile at ");
  if (l_buffer[0] == 0 && seen_eof)
    fprintf (stderr, "end of file");
  else if (l_buffer[0] == 0)
    fprintf (stderr, "start of file");
  else
    fprintf (stderr, "line %d near ,%s'", line_no, l_buffer);
  fprintf (stderr, ": ");
  vfprintf (stderr, fmt, argp);
  va_end (argp);
}

static int
lex (void)
{
  int r;

rescan:
  clrCh ();
  do {
   r = rCh ();
  } while (r >= 0 && r <= 0x20);

  if (r == -1)
    return -1;
  if (r == '/' && pCh () == '*')
    {
      rCh ();
      while ((r=rCh ()) != -1)
        {
	  if (r == '*' && pCh () == '/')
            {
	      rCh ();
	      break;
	    }
        }
      goto rescan;
    }
  else if (r == '/' && pCh () == '/')
    {
      while ((r=rCh ()) != -1)
        {
          if (r == '\n')
	    break;
        }
      goto rescan;
    }
  if (r == '_' || (r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z'))
    {
      bCh (r);
      do {
	addCh (rCh ());
	r = pCh ();
      } while (r == '_' || (r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z')
	       || (r >= '0' && r <= '9') || r == '$' || r == '.');
      return TOK_NAME;
    }
  if (r >= '0' && r <= '9')
    {
      addCh (r);
      if (r == '0')
	{
	  switch (pCh ()) {
	    case 'x': case 'X': addCh (rCh ()); break;
	    case 'o': case 'O': addCh (rCh ()); break;
	    case 'b': case 'B': addCh (rCh ()); break;
	    default:
	      break;
	  }
	}
      return TOK_DIGIT;
    }
  if (r == '"')
    {
      while ((r = pCh ()) != -1 && r != '"' && r != '\n')
	addCh (rCh ());
      if (r != '"')
	printError ("Missing '\"' at end of string.\n");
      else
	rCh ();
      return TOK_STRING;
    }
  addCh (r);
  switch (r)
  {
  case '=': case '{': case '}': case ',':
  case ';':
    return r;
  default:
    break;
  }
  printError ("Illegal character found.\n");
  goto rescan;
}
   
static void
clrCh (void)
{
  l_cur = 0;
  l_buffer[0] = 0;
}

static void
delCh (void)
{
  if (l_cur == 0)
    return;
  --l_cur;
  l_buffer[l_cur] = 0;
}

static int
addCh (int r)
{
  if (r == -1)
    return r;
  if (l_cur == l_max)
    {
      char *h = (char *) realloc (l_buffer, l_max + 129);
      if (!h)
        abort ();
      l_max += 128;
    }
  l_buffer[l_cur++] = (char) r;
  l_buffer[l_cur] = 0;
  return r;
}

static int
pCh (void)
{
  int r = last_ch;
  if (r != -1)
    return r;
  r = rCh ();
  if (r != -1)
    bCh (r);
  return r;
}

static void
bCh (int r)
{
  if (r == '\n')
    line_no--;
  last_ch = r;
}

static int
rCh (void)
{
  int r;
  if ((r = last_ch) == -1)
    {
       char ch;
       if (seen_eof || feof (conf_fp))
         return -1;
       if (fread (&ch, 1, 1, conf_fp) != 1)
         return -1;
       r = ((int) ch) & 0xff;
    }
  else
    last_ch = -1;
  if (r == '\r')
    r = rCh ();
  if (r == '\n')
    line_no++;
  return r;
}

static char **
parse_export (size_t *cnt, int *re, const char *tname)
{
  char **ret = NULL;
  int r = lex ();
  if (r == '=')
    r = lex ();
  if (r != '{')
    {
      printError ("Missing '{' for alias in ,%s'\n", tname);
      *re = r;
      return ret;
    }
  while ((r = lex ()) != -1)
    {
      if (r == '}')
	break;
      if (r == ',' || r == ';')
	continue;
      if (r == TOK_NAME || r == TOK_STRING)
	{
	  char *left = strdup (l_buffer);

	  r = lex ();
	  if (r == ',' || r == '=')
	    r = lex ();
	  if (r != TOK_NAME && r != TOK_STRING)
	    {
	      printError ("Expected in export second string.\n");
	    }
	  else
	    {
	    }
	  free (left);
	}
      else
	printError ("Ignore token in alias of ,%s'.\n", tname);
    }
  return ret;
}

static char **
parse_alias (size_t *cnt, int *re, const char *tname)
{
  char **ret = NULL;
  int r = lex ();
  if (r == '=')
    r = lex ();
  if (r != '{')
    {
      printError ("Missing '{' for alias in ,%s'\n", tname);
      *re = r;
      return ret;
    }
  while ((r = lex ()) != -1)
    {
      if (r == '}')
	break;
      if (r == ',' || r == ';')
	continue;
      if (r == TOK_NAME || r == TOK_STRING)
      {
      }
      else
	printError ("Ignore token in alias of ,%s'.\n", tname);
    }
  return ret;
}

static int
parseTableSub (const char *tname)
{
  char **alias = NULL;
  char **exps;
  size_t alias_cnt = 0;
  size_t exps_cnt = 0;
  int r = lex ();
  while (r != '}')
    {
      if (r == ';')
	{
	  r = lex ();
	  continue;
	}
      if (r != TOK_NAME)
      {
	printError ("Unknown content in ,%s'\n", tname);
	break;
      }
      if (strcmp (l_buffer, "alias")  == 0)
        {
	  alias = parse_alias (&alias_cnt, &r, tname);
	  if (r == -1)
	    break;
        }
      else if (strcmp (l_buffer, "export") == 0)
        {
	  exps = parse_export (&exps_cnt, &r, tname);
	  if (r == -1)
	    break;
        }
      else
      {
	printError ("Unknown command %s in ,%s'\n", l_buffer, tname);
	while ((r = lex ()) != -1 && r != ';');
      }
      r = lex ();
    }
  if (r != '}')
    {
    }
  return r;
}

static int
parseTable (void)
{
  char *table_name;
  int r = lex ();

  if (r == ';')
    return 0;

  switch (r)
    {
    case TOK_NAME:
    case TOK_STRING:
      table_name = strdup (l_buffer);
      break;
    case -1:
      return -1;
    default:
      printError ("Unexpected token.\n");
      return 0;
    }
  r = lex ();
  if (r == '=')
    r = lex ();
  if (r != '{')
    {
      printError ("Missing '{' after ,%s'\n", table_name);
      free (table_name);
      return 0;
    }
  r = parseTableSub (table_name);
  if (r != '}')
    printError ("Missing '}' at end of ,%s'\n", table_name);
  free (table_name);
  return 0;
}

static void
parseStmt (void)
{
  int r;

  while ((r = parseTable ()) != -1)
  {
  }
}


int
genidl_read_config (const char *fname)
{
  if (!fname)
    return -1;
  conf_fp = fopen (fname, "rb");
  if (!conf_fp)
    return -1;
  l_buffer = (char *) malloc (129);
  if (!l_buffer)
    {
      fclose (conf_fp);
      return -1;
    }
  l_max = 128;
  l_cur = 0;
  l_buffer[0] = 0;
  line_no = 1;
  seen_eof = 0;
  parseStmt ();
  free (l_buffer);
  fclose (conf_fp);
  return 0;
}

