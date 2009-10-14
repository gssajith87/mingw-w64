#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <dbghelp.h>
#ifdef HAVE_LIBMANGLE_H
#include <libmangle.h>
#endif

#define output_buffer 100
#ifndef __GNUC__
#pragma comment (lib,"Dbghelp.lib")
#endif

int
main (int argc, char **argv)
{
  int err, i = 1;
  char *buff;
  
  fprintf (stderr, "\nms_demangler\n\n");

  if (argc <= 1)
  {
    printf ("Usage: %s EncodedNames1 EncodedNames2 ...\n", *argv);
    return 1;
  }

  while (argv && argv[i])
  {
    buff = calloc (output_buffer, sizeof (char));
    if (!buff) 
    {
      printf ("calloc() error.\n");
      abort();
    }
    
    if (UnDecorateSymbolName ( argv[i], buff, output_buffer, UNDNAME_COMPLETE))
      printf ("%s\n%s\n\n", argv[i], buff);
    else
    {
    err = GetLastError();
    fprintf (stderr, "UnDecorateSymbolName returned error %d\n", err);
    }

    free (buff);
    i++;
  }
  
  return 0;
}
