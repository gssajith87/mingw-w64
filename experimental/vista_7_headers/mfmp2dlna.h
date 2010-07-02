#ifndef _INC_MFMP2DLNA
#define _INC_MFMP2DLNA

#if (_WIN32_WINNT >= 0x0601)
typedef struct _MFMPEG2DLNASINKSTATS {
  DWORDLONG cBytesWritten;
  BOOL      fPAL;
  DWORD     fccVideo;
  DWORD     dwVideoWidth;
  DWORD     dwVideoHeight;
  DWORDLONG cVideoFramesReceived;
  DWORDLONG cVideoFramesEncoded;
  DWORDLONG cVideoFramesSkipped;
  DWORDLONG cBlackVideoFramesEncoded;
  DWORDLONG cVideoFramesDuplicated;
  DWORD     cAudioSamplesPerSec;
  DWORD     cAudioChannels;
  DWORDLONG cAudioBytesReceived;
  DWORDLONG cAudioFramesEncoded;
} MFMPEG2DLNASINKSTATS;
#endif /*(_WIN32_WINNT >= 0x0601)*/

#endif /*_INC_MFMP2DLNA*/