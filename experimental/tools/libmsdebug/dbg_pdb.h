#ifndef _DBG_PDB_HXX
#define _DBG_PDB_HXX

#include "stdint.h"

#pragma pack(push,1)

/* Constants for unused streams.  */
#define PDB_UNUSED_16       ((uint16_t) -1)
#define PDB_UNUSED_32       ((uint32_t) -1)

/* Type index base/limit.  */
#define PDB_TI_MIN          0x00001000
#define PDB_TI_MAX          0x00FFFFFF

typedef struct sPdbStream2
{
  uint32_t streamBytes;	/* stream size (-1 = unused).  */
  uint32_t reserved;	/* implementation dependent.  */
} sPdbStream2;

#define PDB_STREAM_UNUSED	((uint32_t) 0xffffffffU)

typedef struct sPdbHeader2
{
  char signature[0x2c];		/* version ID.  */
  uint32_t pageBytes;		/* 0x0400, 0x0800, 0x1000.  */
  uint16_t startPage;		/* 0x0009, 0x0005, 0x0002.  */
  uint16_t filePages;		/* file size / pageBytes.  */
  sPdbStream2 rootStream;	/* stream directory.  */
  uint16_t rootPages[];		/* pages containing sPdbRoot_2.  */
} sPdbHeader2;

typedef struct sPdbHeader7
{
  char signature[0x20];		/* version ID.  */
  uint32_t pageBytes;		/* 0x0400.  */
  uint32_t flagPage;		/* 0x0002.  */
  uint32_t filePages;		/* file size / dPageBytes.  */
  uint32_t rootBytes;		/* stream directory size.  */
  uint32_t reserved;		/* 0.  */
  uint32_t indexPages[];		/* root page index pages.  */
} sPdbHeader7;

typedef struct sPdbRoot2
{
  uint16_t nstreams;		/* number of streams.  */
  uint16_t reserved;		/* not used.  */
  sPdbStream2 streams[];	/* stream size list.  */
} sPdbRoot2;

typedef struct sPdbRoot7
{
  uint32_t nstreams;		/* number of streams.  */
  uint32_t streamBytes[];	/* stream size list.  */
} sPdbRoot7;

#pragma pack(pop)

#endif
