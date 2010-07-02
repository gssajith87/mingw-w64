#ifndef _INC_WDSCLIENTAPI
#define _INC_WDSCLIENTAPI
#include <windows.h>
#if (_WIN32_WINNT >= 0x0600)

#define WDS_CLI_MSG_START 0
#define WDS_CLI_MSG_COMPLETE 1
#define WDS_CLI_MSG_PROGRESS 2
#define WDS_CLI_MSG_TEXT 3

/* CALLBACKS

VOID CALLBACK PFN_WdsCliCallback(
  __in      DWORD dwMessageId,
  __in_opt  WPARAM wParam,
  __in_opt  LPARAM lParam,
  __in_opt  PVOID pvUserData
);

VOID WDSCLIAPI PFN_WdsCliTraceFunction(
  __in  LPCWSTR pwszFormat,
  __in  va_list Params
);

*/

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_WDSCLIENTAPI*/
