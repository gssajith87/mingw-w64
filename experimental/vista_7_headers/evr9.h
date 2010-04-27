#ifndef _INC_EVR9
#define _INC_EVR9

#if (_WIN32_WINNT >= 0x0600)

typedef enum  {
  MFVideoAlphaBitmap_EntireDDS     = 0x00000001,
  MFVideoAlphaBitmap_SrcColorKey   = 0x00000002,
  MFVideoAlphaBitmap_SrcRect       = 0x00000004,
  MFVideoAlphaBitmap_DestRect      = 0x00000008,
  MFVideoAlphaBitmap_FilterMode    = 0x00000010,
  MFVideoAlphaBitmap_Alpha         = 0x00000020,
  MFVideoAlphaBitmap_BitMask       = 0x0000003f 
} MFVideoAlphaBitmapFlags;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_EVR9*/
