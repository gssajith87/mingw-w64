#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "img.h"

pe_image *
peimg_load (const char *fname)
{
  pe_image *r;
  file_image *fi = fimg_create ();
  if (!fi)
    return NULL;
  if (!fimg_load (fi, fname))
    {
      fimg_free (fi);
      return NULL;
    }
  if ((r = peimg_create (fi)) != NULL)
    return r;
  fimg_free (fi);
  return NULL;
}

static size_t
find_pe_hdr (file_image *fi)
{
  unsigned char m1, m2;
  int lfanew;
  m1 = fimg_get_uchar_at (fi, 0);
  m2 = fimg_get_uchar_at (fi, 1);
  if (m1 == 'P' && m2 == 'E')
    {
      fprintf (stderr, "Starts with PE\n");
      return 0;
    }
  if (m1 != 'M' || m2 != 'Z')
    return FIMG_POS_END;
  if (fi->data_len < 256)
    return FIMG_POS_END;
  lfanew = (int) fimg_get_uint_at (fi, 60, 0);
  if (lfanew <= 0 || (size_t) lfanew >= fi->data_len)
    return FIMG_POS_END;
  m1 = fimg_get_uchar_at (fi, lfanew);
  m2 = fimg_get_uchar_at (fi, lfanew + 1);
  if (m1 != 'P' || m2 != 'E')
    return FIMG_POS_END;
  m1 = fimg_get_uchar_at (fi, lfanew + 2);
  m2 = fimg_get_uchar_at (fi, lfanew + 3);
  if (m1 != 0 || m1 != m2)
    return FIMG_POS_END;
  return (size_t) lfanew;
}

static int
fill_pe_info (pe_image *pe)
{
  /* File header is 24 bytes long.  */
  pe->pe_filehdr.machine = PEIMG_GET_USHORT (pe, 4);
  pe->pe_filehdr.numsecs = PEIMG_GET_USHORT (pe, 6);
  pe->pe_filehdr.timestamp =  PEIMG_GET_UINT (pe, 8);
  pe->pe_filehdr.pointer2SymTab = PEIMG_GET_UINT (pe, 12);
  pe->pe_filehdr.numSyms = PEIMG_GET_UINT (pe, 16);
  pe->pe_filehdr.szOptHdr = PEIMG_GET_USHORT (pe, 20);
  pe->pe_filehdr.characteristics = PEIMG_GET_USHORT (pe, 22);
  switch (pe->pe_filehdr.machine)
    {
    case 0x14c: /* i386 */
      pe->is_64bit = 0;
      pe->is_bigendian = 0;
      break;
    case 0x8664:
      pe->is_64bit = 1;
      pe->is_bigendian = 0;
      break;
    default:
      fprintf (stderr, "PE image for machince 0x%x not supported\n", pe->pe_filehdr.machine);
      return 0;
    }
  return 1;
}

pe_image *
peimg_create (file_image *pimg)
{
  size_t pe_hdr;
  pe_image *r;
  if (!pimg)
    return NULL;
  pe_hdr = find_pe_hdr (pimg);
  if (pe_hdr == FIMG_POS_END)
    return NULL;
  /* So we might have found a PE-image.  */
  r = (pe_image *) malloc (sizeof (pe_image));
  if (!r)
    return NULL;
  memset (r, 0, sizeof (pe_image));
  r->pimg = pimg;
  r->start_pe = pe_hdr;
  r->size_pe = pimg->data_len - pe_hdr;
  if (!fill_pe_info (r))
    {
      free (r);
      r = NULL;
    }
  return r;
}  

void
peimg_free (pe_image *ppeimg)
{
  if (!ppeimg)
    return;
  if (ppeimg->pimg)
    fimg_free (ppeimg->pimg);
  memset (ppeimg, 0, sizeof (pe_image));
  free (ppeimg);
}

void
peimg_show (pe_image *ppeimg, FILE *outfp)
{
  unsigned short hdr_cha;
  if (!ppeimg || !outfp)
    return;
  fprintf (outfp, "PE image \"%s\"\n  found at position 0x%Ix in file-image\n",
    ppeimg->pimg->filename, ppeimg->start_pe);
  fprintf (outfp, "  Image has size of 0x%Ix byte(s)\n", ppeimg->size_pe);
  fprintf (outfp, "  Image machine kind is: 0x%x (%s)\n",
    ppeimg->pe_filehdr.machine, ppeimg->is_64bit ? "64-bit" : "32-bit");
  fprintf (outfp, "  Image contains %u section(s)\n", ppeimg->pe_filehdr.numsecs);
  fprintf (outfp, "  Optional header-size is %u\n", ppeimg->pe_filehdr.szOptHdr);
  hdr_cha = ppeimg->pe_filehdr.characteristics;
  if (hdr_cha != 0)
    {
      fprintf (outfp, "  Characterstics:");
      if ((hdr_cha & 1) != 0)
        fprintf (outfp, " relocs-stripped");
      if ((hdr_cha & 2) != 0)
        fprintf (outfp, " executable");
      if ((hdr_cha & 4) != 0)
        fprintf (outfp, " line-numbers-stripped");
      if ((hdr_cha & 8) != 0)
        fprintf (outfp, " local-syms-stripped");
      if ((hdr_cha & 16) != 0)
        fprintf (outfp, " aggressive-ws-trim");
      if ((hdr_cha & 32) != 0)
        fprintf (outfp, " large-address-aware");
      if ((hdr_cha & 0x80) != 0)
        fprintf (outfp, " bytes-reversed");
      if ((hdr_cha & 0x100) != 0)
        fprintf (outfp, " 32-bit-machine");
      if ((hdr_cha & 0x200) != 0)
        fprintf (outfp, " debug-stripped");
      if ((hdr_cha & 0x400) != 0)
        fprintf (outfp, " removable-run-from-swap");
      if ((hdr_cha & 0x800) != 0)
        fprintf (outfp, " net-run-from-swap");
      if ((hdr_cha & 0x1000) != 0)
        fprintf (outfp, " system");
      if ((hdr_cha & 0x2000) != 0)
        fprintf (outfp, " DLL");
      if ((hdr_cha & 0x4000) != 0)
        fprintf (outfp, " up-system-only");
      if ((hdr_cha & 0x8000) != 0)
        fprintf (outfp, " bytes-reversed-high");
      hdr_cha &= 0x40;
      if (hdr_cha != 0)
        fprintf (outfp, " unknown-flag-0x40");
      fprintf (outfp, "\n");
    }
}

#if 0
int main(int argc, char **argv)
{
  pe_image *pe;
  pe = peimg_load (argv[0]);
  if (!pe)
    {
      fprintf (stderr, "File not found, or no PE-image\n");
      return 0;
    }
  peimg_show (pe, stderr);
  peimg_free (pe);
  return 1;
}
#endif
