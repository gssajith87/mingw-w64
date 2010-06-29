#ifndef _INC_FUNCTIONDISCOVERYCONSTRAINTS
#define _INC_FUNCTIONDISCOVERYCONSTRAINTS
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

typedef enum tagPropertyConstraint {
  QC_EQUALS               = 0,
  QC_NOTEQUAL             = 1,
  QC_LESSTHAN             = 2,
  QC_LESSTHANOREQUAL      = 3,
  QC_GREATERTHAN          = 4,
  QC_GREATERTHANOREQUAL   = 5,
  QC_STARTSWITH           = 6,
  QC_EXISTS               = 7,
  QC_DOESNOTEXIST         = 8,
  QC_CONTAINS             = 8 
} PropertyConstraint;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_FUNCTIONDISCOVERYCONSTRAINTS*/
