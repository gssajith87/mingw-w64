#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#if 0
#define PRDEBUG(ARG...)  fprintf(stderr,ARG)
#else
#define PRDEBUG(ARG...) do { } while(0)
#endif

#ifndef IMAGE_FIRST_SECTION
#define IMAGE_FIRST_SECTION(ntheader) ((PIMAGE_SECTION_HEADER) ((ULONG_PTR)ntheader + FIELD_OFFSET(IMAGE_NT_HEADERS,OptionalHeader) + ((PIMAGE_NT_HEADERS)(ntheader))->FileHeader.SizeOfOptionalHeader))
#endif

#ifndef IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
#define IMAGE_SIZEOF_NT_OPTIONAL32_HEADER 224
#endif
#ifndef IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER 240
#endif
#ifndef IMAGE_NT_OPTIONAL_HDR32_MAGIC
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC 0x10b
#endif
#ifndef IMAGE_NT_OPTIONAL_HDR64_MAGIC
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC 0x20b
#endif

typedef struct sExportname {
  struct sExportname *next;
  char *name;
  char *forward;
  DWORD ord;
  DWORD func;
  DWORD retpop;
  int be64;
  int beData;
} sExportName;

enum {
  c_ill=-1,c_EG,c_lb,c_lv,c_1,c_2,c_3,c_4,
  c_0f,c_ad,c_op,c_EGlv,c_EGlb,c_jxx,c_jxxv,
  c_O,
  c_g4, c_EGg3b, c_EGg3v,
  c_jmpnjb,c_jmpfap,
  c_jmpnjv,c_calljv,c_callfar,
  c_iret,c_int3,
  c_retf,c_retflw,
  c_retn,c_retnlw,
};

static int load_pep(void);
static void do_pedef(void);
static void do_pepdef(void);
static void do_export_read(DWORD va_exp,DWORD sz_exp,int be64);
static void add_export_list(DWORD ord,DWORD func,const char *name, const char *forward,int be64,int beData);
static void dump_def(void);
static int disassembleRet(DWORD func,DWORD *retpop,const char *name);
static size_t getMemonic(int *aCode,DWORD pc,DWORD *jmp_pc);

static void *map_va(DWORD va);
static int is_data(DWORD va);

static sExportName *gExp = NULL;
static sExportName *gExpTail = NULL;
char *fninput;
char *fnoutput;
char *fndllname;

size_t gDta_size;
unsigned char *gDta;
PIMAGE_DOS_HEADER gMZDta;
PIMAGE_NT_HEADERS32 gPEDta;
PIMAGE_NT_HEADERS64 gPEPDta;

int main(int argc,char **argv)
{
  int i;
  if (argc < 2)
  {
    fprintf (stderr,"gendef.exe input-dll-files ...\n");
    return 0;
  }
  for (i=1;i<argc;i++)
  {
    char *r1,*r2;
    fninput = strdup(argv[i]);
    r1 = strrchr (fninput,'/');
    r2 = strrchr (fninput,'\\');
    if (!r1 && r2!=NULL) r1=r2+1;
    else if(r1==NULL && r2==NULL)
      r1 = fninput;
    else if (r2!=NULL && r1!=NULL && r1 < r2)
      r1=r2+1;
    else r1++;
    fnoutput = (char*) malloc(strlen(fninput)+5);
    strcpy (fnoutput,r1);

    r1 = strrchr(fnoutput,'.');
    if (r1) strcpy(r1,".def");
    else strcat(fnoutput,".def");
    fprintf(stderr,"Loading %s ...\n", fninput);
    if (load_pep()) {
      fprintf(stderr,"Generating from %s definition file %s ...\n", fninput,fnoutput);
      if (gPEDta)
	do_pedef();
      else
	do_pepdef();
      dump_def ();
      if (fndllname)
	free (fndllname);
      fndllname = NULL;
      free (gDta);
    }
    free (fnoutput);
    free (fninput);
  }
  return 0;
}

static int
load_pep(void)
{
  FILE *fp = fopen (fninput, "rb");
  if (!fp) {
    fprintf(stderr,"*** failed to open()\n"); return 0;
  }
  fseek(fp,0,SEEK_END);
  gDta_size = (size_t) ftell(fp);
  if (gDta_size > 0) {
    fseek(fp,0,SEEK_SET);
    gDta = (unsigned char*)malloc(gDta_size + 1);
    if (gDta) {
      fread (gDta,1,gDta_size,fp);
      gDta[gDta_size]=0;
    }
  }
  fclose(fp);
  if (!gDta) {
    fprintf(stderr,"*** unable to allocate %Iu bytes\n", gDta_size);
    return 0;
  }
  gMZDta = (PIMAGE_DOS_HEADER) gDta;
  if (gDta_size < sizeof(IMAGE_DOS_HEADER) || gDta[0]!='M' || gDta[1]!='Z'
      || gMZDta->e_lfanew <= 0
      || gMZDta->e_lfanew >= (LONG) gDta_size)
  {
    fprintf(stderr,"*** not a PE(+) file\n");
    free(gDta);
    return 0;
  }
  gPEDta = (PIMAGE_NT_HEADERS32) &gDta[gMZDta->e_lfanew];
  gPEPDta = (PIMAGE_NT_HEADERS64) gPEDta;
  if (gPEDta->Signature != IMAGE_NT_SIGNATURE)
  {
    fprintf(stderr,"*** no PE(+) signature\n");
    free(gDta);
    return 0;
  }
  if (gPEDta->FileHeader.SizeOfOptionalHeader == IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
    && gPEDta->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
  {
    gPEPDta=NULL;
    fprintf(stderr," * Found PE image\n");
  }
  else if (gPEPDta->FileHeader.SizeOfOptionalHeader == IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
    && gPEPDta->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
  {
    gPEDta=NULL;
    fprintf(stderr," * Found PE+ image\n");
  }
  else {
    free(gDta);
    fprintf(stderr,"*** no PE(+) optional header\n");
    return 0;
  }
  return 1;
}

static int is_data(DWORD va)
{
  PIMAGE_SECTION_HEADER sec;
  DWORD sec_cnt,i;
  char *dptr;
  if(gPEDta) {
    sec_cnt = gPEDta->FileHeader.NumberOfSections;
    sec = IMAGE_FIRST_SECTION(gPEDta);
  } else {
    sec_cnt = gPEPDta->FileHeader.NumberOfSections;
    sec = IMAGE_FIRST_SECTION(gPEPDta);
  }
  if(!sec) return 0;
  for (i=0;i<sec_cnt;i++) {
    if (va >= sec[i].VirtualAddress && va < (sec[i].VirtualAddress+sec[i].Misc.VirtualSize))
      break;
  }
  if (i == sec_cnt) return 0; 
  if ((sec[i].Characteristics&(IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE))!=0)
    return 0;
  if ((sec[i].Characteristics&IMAGE_SCN_MEM_DISCARDABLE)!=0)
    return 1;
  if ((sec[i].Characteristics&IMAGE_SCN_MEM_READ)==0)
    return 0;
  if ((sec[i].Characteristics&(IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_CNT_UNINITIALIZED_DATA|IMAGE_SCN_LNK_COMDAT))!=0)
    return 1;
  return 1;
}

static void *map_va(DWORD va)
{
  PIMAGE_SECTION_HEADER sec;
  DWORD sec_cnt,i;
  char *dptr;
  if(gPEDta) {
    sec_cnt = gPEDta->FileHeader.NumberOfSections;
    sec = IMAGE_FIRST_SECTION(gPEDta);
  } else {
    sec_cnt = gPEPDta->FileHeader.NumberOfSections;
    sec = IMAGE_FIRST_SECTION(gPEPDta);
  }
  for (i=0;i<sec_cnt;i++) {
    if (va >= sec[i].VirtualAddress && va < (sec[i].VirtualAddress+sec[i].Misc.VirtualSize))
    {
      dptr = &gDta[va-sec[i].VirtualAddress+sec[i].PointerToRawData];
      return (void *)dptr;
    }
  }
  return NULL;
}

#ifndef IMAGE_DIRECTORY_ENTRY_EXPORT
#define IMAGE_DIRECTORY_ENTRY_EXPORT 0
#endif

/* For pep we can take the exports itself, there is no additional decoration necessary.  */
static void do_pepdef(void)
{
  DWORD va_exp = gPEPDta->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
  DWORD sz_exp = gPEPDta->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
  do_export_read(va_exp,sz_exp,1);
}

static void do_pedef(void)
{
  DWORD va_exp = gPEDta->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
  DWORD sz_exp = gPEDta->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
  do_export_read(va_exp,sz_exp,0);
}

static void do_export_read(DWORD va_exp,DWORD sz_exp,int be64)
{
  DWORD i;
  PIMAGE_EXPORT_DIRECTORY exp_dir;
  PDWORD functions;
  PWORD ordinals;
  PDWORD name;
  if (va_exp == 0 || sz_exp==0)
    return;
  exp_dir = (PIMAGE_EXPORT_DIRECTORY) map_va(va_exp);
  PRDEBUG(" * export directory at VA = 0x%x size=0x%x\n", va_exp,sz_exp);
  fndllname = strdup((char*) map_va(exp_dir->Name));
  PRDEBUG(" * Name: %s\n * Base: %u\n", fndllname, exp_dir->Base);
  functions = (PDWORD) map_va(exp_dir->AddressOfFunctions);
  ordinals = (PWORD) map_va(exp_dir->AddressOfNameOrdinals);
  name = (PDWORD) map_va(exp_dir->AddressOfNames);
  
  for(i=0;i<exp_dir->NumberOfFunctions;i++)
  {
    DWORD entryPointRVA = functions[i];
    DWORD j;
    char *fname;
    DWORD ord;
    fname = NULL;
    if(!entryPointRVA)
      continue;
    ord = i + exp_dir->Base;
    for(j=0;j<exp_dir->NumberOfNames;j++)
      if(ordinals[j]==i)
	fname = (char*) map_va(name[j]);
    if(entryPointRVA >= va_exp && entryPointRVA <= (va_exp+sz_exp))
    {
      add_export_list(ord,0,fname,(char*) map_va(entryPointRVA),be64,0);
    } else
      add_export_list(ord,entryPointRVA,fname,NULL,be64,is_data(entryPointRVA));
  }
}

static void
add_export_list(DWORD ord,DWORD func,const char *name, const char *forward,int be64,int beData)
{
  sExportName *exp = NULL;
  if (!name) name="";
  if (!forward) forward="";
  exp = (sExportName *) malloc(sizeof(sExportName)+strlen(name)+strlen(forward)+2);
  if(!exp) return;
  exp->name = (char *) &exp[1];
  exp->forward = exp->name + strlen(name) + 1;
  strcpy(exp->name,name);
  strcpy(exp->forward,forward);
  exp->next=NULL;
  exp->ord=ord;
  exp->func=func;
  exp->be64=be64;
  exp->beData=beData;
  exp->retpop = (DWORD)-1;
  if (gExpTail) gExpTail->next=exp;
  else gExp=exp;
  gExpTail = exp;
}

static void
dump_def(void)
{
  sExportName *exp;
  FILE *fp;

  if (!fndllname || gExp == NULL) return;
  fp = fopen(fnoutput,"wt");
  if(!fp) {
    fprintf(stderr," * failed to create %s ...\n",fnoutput);
    return;
  }
  fprintf (fp,"/**\n * Definition file of %s\n * Generated by gendef (c) 2008 Kai Tietz\n */\n",
    fndllname);
  fprintf (fp,"LIBRARY \"%s\"\nEXPORTS\n",fndllname);
  while ((exp = gExp) != NULL) {
    gExp = exp->next;
    if (exp->name[0]==0)
      fprintf(fp,"ord_%u",exp->ord,exp->ord);
    else
      fprintf(fp,"%s",exp->name);
    if (!exp->beData && !exp->be64 && exp->func!=0)
      exp->beData = disassembleRet(exp->func, &exp->retpop,exp->name);
    if (exp->retpop != (DWORD) -1)
      fprintf(fp,"@%u",exp->retpop);
    if (exp->name[0]==0)
      fprintf(fp," @%u",exp->ord);
    if (exp->beData)
      fprintf(fp," DATA");
    fprintf(fp,"\n");
    free (exp);
  }
  gExpTail=NULL;
  fclose(fp);
}

typedef struct sAddresses {
  DWORD max;
  DWORD cnt;
  DWORD *ptrs;
  DWORD idx;
} sAddresses;

static int disassmbleRetIntern(DWORD pc,DWORD *retpop,sAddresses *seen,sAddresses *stack,int *hasret,int *atleast_one,const char *name);
static sAddresses*init_addr(void);
static void dest_addr(sAddresses *ad);
static int push_addr(sAddresses *ad,DWORD val);
static int pop_addr(sAddresses *ad,DWORD *val);

static sAddresses*init_addr(void)
{
  sAddresses *r = (sAddresses*)malloc(sizeof(sAddresses));
  r->max=8;
  r->cnt=0;
  r->ptrs = (DWORD *) malloc(sizeof(DWORD)*8);
  r->idx=0;
  return r;
}

static void dest_addr(sAddresses *ad)
{
  free (ad->ptrs);
  free (ad);
}

static int push_addr(sAddresses *ad,DWORD val)
{
  DWORD i;
  for (i=0;i<ad->cnt;i++) {
    if (ad->ptrs[i]==val) return 0;
  }
  if (ad->max == ad->cnt) {
    DWORD *p=(DWORD *) malloc(sizeof(DWORD)*(ad->max + 8));
    memcpy (p,ad->ptrs,sizeof(DWORD)*ad->max);
    ad->max+=8;
    free (ad->ptrs);
    ad->ptrs=p;
  }
  ad->ptrs[ad->cnt++]=val;
  return 1;
}

static int pop_addr(sAddresses *ad,DWORD *val)
{
  if (!ad || ad->idx==ad->cnt) return 0;
  ad->idx++;
  *val=ad->ptrs[ad->idx-1];
  return 1;
}

/* exp->beData */
static int disassembleRet(DWORD func,DWORD *retpop,const char *name)
{
  sAddresses *seen = init_addr();
  sAddresses *stack = init_addr();
  DWORD pc;
  int hasret=0;
  int atleast_one = 0;
  *retpop = (DWORD) -1;
  push_addr(stack,func);

  while (!hasret && pop_addr(stack,&pc)) {
    disassmbleRetIntern(pc,retpop,seen,stack,&hasret,&atleast_one,name);
  }
  dest_addr(seen);
  dest_addr(stack);
  return (atleast_one ? 0 : 1);
}

static int disassmbleRetIntern(DWORD pc,DWORD *retpop,sAddresses *seen,sAddresses *stack,int *hasret,int *atleast_one,const char *name)
{
  size_t sz;
  int code,break_it;
  DWORD tojmp;
  while(1) {
    if (!push_addr(seen,pc)) return 0;    
    sz=getMemonic(&code,pc,&tojmp);
    if (!sz || code == c_ill) {
      PRDEBUG(" %s = 0x%x ILL (%Ix) at least one==%d\n",name,pc, sz,atleast_one[0]);
      break;
    }
    atleast_one[0]+=1;
    break_it=0;
    pc+=sz;
    switch(code) {
    case c_jmpnjb: case c_jmpnjv:
      pc = tojmp; break;
    case c_jxx:
      push_addr(stack,tojmp);
      break;
    case c_jmpfap: case c_int3:
      break_it=1; break;
    case c_iret: case c_retf: case c_retn:
      *hasret = 1; return 0;
    case c_retflw: case c_retnlw:
      *hasret=1; *retpop=tojmp; return 0;
    }
    if (break_it) break;
  }

  return 0;
}

static int opMap2[256] = {
  c_EG,c_EG,c_EG,c_EG,c_1,c_1,c_ill,c_ill, /* 0x00-0x07 */
  c_1,c_1,c_ill,c_ill,c_ill,c_ill,c_ill,c_ill, /* 0x08-0x0f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x10-0x17 */
  c_EG,c_ill,c_ill,c_ill,c_ill,c_ill,c_ill,c_ill, /* 0x18-0x1f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_ill,c_EG,c_ill, /* 0x20-0x27 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x28-0x2f */
  c_1,c_1,c_1,c_1,c_1,c_1,c_ill,c_ill, /* 0x30-0x37 */
  c_ill,c_ill,c_ill,c_ill,c_ill,c_ill,c_ill,c_ill, /* 0x38-0x3f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x40-0x47 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x48-0x4f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x50-0x57 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x58-0x5f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x60-0x67 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x68-0x6f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x70-0x77 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x78-0x7f */
  c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv, /* 0x80-0x87 */
  c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv,c_jxxv, /* 0x88-0x8f */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x90-0x97 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x98-0x9f */
  c_1,c_1,c_1,c_EG,c_EGlb,c_EG,c_ill,c_ill, /* 0xa0-0xa7 */
  c_1,c_1,c_1,c_EG,c_EGlb,c_EG,c_EG,c_EG, /* 0xa8-0xaf */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xb0-0xb7 */
  c_ill,c_ill,c_EGlb,c_EG, c_EG,c_EG,c_EG,c_EG, /* 0xb8-0xbf */
  c_EG,c_EG,c_EG,c_EG,c_EGlb,c_EGlb,c_EGlb,c_EGlb, /* 0xc0-0xc7 */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0xc8-0xcf */
  c_ill,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xd0-0xd7 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xd8-0xdf */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xe0-0xe7 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xe8-0xef */
  c_ill,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xf0-0xf7 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_ill /* 0xf8-0xff */
};

static int opMap1[256] = {
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x00-0x07 */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_0f, /* 0x08-0x0f */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x10-0x17 */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x18-0x1f */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x20-0x27 */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x28-0x2f */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x30-0x37 */
  c_EG,c_EG,c_EG,c_EG,c_lb,c_lv,c_1,c_1, /* 0x38-0x3f */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0x40-0x47 */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0x48-0x4f */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0x50-0x57 */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0x58-0x5f */
  c_1,c_1,c_EG,c_EG,c_1,c_1,c_op,c_ad, /* 0x60-0x67 */
  c_lv,c_EGlv,c_lb,c_EGlb,c_1,c_1,c_1,c_1, /* 0x68-0x6f */
  c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx, /* 0x70-0x77 */
  c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx,c_jxx, /* 0x78-0x7f */
  c_EGlb,c_EGlv,c_EGlb,c_EGlb,c_EG,c_EG,c_EG,c_EG, /* 0x80-0x87 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0x88-0x8f */
  c_1,c_1,c_1,c_1,c_1,c_1,c_1,c_1, /* 0x90-0x97 */
  c_1,c_1,c_callfar,c_1,c_1,c_1,c_1,c_1, /* 0x98-0x9f */
  c_O,c_O,c_O,c_O,c_1,c_1,c_1,c_1, /* 0xa0-0xa7 */
  c_lb,c_lv,c_1,c_1,c_1,c_1,c_1,c_1, /* 0xa8- 0xaf */
  c_2,c_2,c_2,c_2,c_2,c_2,c_2,c_2, /* 0xb0-0xb7 */
  c_lv,c_lv,c_lv,c_lv,c_lv,c_lv,c_lv,c_lv, /* 0xb8-0xbf */
  c_EGlb,c_EGlb,c_retnlw,c_retn,c_EG,c_EG,c_EGlb,c_EGlv, /* 0xc0-0xc7 */
  c_4,c_1,c_retflw,c_retf,c_int3,c_2,c_1,c_iret, /* 0xc8-0xcf */
  c_EG,c_EG,c_EG,c_EG,c_2,c_2,c_1,c_1, /* 0xd0-0xd7 */
  c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG,c_EG, /* 0xd8-0xdf */
  c_jxx,c_jxx,c_jxx,c_jxx,c_2,c_2,c_2,c_2, /* 0xe0-0xe7 */
  c_calljv,c_jmpnjv,c_jmpfap,c_jmpnjb,c_1,c_1,c_1,c_1, /* 0xe8-0xef */
  c_1,c_1,c_1,c_1, c_1,c_1,c_EGg3b,c_EGg3v, /* 0xf0-0xf7 */
  c_1,c_1,c_1,c_1,c_1,c_1,c_g4,c_g4 /* 0xf8-0xff */
};

static size_t getMemonic(int *aCode,DWORD pc,DWORD *jmp_pc)
{
  static unsigned char lw[4];
  unsigned char *p;
  int addr_mode = 1;
  int oper_mode = 1;
  DWORD sz = 0;
  unsigned char b;
  int tb1;
  for(;;) {
    p = (unsigned char*)map_va(pc + sz);
    if (!p) { *aCode=c_ill; return 0; }
    b = p[0];
    if (b==0x26 || b==0x2e || b==0x36 || b==0x3e || b==0x64 || b==0x65)
      ++sz;
    else if (b==0x66) { oper_mode^=1; sz++; }
    else if (b==0x67) { addr_mode^=1; sz++; }
    else if (b==0xf2 || b==0xf3 || b==0xf0) sz++;
    else break;
  }
  sz++;
  tb1=opMap1[(unsigned int) b];
redo_switch:
  if (tb1!=c_ill) { lw[0]=lw[1]; lw[1]=lw[2]; lw[2]=lw[3]; lw[3]=b; }
  switch (tb1) {
  case c_ill:
    PRDEBUG(" 0x%x (0x%x,0x%x,0x%x,0x%x last) illegal ", (DWORD)b, (DWORD)lw[0], (DWORD)lw[1],(DWORD)lw[2],(DWORD)lw[3]);
    *aCode=c_ill; return 0;
  case c_4: sz++;
  case c_3: sz++;
  case c_lb:
  case c_2: sz++;
  case c_retn: case c_retf:
  case c_iret: case c_int3:
  case c_ad: case c_op:
  case c_1: *aCode=tb1; return sz;
  case c_lv:
    if (oper_mode) sz+=4;
    else sz+=2;
    *aCode=tb1; return sz;
  case c_O: case c_calljv:
    if (addr_mode) sz+=4;
    else sz+=2;
    *aCode=tb1; return sz;
  case c_EG: case c_EGlv: case c_EGlb: case c_g4: case c_EGg3v: case c_EGg3b:
    p = (unsigned char*)map_va(pc + sz);
    sz++;
    if (!p) { *aCode=c_ill; return 0; }
    b = p[0];
    if (addr_mode) {
      if((b&0xc0)==0 && (b&7)==5) { sz+=4; goto sib_done; }
      if((b&0x7)==4)
	sz++;
      if((b&0xc0)==0x40)
	sz+=1;
      else if((b&0xc0)==0x80)
	sz+=4;
sib_done:
      ;
    } else {
      if((b&0xc0)==0) {
	if((b&0x07)==6) sz+=2;
      } else if((b&0xc0)==0x40)
	sz+=1;
      else if((b&0xc0)==0x80)
	sz+=2;
    }
    if (tb1==c_EGlv) sz+=(oper_mode ? 4 : 2);
    else if(tb1==c_EGlb) sz++;
    else if(tb1==c_g4) {
      if ((b&0x38)==0x20 || (b&0x38)==0x28)
	tb1=c_int3;
    } else if (tb1==c_EGg3v || tb1==c_EGg3b) {
      switch (((b&0x38)>>3)) {
      case 1:
      case 0: sz+= (tb1==c_EGg3v ? (oper_mode ? 4 : 2) : 1); break;
      default: break;
      }
    }
    *aCode=tb1; return sz;
  case c_jxx: case c_jmpnjb:
    p = (unsigned char*)map_va(pc + sz);
    if (!p) { *aCode=c_ill; return 0; }
    b = p[0];
    sz++;
    if ((b&80)!=0) jmp_pc[0]=pc+sz+(((DWORD) b)|0xffffff00);
    else jmp_pc[0]=pc+sz+(DWORD) b;
    *aCode=tb1; return sz;
  case c_jmpnjv:
  case c_jxxv: 
    p = (unsigned char*)map_va(pc + sz);
    if (!p) { *aCode=c_ill; return 0; }
    if (addr_mode) { jmp_pc[0]=*((DWORD *)p); sz+=4; }
    else {
      jmp_pc[0]=(DWORD) *((unsigned short *)p);
      if ((jmp_pc[0]&0x8000)!=0) jmp_pc[0]|=0xffff0000;
      sz+=2;
    }
    jmp_pc[0]+=pc+sz;
    if ((jmp_pc[0]&0xff000000)!=0) {
      PRDEBUG(" 0x%x (0x%x,0x%x,0x%x,0x%x last) illegal ", (DWORD)b, (DWORD)lw[0], (DWORD)lw[1],(DWORD)lw[2],(DWORD)lw[3]);
      PRDEBUG("jmp(cond) 0x%x (sz=%x,pc=%x,off=%x) ", jmp_pc[0], (DWORD)sz,pc,(DWORD) (jmp_pc[0]-(sz+pc)));
    }
    *aCode=(tb1==c_jxxv ? c_jxx : tb1); return sz;
  case c_0f:
    p = (unsigned char*)map_va(pc + sz);
    if (!p) { *aCode=c_ill; return 0; }
    b = p[0];
    sz++;
    tb1=opMap2[b];
    goto redo_switch;
  case c_jmpfap:
    sz+=4; if(addr_mode) sz+=2;
    *aCode=tb1; return sz;
  case c_callfar:
    sz+=4; if(addr_mode) sz+=2;
    *aCode=tb1; return sz;
  case c_retflw: case c_retnlw:
    p = (unsigned char*)map_va(pc + sz);
    if (!p) { *aCode=c_ill; return 0; }
    *jmp_pc=*((unsigned short*)p);
    sz+=2;
    *aCode=tb1;
    return sz;
  default:
    PRDEBUG(" * opcode 0x%x (tbl=%d) unknown\n", b, tb1);
    sz=0; *aCode=c_ill; break;
  }
  return sz;
}
