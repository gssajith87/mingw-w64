#ifndef _M_MS_HXX
#define _M_MS_HXX

#include "m_token.h"

#define ENCODING_TYPE_MS	1

typedef struct sCached {
  int count;
  uMToken *arr[10];
} sCached;

typedef struct sMSCtx {
  const char *name;
  const char *end;
  const char *pos;
  int err;
  int fExplicitTemplateParams;
  int fGetTemplateArgumentList;
  sCached *pZNameList;
  sCached *pTemplateArgList;
  sCached *pArgList;
} sMSCtx;

#define GET_CHAR(CTX)	((CTX)->pos == (CTX)->end ? 0 : (CTX)->pos[0])
#define INC_CHAR(CTX)	do { if ((CTX)->pos != (CTX)->end) (CTX)->pos++; } while (0)
#define DEC_CHAR(CTX)   do { if ((CTX)->pos != (CTX)->name) (CTX)->pos--; } while (0)
#define SKIP_CHAR(CTX,LEN) do { (CTX)->pos += (LEN); if ((CTX)->pos > (CTX)->end) (CTX)->pos=(CTX)->end; } while (0)

uMToken *decode_ms_name (const char *name);
int encode_ms_name (uMToken *tok);

#endif
