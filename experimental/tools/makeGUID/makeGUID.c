#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc == 3 && strlen(argv[2]) == 36) {
    printf("DEFINE_GUID(%s,",argv[1]);
    printf("0x%.8s,",argv[2]);
    printf("0x%.4s,",argv[2]+9);
    printf("0x%.4s,",argv[2]+14);
    printf("0x%.2s,",argv[2]+19);
    printf("0x%.2s,",argv[2]+21);
    printf("0x%.2s,",argv[2]+24);
    printf("0x%.2s,",argv[2]+26);
    printf("0x%.2s,",argv[2]+28);
    printf("0x%.2s,",argv[2]+30);
    printf("0x%.2s,",argv[2]+32);
    printf("0x%.2s);",argv[2]+34);
    printf("\n");
  } else {
    printf("Usage: %s [NAME] [GUID]\n", argv[0]);
    printf("Produces GUID declarations in the form of\n");
    printf("DEFINE_GUID(NAME,0x12345678,0x2235,...);\n");
    printf("\nUsage example:\n");
    printf("%s PARTITION_SYSTEM_GUID c12a7328-f81f-11d2-ba4b-00a0c93ec93b\n",argv[0]);
    printf("DEFINE_GUID(PARTITION_SYSTEM_GUID,0xc12a7328,0xf81f,0x11d2,0xba,0x4b,0x00,0xa0,0xc9,0x3e,0xc9,0x3b);\n");
    printf("\nBuilt on %s\n", __DATE__);
    printf("Report bugs to <mingw-w64-public@lists.sourceforge.net>\n");
  }
  return 0;
}
