#ifndef _DBG_MEMFILE_HXX
#define _DBG_MEMFILE_HXX

#include <stdarg.h>

typedef struct sDbgMemFile
{
  unsigned int ref_cnt;
  char name[1024];
  size_t size;
  unsigned char *data;
} sDbgMemFile;

sDbgMemFile *dbg_memfile_open (const char *filename);
sDbgMemFile *dbg_memfile_create (const char *name, size_t size);
int dbg_memfile_retain (sDbgMemFile *pDFile);
int dbg_memfile_release (sDbgMemFile *pDFile);
int dbg_memfile_save (sDbgMemFile *pDFile, const char *filename);
int dbg_memfile_write (sDbgMemFile *pDFile, size_t off, const unsigned char *dta, size_t len);
int dbg_memfile_read (const sDbgMemFile *pDFile, size_t off, unsigned char *dta, size_t len);
size_t dbg_memfile_getsize (sDbgMemFile *pDFile);
const char *dbg_memfile_getname (sDbgMemFile *pDFile);
int dbg_memfile_setname (sDbgMemFile *pDFile, const char *name);

sDbgMemFile *dbg_memfile_dump (sDbgMemFile *pDFile);
void dbg_memfile_dump_in (sDbgMemFile *pText, sDbgMemFile *pDFile);

/* text stream emulation methods.  */
sDbgMemFile *dbg_memfile_create_text (const char *name);
int dbg_memfile_printf (sDbgMemFile *pDFile, const char *fmt, ...);
int dbg_memfile_vprintf (sDbgMemFile *pDFile, const char *fmt, va_list argp);

#endif
