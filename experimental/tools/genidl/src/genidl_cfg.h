#ifndef _GENIDL_H
#define _GENIDL_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <stdarg.h>
#include <stdint.h>

#if 0
typedef unsigned long long uint64_t;
typedef signed long long int64_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
#endif

typedef struct sCfgAlias {
  struct sCfgAlias *next;
  char name[1];
} sCfgAlias;

typedef struct sCfgItem {
  struct sCfgItem *next;
  char *type;
  char name[1];
} sCfgItem;

typedef struct sCfgLib {
  struct sCfgLib *next;
  sCfgAlias *alias;
  sCfgItem *item;
  char name[1];
} sCfgLib;

int genidl_read_config (const char *fname);
int genidl_save_config_fp (FILE *fp);
int genidl_save_config (const char *fname);
int genidl_ismodified_config (void);

int genidl_add_lib (const char *lib);
int genidl_add_lib_alias (const char *lib, const char *alias);
int genidl_add_lib_item (const char *lib, const char *name, const char *typ);
int genidl_del_lib_item (const char *lib);
const char *genidl_find_type (const char *lib, const char *name);

char *genidl_strlwr (char *s);

#endif
