#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <setjmp.h>
#include <signal.h>

int ic_test_invalid_parameter_called = 0;
int ic_test_segfault = 0;

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

extern int ic_test_main (int seq);

int ic_test_main (int seq)
{
  if (seq == 0) memcpy ((void *) (intptr_t) 1, "ab", 2);
  else  return 0;
  return 1;
}

int main(int argc, char **argv)
{
  int r, no = 0;
  void (*ipfh)(_invalid_parameter_handler);
  ipfh = GetProcAddress (GetModuleHandle ("msvcrt"), "_set_invalid_parameter_handler");
  signal (SIGSEGV, catchSigSegV);
  if (ipfh) (*ipfh) (my_invalid_parameter_handler);
  while (1) {
  if (!setjmp (buf))
  {
    r = ic_test_main (no);
    break;
  }
  else
   ++no;
  }
  fprintf (stderr, "TEST: %s\n", (r == 0 ? "OK" : (r == -1 ? "SKIP" : "FAILED")));

  return r;
}

