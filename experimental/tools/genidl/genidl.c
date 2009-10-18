#define _CRT_SECURE_NO_WARNINGS
#include "genidl_cfg.h"
#include "genidl_readpe.h"
#include "genidl_typeinfo.h"
#include "genidl_typinfo.h"

/* Configure globals.  */
int show_dump_too = 0;

/* Process files.  */
size_t file_args_cnt = 0;
char **file_args = NULL;

static int
scanArgs (int argc, char **argv)
{
  int seen_error = 0;
  if (!argc)
    return -1;
  file_args = (char **) malloc (sizeof (char *) * argc);
  while (argc > 0)
    {
      char *h = *argv;
      if (h[0]  == '-')
	{
	  h++;
	  switch (*h) {
	  case 'd':
	    if (! strcmp (h, "dump") || h[1] == 0)
	      show_dump_too = 1;
	    else
	      goto unknown_fail;
	    break;
	  case 'h':
	    if (! strcmp(h, "help") || h[1] == 0)
	      return -2;
	    goto unknown_fail;
	  default:
unknown_fail:
	    fprintf (stderr, "Option ,%s' is unknown.\n", h);
	    seen_error = 1;
	    break;
	  }
	}
      else
	{
	  file_args[file_args_cnt++] = *argv;
	}
      --argc;
      ++argv;
    }
  if (seen_error || file_args_cnt == 0)
    return -2;
  return 0;
}

int main(int argc,char **argv)
{
  FILE *fp,*gp;
  long p;
  int be64;
  size_t len;
  size_t i;
  unsigned char *dta = NULL;
  if (scanArgs (--argc, ++argv) < 0)
    {
      fprintf (stderr, "Syntax error.\n");
      exit (1);
    }
  for (i=0;i<file_args_cnt;i++)
    {
      char s[1024];
      int start, end;
      gp = fopen (file_args[i], "rb");
      if (!gp)
	{
	  fprintf (stderr, "Failed to open file ,%s'.\n", file_args[i]);
	  continue;
	}
      p = genidl_ispe (gp, &be64);
      fprintf (stderr, "Found PE at %ld (%s bits)\n", p, be64 ? "32" : "64");
      end = genidl_pe_typelib_resource_count (gp);
      fprintf (stderr, "Contains %d typelib resource(s)\n", end);
      for (start = 0; start < end; start++)
	{
      genidl_pe_typelib_resource_read (gp, start, &dta, &len);
      sprintf (s, "test_dump_%d_%d.idl", (int) i, start);
      fp = fopen (s,"wt");
      {
	sTI2TypLib *tl = TI2_typlib_init (dta, (size_t) len);
	if (tl)
	  {
	    TI2_typlib_idl (fp, tl);
	    TI2_typlib_dest (tl);
	  }
	if (show_dump_too)
	  dumpInfo (fp, dta, len);
      }
      fclose (fp);
	}
      fclose (gp);
    }
  return 0;
}
