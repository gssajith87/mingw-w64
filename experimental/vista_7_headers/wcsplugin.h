#ifndef _INC_WCSPLUGIN
#define _INC_WCSPLUGIN
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef struct _BlackInformation {
  WINBOOL  bBlackOnly;
  FLOAT blackWeight;
} BlackInformation;

typedef struct _JabColorF {
  FLOAT J;
  FLOAT a;
  FLOAT b;
} JabColorF;

typedef struct _PrimaryJabColors {
  JabColorF red;
  JabColorF yellow;
  JabColorF green;
  JabColorF cyan;
  JabColorF blue;
  JabColorF magenta;
  JabColorF black;
  JabColorF white;
} PrimaryJabColors;

typedef struct _GamutShellTriangle {
  UINT aVertexIndex[3];
} GamutShellTriangle;

typedef struct _GamutShell {
  FLOAT                                    JMin;
  FLOAT                                    JMax;
  UINT                                     cVertices;
  UINT                                     cTriangles;
  JabColorF                                *pVertices;
  GamutShellTriangle                       *pTriangles;
} GamutShell;

typedef struct _GamutBoundaryDescription {
  PrimaryJabColors                      primaries;
  UINT                                 cNeutralSamples
  JabColorF                            *pNeutralSamples;
  GamutShell                           *pReferenceShell;
  GamutShell                           *pPlausibleShell;
  GamutShell                           *pPossibleShell;
} GamutBoundaryDescription;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WCSPLUGIN*/
