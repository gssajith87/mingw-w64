#ifndef _INC_MUILOAD
#define _INC_MUILOAD
#include <windows.h>

WINBOOL WINAPI FreeMUILibrary(
  HMODULE hResModule
);

HINSTANCE WINAPI LoadMUILibrary(
  LPCTSTR pszFullModuleName,
  DWORD dwLangConvention,
  LANGID LangID
);

#endif /*_INC_MUILOAD*/
