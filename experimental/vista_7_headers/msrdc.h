#ifndef _INC_MSRDC
#define _INC_MSRDC
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)
typedef LPVOID SimilarityFileIndexT;

typedef struct _FindSimilarFileIndexResults {
  SimilarityFileIndexT m_FileIndex;
  unsigned             m_MatchCount;
} FindSimilarFileIndexResults;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif _INC_MSRDC
