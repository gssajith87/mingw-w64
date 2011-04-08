#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <setjmp.h>
#include <signal.h>
#include "testlib.h"

int ic_test_invalid_parameter_called = 0;
int ic_test_segfault = 0;
const char *ic_test_msvcrt_name = "msvcrt";
const char *ic_test_testname = NULL;

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

static int ic_test_subtest_cnt = 0;
static int ic_test_subtest_failed = 0;

static int ic_test_show_test (int cond, const char *expr)
{
  fprintf (stderr, "  Sub test %d of %s: \"%s\" %s\n",
	ic_test_subtest_cnt + 1, ic_test_testname,
	expr, (cond ? "OK" : "FAILED"));
  ic_test_subtest_cnt++;
  if (!cond) ic_test_subtest_failed++;
  return 1;
}

void ic_test_reset_internal_vars (void)
{
  ic_test_segfault = 0;
  ic_test_invalid_parameter_called = 0;
}

#ifdef TEST_APP
int ic_test_main (int seq, int flags)
{
  if (seq == 0) memcpy ((void *) (intptr_t) 1, "ab", 2);
  else if (seq == 1) return IC_TEST_RSLT_OK;
  else return IC_TEST_RSLT_SUCCESS;
  return IC_TEST_RSLT_FAILED;
}
#endif

void *ic_test_getsymbol (const char *name)
{
  static HMODULE hmod = NULL;
  if (!name || *name == 0) return NULL;
  if (!hmod)
    hmod = GetModuleHandle (ic_test_msvcrt_name);
  if (!hmod)
    hmod = LoadLibrary (ic_test_msvcrt_name);
  if (!hmod)
  {
    fprintf (stderr, "Failed to open ,%s'\n", ic_test_msvcrt_name);
    return NULL;
  }
  return GetProcAddress (hmod, name);
}

int main(int argc, char **argv)
{
  int r = IC_TEST_RSLT_OK, no = 0;
  int flags = 0;
  void (*ipfh)(_invalid_parameter_handler);
  const char *n1, *n2;

  /* Get test's name.  */
  n1 = strrchr (argv[0], '\\');
  n2 = strrchr (argv[0], '/');
  if (!n1 && !n2) ic_test_testname = argv[0];
  else if (!n1) ic_test_testname = n2 + 1;
  else if (!n2) ic_test_testname = n1 + 1;
  else if (n1 < n2) ic_test_testname = n2 + 1;
  else ic_test_testname = n1 + 1;

  if (argc > 1)
    ic_test_msvcrt_name = argv[1];

  ipfh = ic_test_getsymbol ("_set_invalid_parameter_handler");
  signal (SIGSEGV, catchSigSegV);
  if (ipfh) (*ipfh) (my_invalid_parameter_handler);
  else flags |= IC_TEST_NO_INVALID_PARA_HANDLER;
  while (r == IC_TEST_RSLT_OK)
  {
    if (!setjmp (buf))
    {
      r = ic_test_main (no, flags);
    }
    ++no;
  }
  if (ic_test_subtest_failed != 0) r = IC_TEST_RSLT_FAILED;
  if (ic_test_subtest_cnt == 0) r = IC_TEST_RSLT_UNSUPPORTED;
  fprintf (stderr, "TEST %s (%d of %d): ", ic_test_testname,
	(r == IC_TEST_RSLT_SUCCESS ? ic_test_subtest_cnt : ic_test_subtest_failed),
	ic_test_subtest_cnt);
  switch (r)
  {
    case IC_TEST_RSLT_SUCCESS: fprintf (stderr, "OK"); break;
    case IC_TEST_RSLT_FAILED: fprintf (stderr, "FAILED"); break;
    case IC_TEST_RSLT_UNSUPPORTED: fprintf (stderr, "UNSUPPORTED"); break;
    default: fprintf (stderr, "???%d???", r); break;
  }
  fprintf (stderr, "\n");

  return r;
}

