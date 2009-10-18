#ifndef _GENIDL_READPE_H
#define _GENIDL_READPE_H

#pragma pack(push,1)

typedef struct sDosHeader {
  uint16_t magic;
  uint16_t cblp;
  uint16_t cp;
  uint16_t crlc;
  uint16_t cparhdr;
  uint16_t minalloc;
  uint16_t maxalloc;
  uint16_t ss;
  uint16_t sp;
  uint16_t csum;
  uint16_t ip;
  uint16_t cs;
  uint16_t lfarlc;
  uint16_t ovno;
  uint16_t res[4];
  uint16_t oemid;
  uint16_t oeminfo;
  uint16_t res2[10];
  int32_t lfanew;
} sDosHeader;

typedef struct sImgDataDir {
  uint32_t virtualAddress;
  uint32_t size;
} sImgDataDir;

#define IMG_NOOF_DIR_ENTRIES 16

typedef struct sImgOptionalHeaders32 {
  uint16_t Magic;
  unsigned char MajorLinkerVersion;
  unsigned char MinorLinkerVersion;
  uint32_t SizeOfCode;
  uint32_t SizeOfInitializedData;
  uint32_t SizeOfUninitializedData;
  uint32_t AddressOfEntryPoint;
  uint32_t BaseOfCode;
  uint32_t BaseOfData;
  uint32_t ImageBase;
  uint32_t SectionAlignment;
  uint32_t FileAlignment;
  uint16_t MajorOperatingSystemVersion;
  uint16_t MinorOperatingSystemVersion;
  uint16_t MajorImageVersion;
  uint16_t MinorImageVersion;
  uint16_t MajorSubsystemVersion;
  uint16_t MinorSubsystemVersion;
  uint32_t Win32VersionValue;
  uint32_t SizeOfImage;
  uint32_t SizeOfHeaders;
  uint32_t CheckSum;
  uint16_t Subsystem;
  uint16_t DllCharacteristics;
  uint32_t SizeOfStackReserve;
  uint32_t SizeOfStackCommit;
  uint32_t SizeOfHeapReserve;
  uint32_t SizeOfHeapCommit;
  uint32_t LoaderFlags;
  uint32_t NumberOfRvaAndSizes;
  sImgDataDir DataDirectory[IMG_NOOF_DIR_ENTRIES];
} sImgOptionalHeaders32;

typedef struct sImgOptionalHeaders64 {
  uint16_t Magic;
  unsigned char MajorLinkerVersion;
  unsigned char MinorLinkerVersion;
  uint32_t SizeOfCode;
  uint32_t SizeOfInitializedData;
  uint32_t SizeOfUninitializedData;
  uint32_t AddressOfEntryPoint;
  uint32_t BaseOfCode;
  uint64_t ImageBase;
  uint32_t SectionAlignment;
  uint32_t FileAlignment;
  uint16_t MajorOperatingSystemVersion;
  uint16_t MinorOperatingSystemVersion;
  uint16_t MajorImageVersion;
  uint16_t MinorImageVersion;
  uint16_t MajorSubsystemVersion;
  uint16_t MinorSubsystemVersion;
  uint32_t Win32VersionValue;
  uint32_t SizeOfImage;
  uint32_t SizeOfHeaders;
  uint32_t CheckSum;
  uint16_t Subsystem;
  uint16_t DllCharacteristics;
  uint64_t SizeOfStackReserve;
  uint64_t SizeOfStackCommit;
  uint64_t SizeOfHeapReserve;
  uint64_t SizeOfHeapCommit;
  uint32_t LoaderFlags;
  uint32_t NumberOfRvaAndSizes;
  sImgDataDir DataDirectory[IMG_NOOF_DIR_ENTRIES];
} sImgOptionalHeaders64;

typedef struct sImgFileHeader {
  uint16_t Machine;
  uint16_t NumberOfSections;
  uint32_t TimeDateStamp;
  uint32_t PointerToSymbolTable;
  uint32_t NumberOfSymbols;
  uint16_t SizeOfOptionalHeader;
  uint16_t Characteristics;
} sImgFileHeader;

#define IMG_SIZEOF_NT_OPTIONAL32_HEADER 224
#define IMG_SIZEOF_NT_OPTIONAL64_HEADER 240

typedef struct sImgNtHeaders64 {
  uint32_t Signature;
  sImgFileHeader FileHeader;
  sImgOptionalHeaders64 OptionalHeader;
} sImgNtHeaders64;

typedef struct sImgNtHeaders32 {
  uint32_t Signature;
  sImgFileHeader FileHeader;
  sImgOptionalHeaders32 OptionalHeader;
} sImgNtHeaders32;

typedef union uImgHeader {
  sImgNtHeaders32 hdr32;
  sImgNtHeaders64 hdr64;
} uImgHeader;

#define IMG_FIRST_SECTION(ntheader) ((sImgSectionHdr *) ((ULONG_PTR)ntheader + FIELD_OFFSET(IMAGE_NT_HEADERS,OptionalHeader) + ((PIMAGE_NT_HEADERS)(ntheader))->FileHeader.SizeOfOptionalHeader))

typedef struct sImgSectionHdr {
  unsigned char Name[8];
  union {
    uint32_t PhysicalAddress;
    uint32_t VirtualSize;
  } Misc;
  uint32_t VirtualAddress;
  uint32_t SizeOfRawData;
  uint32_t PointerToRawData;
  uint32_t PointerToRelocations;
  uint32_t PointerToLinenumbers;
  uint16_t NumberOfRelocations;
  uint16_t NumberOfLinenumbers;
  uint32_t Characteristics;
} sImgSectionHdr;

long genidl_ispe (FILE *fp, int *be64);
int genidl_pe_typelib_resource_read (FILE *fp, int noRes, unsigned char **pDta, size_t *szDta);
int genidl_pe_typelib_resource_count (FILE *fp);

#pragma pack(pop)

#endif
