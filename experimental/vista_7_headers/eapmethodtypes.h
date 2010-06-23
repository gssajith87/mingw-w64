#ifndef _INC_EAPMETHODTYPES
#define _INC_EAPMETHODTYPES
#if (_WIN32_WINNT >= 0x0600)
#include <windows.h>
#include <eaptypes.h>

typedef struct tagEapPacket {
  BYTE Code;
  BYTE Id;
  BYTE Length[2];
  BYTE Data[1];
} EapPacket;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EAPMETHODTYPES*/
