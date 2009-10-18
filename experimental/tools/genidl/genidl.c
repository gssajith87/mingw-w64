#define _CRT_SECURE_NO_WARNINGS
#include "genidl_cfg.h"
#include "genidl_readpe.h"
#include "genidl_typeinfo.h"
#include "genidl_typinfo.h"

int main(int argc,char **argv)
{
  FILE *fp;
  long p;
  int be64;
  size_t len;
  unsigned char *dta = NULL;

  if (argc > 1)
    fp = fopen (argv[1], "rb");
  else
  //fp = fopen ("C:/windows/System32/stdole2.tlb","rb");
  //fp = fopen ("C:/windows/System32/stdole32.tlb","rb");
  //fp = fopen ("C:/windows/System32/msdatsrc.tlb","rb");
  fp = fopen ("C:/windows/System32/activeds.tlb","rb");
  //fp = fopen ("C:/windows/System32/mshtml.tlb","rb");
  //fp = fopen ("C:/windows/System32/MSVidCtl.dll","rb");
  //fp = fopen ("C:/windows/System32/cdosys.dll","rb");
  if (!fp)
    return 0;
  p = genidl_ispe (fp, &be64);
  printf ("Found PE at %ld (%s bits)\n", p, be64 ? "32" : "64");
  printf ("Contains %d typelib resource(s)\n", genidl_pe_typelib_resource_count (fp));
  genidl_pe_typelib_resource_read (fp, 0, &dta, &len);
  fclose (fp);
  fp = fopen ("test_dump.c","wt");
  {
    sTI2TypLib *tl = TI2_typlib_init (dta, (size_t) len);
    if (tl) {
      TI2_typlib_idl (fp, tl);
      TI2_typlib_dest (tl);
    }
    //dumpInfo (fp, dta, len);
  }
  fclose(fp);
  return 0;
}
