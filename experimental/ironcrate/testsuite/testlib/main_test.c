#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <setjmp.h>
#include <signal.h>
#include "testlib.h"

#define IC_TEST_NO_INVALID_PARA_HANDLER	1

extern int ic_test_main (int seq, int flags);
extern void *ic_test_getsymbol (const char *name);

int ic_test_invalid_parameter_called = 0;
int ic_test_segfault = 0;
const char *ic_test_msvcrt_name = "msvcrt";

static jmp_buf buf;

static void my_invalid_parameter_handler (const wchar_t *exp, const wchar_t *p1, const wchar_t *p2, unsigned int l1, uintptr_t l2)
{
  fprintf (stderr, "INVALID_HANDLER: %ws %ws %ws %u %Iu\n",
   (!exp ? L"" : exp), (!p1 ? L"" : p1), (!p2 ? L"" : p2), l1, l2);
  ++ic_test_invalid_parameter_called;
}

static void catchSigSegV( int sig )
{
 ++ic_test_segfault;
 longjmp(buf, 1);
}

int ic_test_main (int seq, int flags)
{
  if (seq == 0) memcpy ((void *) (intptr_t) 1, "ab", 2);
  else  return 0;
  return 1;
}

void *ic_test_getsymbol (const char *name)
{
  if (!name || *name == 0) return NULL;
  return GetProcAddress (GetModuleHandle (ic_test_msvcrt_name), name);
}

int main(int argc, char **argv)
{
  int r, no = 0;
  int flags = 0;
  void (*ipfh)(_invalid_parameter_handler);
  if (argc > 1)
    ic_test_msvcrt_name = argv[1];

  ipfh = ic_test_getsymbol ("_set_invalid_parameter_handler");
  signal (SIGSEGV, catchSigSegV);
  if (ipfh) (*ipfh) (my_invalid_parameter_handler);
  else flags |= IC_TEST_NO_INVALID_PARA_HANDLER;
  while (1) {
  if (!setjmp (buf))
  {
    r = ic_test_main (no, flags);
    break;
  }
  else
   ++no;
  }
  fprintf (stderr, "TEST: %s\n", (r == 0 ? "OK" : (r == -1 ? "SKIP" : "FAILED")));

  return r;
}

