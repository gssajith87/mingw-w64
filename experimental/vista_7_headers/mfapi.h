#ifndef _INC_MFAPI
#define _INC_MFAPI

#if (_WIN32_WINNT >= 0x0600)

typedef enum  {
  MF_TOPOSTATUS_INVALID           = 0,
  MF_TOPOSTATUS_READY             = 100,
  MF_TOPOSTATUS_STARTED_SOURCE    = 200,
  MF_TOPOSTATUS_DYNAMIC_CHANGED   = 210,
  MF_TOPOSTATUS_SINK_SWITCHED     = 300,
  MF_TOPOSTATUS_ENDED             = 400 
} MF_TOPOSTATUS;

typedef enum _MFVideoDRMFlags {
  MFVideoDRMFlag_None                 = 0,
  MFVideoDRMFlag_AnalogProtected      = 1,
  MFVideoDRMFlag_DigitallyProtected   = 2 
} MFVideoDRMFlags;


#if (_WIN32_WINNT >= 0x0601)
typedef enum  {
  MF_STANDARD_WORKQUEUE   = 0,
  MF_WINDOW_WORKQUEUE     = 1 
} MFASYNC_WORKQUEUE_TYPE;
#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum _MFVideoPadFlags {
  MFVideoPadFlag_PAD_TO_None   = 0,
  MFVideoPadFlag_PAD_TO_4x3    = 1,
  MFVideoPadFlag_PAD_TO_16x9   = 2 
} MFVideoPadFlags;

typedef enum _MFVideoSrcContentHintFlags {
  MFVideoSrcContentHintFlag_None    = 0,
  MFVideoSrcContentHintFlag_16x9    = 1,
  MFVideoSrcContentHintFlag_235_1   = 2 
} MFVideoSrcContentHintFlags;

typedef enum _MFWaveFormatExConvertFlags {
  MFWaveFormatExConvertFlag_Normal            = 0,
  MFWaveFormatExConvertFlag_ForceExtensible   = 1 
} MFWaveFormatExConvertFlags;


#endif  /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_MFAPI*/
