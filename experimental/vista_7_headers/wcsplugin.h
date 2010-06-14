#ifndef _INC_WCSPLUGIN
#define _INC_WCSPLUGIN
#if (_WIN32_WINNT >= 0x0600)

typedef struct _BlackInformation {
  WINBOOL  bBlackOnly;
  FLOAT blackWeight;
} BlackInformation;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WCSPLUGIN*/
