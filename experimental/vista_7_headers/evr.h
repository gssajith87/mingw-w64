#ifndef _INC_EVR
#define _INC_EVR

#if (_WIN32_WINNT >= 0x0600)
#if (_WIN32_WINNT >= 0x0601)

typedef enum _EVRFilterConfig_Prefs {
  EVRFilterConfigPrefs_EnableQoS   = 0x00000001,
  EVRFilterConfigPrefs_Mask        = 0x00000001 
} EVRFilterConfigPrefs;

#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum MFVideoAspectRatioMode {
  MFVideoARMode_None               = 0x00000000,
  MFVideoARMode_PreservePicture    = 0x00000001,
  MFVideoARMode_PreservePixel      = 0x00000002,
  MFVideoARMode_NonLinearStretch   = 0x00000004,
  MFVideoARMode_Mask               = 0x00000007 
} MFVideoAspectRatioMode;

#if (_WIN32_WINNT >= 0x0601)

typedef enum _MFVideoMixPrefs {
  MFVideoMixPrefs_ForceHalfInterlace         = 0x00000001,
  MFVideoMixPrefs_AllowDropToHalfInterlace   = 0x00000002,
  MFVideoMixPrefs_AllowDropToBob             = 0x00000004,
  MFVideoMixPrefs_ForceBob                   = 0x00000008,
  MFVideoMixPrefs_Mask                       = 0x0000000f 
} MFVideoMixPrefs;

#endif /*(_WIN32_WINNT >= 0x0601)*/

typedef enum MFVideoRenderPrefs {
  MFVideoRenderPrefs_DoNotRenderBorder       = 0x00000001,
  MFVideoRenderPrefs_DoNotClipToDevice       = 0x00000002,
  MFVideoRenderPrefs_AllowOutputThrottling   = 0x00000004,
  MFVideoRenderPrefs_ForceOutputThrottling   = 0x00000008,
  MFVideoRenderPrefs_ForceBatching           = 0x00000010,
  MFVideoRenderPrefs_AllowBatching           = 0x00000020,
  MFVideoRenderPrefs_ForceScaling            = 0x00000040,
  MFVideoRenderPrefs_AllowScaling            = 0x00000080,
  MFVideoRenderPrefs_DoNotRepaintOnStop      = 0x00000100,
  MFVideoRenderPrefs_Mask                    = 0x000000ff 
} MFVideoRenderPrefs;

Copy

typedef enum  {
  MFVP_MESSAGE_FLUSH                 = 0x00000000,
  MFVP_MESSAGE_INVALIDATEMEDIATYPE   = 0x00000001,
  MFVP_MESSAGE_PROCESSINPUTNOTIFY    = 0x00000002,
  MFVP_MESSAGE_BEGINSTREAMING        = 0x00000003,
  MFVP_MESSAGE_ENDSTREAMING          = 0x00000004,
  MFVP_MESSAGE_ENDOFSTREAM           = 0x00000005,
  MFVP_MESSAGE_STEP                  = 0x00000006,
  MFVP_MESSAGE_CANCELSTEP            = 0x00000007 
} MFVP_MESSAGE_TYPE;



#endif /*(_WIN32_WINNT >= 0x0600)*/

#endif /*_INC_EVR*/
