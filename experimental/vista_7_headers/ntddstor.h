#ifndef _INC_NTDDSTOR
#define _INC_NTDDSTOR
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef struct _STORAGE_READ_CAPACITY {
  ULONG         Version;
  ULONG         Size;
  ULONG         BlockLength;
  LARGE_INTEGER NumberOfBlocks;
  LARGE_INTEGER DiskLength;
} STORAGE_READ_CAPACITY, *PSTORAGE_READ_CAPACITY;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_NTDDSTOR*/
