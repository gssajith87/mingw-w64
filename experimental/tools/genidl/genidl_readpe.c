#define _CRT_SECURE_NO_WARNINGS
#include "genidl_cfg.h"

#include "genidl_readpe.h"

static int32_t readResourceDirectory (FILE *fp, unsigned char **dta, size_t *length, size_t *resRVA);

static void walk_res_dir (PIMAGE_RESOURCE_DIRECTORY resDir, unsigned char *base,uint32_t level, uint32_t resourceType, int32_t beTypelib, int32_t *noRes,uint32_t *zOff, uint32_t *zSize);

int32_t genidl_pe_typelib_resource_count (FILE *fp)
{
  int32_t cnt = 0x2000;
  uint32_t zOff = 0,zSize = 0;
  size_t resRVA = 0;
  unsigned char *dta = NULL;
  size_t length = 0;
  if (!readResourceDirectory (fp, &dta, &length,&resRVA))
    return 0;
  if (!length || !dta)
    return 0;
  zOff = zSize = 0;
  walk_res_dir ((PIMAGE_RESOURCE_DIRECTORY) dta, dta,0, 0, 0, &cnt,&zOff,&zSize);
  free (dta);
  return 0x2000-cnt;
}

int32_t genidl_pe_typelib_resource_read (FILE *fp, int32_t noRes, unsigned char **pDta, size_t *szDta)
{
  uint32_t zOff,zSize;
  unsigned char *dta = NULL;
  size_t length = 0;
  size_t resRVA = 0;
  if (!readResourceDirectory (fp, &dta, &length, &resRVA))
    return 0;
  if (!length || !dta)
    return 0;
  zOff = zSize = 0;
  walk_res_dir ((PIMAGE_RESOURCE_DIRECTORY) dta, dta,0, 0, 0, &noRes,&zOff,&zSize);
  if (zOff != 0)
    {
      pDta[0] = (unsigned char *) malloc (zSize + 1);
      szDta[0] = zSize;

      memcpy (pDta[0], dta + zOff - resRVA , zSize);
      free (dta);
      return 1;
    }
  free (dta);
  return 0;
}

static void get_res_name_by_id(uint32_t id, unsigned char *resourceBase, char *buffer, uint32_t cBytes);
static void walk_res_entry(PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry, unsigned char *resourceBase, uint32_t level, int32_t beTypelib, int32_t *noRes,uint32_t *zOff,uint32_t *zSize);

static void
walk_res_dir (PIMAGE_RESOURCE_DIRECTORY resDir, unsigned char *base,uint32_t level, uint32_t resourceType, int32_t beTypelib, int32_t *noRes,uint32_t *zOff,uint32_t *zSize)
{
  PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry;
  char szType[64];
  uint32_t i;
  if (resourceType & IMAGE_RESOURCE_NAME_IS_STRING)
    get_res_name_by_id(resourceType, base,szType, sizeof(szType));
  else
    sprintf(szType, "%X", resourceType);
  if (!strcmp (szType,"TYPELIB"))
    beTypelib = 1;
  resDirEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(resDir+1);
  for ( i=0; i < resDir->NumberOfNamedEntries; i++, resDirEntry++)
    {
      walk_res_entry(resDirEntry, base, level+1, beTypelib, noRes,zOff,zSize);
      if (zOff[0] != 0)
	return;
    }

  for (i=0; i < resDir->NumberOfIdEntries; i++, resDirEntry++ )
    {
      walk_res_entry(resDirEntry, base, level+1, beTypelib, noRes,zOff,zSize);
      if (zOff[0] != 0)
	return;
    }
}

static void walk_res_entry(PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry, unsigned char *resourceBase, uint32_t level, int32_t beTypelib,int32_t *noRes,uint32_t *zOff,uint32_t *zSize)
{
    PIMAGE_RESOURCE_DATA_ENTRY pResDataEntry;
    
    if (resDirEntry->OffsetToData & IMAGE_RESOURCE_DATA_IS_DIRECTORY) {
        walk_res_dir ((PIMAGE_RESOURCE_DIRECTORY) ((resDirEntry->OffsetToData & 0x7FFFFFFF) + resourceBase),
            resourceBase, level, resDirEntry->Name, beTypelib, noRes,zOff,zSize);
	return;
    }

    if (!beTypelib)
      return;
    if(noRes[0] != 0)
    {
      noRes[0]-=1;
      return;
    }
    pResDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)
                    (resourceBase + resDirEntry->OffsetToData);
    zOff[0] = pResDataEntry->OffsetToData; /* RVA!!! */
    zSize[0] = pResDataEntry->Size;
}

static void get_res_name_by_id(uint32_t id, unsigned char *resourceBase, PSTR buffer, uint32_t cBytes)
{
    PIMAGE_RESOURCE_DIR_STRING_U prdsu;

    if ( !(id & IMAGE_RESOURCE_NAME_IS_STRING) )
    {
        sprintf(buffer, "%X", id);
        return;
    }
    
    id &= 0x7FFFFFFF;
    prdsu = (PIMAGE_RESOURCE_DIR_STRING_U)(resourceBase + id);

    WideCharToMultiByte(CP_ACP, 0, prdsu->NameString, prdsu->Length, buffer, cBytes, 0, 0);
    buffer[ min(cBytes-1,prdsu->Length) ] = 0;  // Null terminate it!!!
}

static int readResourceDirectory (FILE *fp, unsigned char **dta, size_t *length, size_t *resRVA)
{
  long pe_header;
  int be64;
  uImgHeader hdr;
  uint32_t res_size = 0;
  uint32_t sect_count;
  sImgSectionHdr sec;

  pe_header = genidl_ispe (fp, &be64);
  *dta = NULL; length[0]=0;
  if (!pe_header)
    return 0;
  fseek (fp, pe_header, SEEK_SET);
  if (be64)
  {
    fread (&hdr.hdr64, 1, sizeof (sImgNtHeaders64), fp);
    res_size = hdr.hdr64.OptionalHeader.DataDirectory[2].size;
    sect_count = hdr.hdr64.FileHeader.NumberOfSections;
  }
  else
  {
    fread (&hdr.hdr32, 1, sizeof (sImgNtHeaders32), fp);
    res_size = hdr.hdr32.OptionalHeader.DataDirectory[2].size;
    sect_count = hdr.hdr32.FileHeader.NumberOfSections;
  }
  if (!res_size)
    return 1;
  while (sect_count > 0)
    {
      fread (&sec, 1, sizeof (sImgSectionHdr),fp);
      if (!strcmp (sec.Name, ".rsrc"))
      {
	fseek (fp, (int32_t) sec.PointerToRawData, SEEK_SET);
	resRVA[0] = sec.VirtualAddress;
	dta[0] = (unsigned char *) malloc (res_size);
	fread (dta[0], 1, res_size, fp);
	length[0] = res_size;
	return 1;
      }
      sect_count--;
    }
  return 1;
}

int32_t
genidl_ispe (FILE *fp, int32_t *be64)
{
  sDosHeader hdr;
  uImgHeader img;

  *be64 = 0;
  fseek(fp, 0, SEEK_SET);
  if (fread (&hdr, 1, sizeof (hdr), fp) !=  sizeof (hdr))
    return 0;
  if (hdr.magic != 0x5a4d)
    return 0;
  if (hdr.lfanew == 0)
    return 0;
  fseek (fp, (int32_t) hdr.lfanew, SEEK_SET);
  if (fread (&img, 1, sizeof (img), fp) != sizeof (img))
    return 0;
  if (img.hdr32.Signature != 0x4550)
    return 0;
  if (img.hdr32.FileHeader.SizeOfOptionalHeader == IMG_SIZEOF_NT_OPTIONAL32_HEADER)
    *be64 = 0;
  else if (img.hdr32.FileHeader.SizeOfOptionalHeader == IMG_SIZEOF_NT_OPTIONAL64_HEADER)
    *be64 = 1;
  else
    return 0;
  return (int32_t) hdr.lfanew;
}
