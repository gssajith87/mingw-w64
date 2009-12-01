#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

#define TOK_NAME  256
#define TOK_DIGIT 257
#define TOK_STRING 258

int genidl_read_config (const char *fname);

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
	       || (r >= '0' && r <= '9') || r == '$');
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

static void parseStmt (void)
{
  int r;

  while ((r = lex ()) != -1)
  {
    fprintf (stderr, " %s", l_buffer);
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

