#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "img.h"

unsigned short set_pe_hdr_chara = 0;
unsigned short mask_pe_hdr_chara = 0xffff;
int dump_information = 0;
static char *file_name = NULL;

static void
show_usage (void)
{
  fprintf (stderr, "genpeimg [options] files...\n");
  fprintf (stderr, "\nOptions:\n"
    " --set-pe-characteristics -p  Takes as addition argument one or more of the following\n"
    "                              options:\n"
    "  +<flags> or -<flags>\n"
    "  flags are: l, r, n, s, u\n"
    "    l: large-address-aware (only valid for 32-bit)\n"
    "    r: removable-run-from-swap\n"
    "    n: new-run-from-swap\n"
    "    s: system\n"
    "    u: up-system-only\n");
  fprintf (stderr,
    " --help, -h: Show this page.\n"
    " --dump-image-information, -d:  Dump image information to stdout\n");
  exit (0);
}

static int
pass_args (int argc, char **argv)
{
  int has_file = 0;
  int has_error = 0;
  while (argc-- > 0)
    {
      int is_pos = 1;
      char *h = *argv++;
      if (h[0] != '-')
        {
	  has_file = 1;
	  file_name = h;
	  continue;
	}
      switch (h[1])
        {
	case 'p':
	  if (h[2] != 0)
	    goto error_point;
	  if (argc == 0)
	    {
	      fprintf (stderr, "Missing argument for -p\n");
	      show_usage ();
	    }
	  h = *argv++; argc--;
	  while (*h != 0)
	    {
	      if (*h == '-') is_pos = 0;
	      else if (*h == '+') is_pos = 1;
	      else if (*h == 'l')
		{
		  if (is_pos)
		    set_pe_hdr_chara |= 0x20;
		  else
		    mask_pe_hdr_chara &= ~0x20;
		}
	      else if (*h == 'r')
		{
		  if (is_pos)
		    set_pe_hdr_chara |= 0x400;
		  else
		    mask_pe_hdr_chara &= ~0x400;
		}
	      else if (*h == 'n')
		{
		  if (is_pos)
		    set_pe_hdr_chara |= 0x800;
		  else
		    mask_pe_hdr_chara &= ~0x800;
		}
	      else if (*h == 's')
		{
		  if (is_pos)
		    set_pe_hdr_chara |= 0x1000;
		  else
		    mask_pe_hdr_chara &= ~0x1000;
		}
	      else if (*h == 'u')
		{
		  if (is_pos)
		    set_pe_hdr_chara |= 0x4000;
		  else
		    mask_pe_hdr_chara &= ~0x4000;
		}
	      else
		{
		  fprintf (stderr, "Unknown flag-option '%c' for -p\n", *h);
		  has_error = 1;
		}
	      ++h;
	    }
	  break;
	case 'd':
	  if (h[2] == 0)
	    {
	      dump_information = 1;
	      break;
	    }
	  goto error_point;
	case 'h':
	  if (h[2] == 0)
	    show_usage ();
	default:
error_point:
	  fprintf (stderr, "Unknown option ,%s'\n", h);
	  has_error = 1;
	  break;
	}
    }
  if (has_error)
    show_usage ();
  if (!has_file)
    {
      fprintf (stderr, "File argument missing\n");
      show_usage ();
    }
  return 1;
}

int main (int argc, char **argv)
{
  pe_image *pe;
  --argc, ++argv;
  pass_args (argc, argv);

  pe = peimg_load (file_name);
  if (!pe)
    {
      fprintf (stderr, "File not found, or no PE-image\n");
      return 0;
    }

  if (dump_information)
    peimg_show (pe, stdout);
  peimg_free (pe);
  return 0;
}
