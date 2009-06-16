#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "dbg_memfile.h"

static int get_vprintf_len (const char *fmt, va_list argp);

sDbgMemFile *
dbg_memfile_open (const char *filename)
{
  FILE *fp;
  size_t size;
  sDbgMemFile *ret = NULL;

  if (!filename || filename[0] == 0)
    return NULL;
  fp = fopen (filename, "rb");
  if (!fp)
    return NULL;
  fseek (fp, 0, SEEK_END);
  size = (size_t) ftell (fp);
  fseek (fp, 0, SEEK_SET);
  ret = dbg_memfile_create (filename, size);
  if (!ret)
    {
      fclose (fp);
      return NULL;
    }
  fread (ret->data, 1, size, fp);
  fclose (fp);
  return ret;
}

sDbgMemFile *
dbg_memfile_create (const char *name, size_t size)
{
  sDbgMemFile *ret = NULL;
  if (!name)
    return NULL;
  ret = (sDbgMemFile *) malloc (sizeof (sDbgMemFile));
  if (!ret)
    return NULL;
  memset (ret, 0, sizeof (sDbgMemFile));
  
  dbg_memfile_retain (ret);
  ret->size = size;
  ret->data = (unsigned char*) malloc (size + 1);
  if (ret->data == NULL)
    {
      dbg_memfile_release (ret);
      return NULL;
    }
  dbg_memfile_setname (ret, name);
  return ret;
}

int
dbg_memfile_retain (sDbgMemFile *pDFile)
{
  if (!pDFile)
    return -1;
  pDFile->ref_cnt += 1;
  return 0;
}

int
dbg_memfile_release (sDbgMemFile *pDFile)
{
  if (!pDFile)
    return -1;
  pDFile->ref_cnt -= 1;
  if (pDFile->ref_cnt == 0)
    {
      if (pDFile->data)
        free (pDFile->data);
      memset (pDFile, 0, sizeof (sDbgMemFile));
      return 0;
    }
  return 1;
}

int
dbg_memfile_save (sDbgMemFile *pDFile, const char *filename)
{
  FILE *fp;
  if (!pDFile || !filename || filename[0] == 0)
    return -1;
  fp = fopen (filename, "wb");
  if (!fp)
    return -2;
  fwrite (pDFile->data, 1, pDFile->size, fp);
  fclose (fp);
  return 0;
}

int
dbg_memfile_write (sDbgMemFile *pDFile, size_t off, const unsigned char *dta, size_t len)
{
  if (!pDFile)
    return -1;
  if (pDFile->size < (off + len))
    {
      unsigned char *d = (unsigned char *) realloc (pDFile->data, (off + len));
      if (!d)
        return -3;
      pDFile->data = d;
      memset (pDFile->data + pDFile->size, 0, (off + len) - pDFile->size);
      pDFile->size = off + len;
    }
  if (!dta || !len)
    return (int) len;
  memcpy (pDFile->data + off, dta, len);
  return (int) len;
}

int
dbg_memfile_read (const sDbgMemFile *pDFile, size_t off, unsigned char *dta, size_t len)
{
  if (!pDFile)
    return -1;
  if (!dta)
    return -2;
  if (!len)
    return 0;
  if (pDFile->size <= off)
    {
      memset (dta, 0, len);
      return 0;
    }
  if ((pDFile->size - off) < len)
    {
      memset (dta + (pDFile->size - off), 0, len - (pDFile->size - off));
      len = (pDFile->size - off);
    }
  memcpy (dta, &(pDFile->data[off]), len);
  return (int) len;
}

size_t
dbg_memfile_getsize (sDbgMemFile *pDFile)
{
  if (!pDFile)
    return 0;
  return pDFile->size;
}

const char *
dbg_memfile_getname (sDbgMemFile *pDFile)
{
  if (!pDFile)
    return NULL;
  return &(pDFile->name[0]);
}

int
dbg_memfile_setname (sDbgMemFile *pDFile, const char *name)
{
   size_t len;
  if (!pDFile)
    return -1;
  if (!name)
    return -2;
  len = strlen (name);
  
  if (len >= 1024)
    {
      name += (len - 1023);
      len = 1023;
    }
  strcpy (pDFile->name, name);
  return 0;
}

int
dbg_memfile_printf (sDbgMemFile *pDFile, const char *fmt, ...)
{
  va_list argp;
  va_start (argp, fmt);
  dbg_memfile_vprintf (pDFile, fmt, argp);
  va_end (argp);
  return 0;
}

int
dbg_memfile_vprintf (sDbgMemFile *pDFile, const char *fmt, va_list argp)
{
  char *h;
  int len;
  if (!pDFile)
    return 0;
  len = get_vprintf_len (fmt, argp);
  if (!len)
    return 0;
  h = (char *) malloc (len + 1);
  if (!h)
    return 0;
  vsprintf (h, fmt, argp);
  dbg_memfile_write (pDFile, (pDFile->size == 0 ? 0 : pDFile->size - 1), (const unsigned char *) h, strlen (h) + 1);
  free (h);
  return 0;
}

static int get_vprintf_len (const char *fmt, va_list argp)
{
  static FILE *fpNul = NULL;
  int len;

  if (!fpNul)
    {
#ifdef _WIN32
      fpNul = fopen ("NUL","wt");
#else
      fpNul = fopen ("/dev/null","w");
#endif
      if (!fpNul)
	return 0;
    }
  len = vfprintf (fpNul, fmt, argp);
  return (len < 0 ? 0 : (len + 2));
}

sDbgMemFile *
dbg_memfile_create_text (const char *name)
{
  return dbg_memfile_create ((name && name[0] != 0 ? name : "<text>"), 1);
}

sDbgMemFile *
dbg_memfile_dump (sDbgMemFile *pDFile)
{
  sDbgMemFile *ret;
  size_t size, i, k;

  ret = dbg_memfile_create_text ("dump");
  if (!pDFile)
    return ret;
  dbg_memfile_dump_in (ret, pDFile);
  return ret;
}

void
dbg_memfile_dump_in (sDbgMemFile *pText, sDbgMemFile *pDFile)
{
  size_t size, i, k;

  if (!pDFile || !pText)
    return;
  dbg_memfile_printf (pText, "Dump of '%s':\n", dbg_memfile_getname (pDFile));
  size = dbg_memfile_getsize (pDFile);
  for (i = 0; i < size;)
    {
      char s[17];
      dbg_memfile_printf (pText, "0x%08x:", (unsigned int) i);
      for (k = 0;k < 16 && i < size; k++, i++)
        {
          dbg_memfile_printf (pText, " %02X", pDFile->data[i]);
          s[k] = (pDFile->data[i] >= 0x20 && pDFile->data[i] <= 0x7f) ? pDFile->data[i] : '.';
        }
      s[k]=0;
      dbg_memfile_printf (pText, " - %s\n", s);
    }
}
