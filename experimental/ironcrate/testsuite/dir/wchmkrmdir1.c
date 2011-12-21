#include "../testlib/main_test.c"
#include <errno.h>
#include <stdlib.h>

typedef int (*ffct)(const wchar_t *);
#define TSTNAME L"abc"

static int
test_dirlen (ffct fchdir, ffct fmkdir, ffct frmdir)
{
  int m;
  if (fmkdir (TSTNAME))
   return 0;
  if (fchdir (TSTNAME))
    return 0;
  m = test_dirlen (fchdir, fmkdir, frmdir);
  fchdir (L"..");
  frmdir (TSTNAME);
  return m + 4;
}

/* int __cdecl _wchdir (const wchar_t *path).

   Flow-graph:
	(1) Max path length is 260.
	(2) If path is NULL, errno is IC_EINVAL and doserrno is 0. Return -1
	(3) On invalid path errno is and return -1
	(4) On success and not an UNC path, environment-variable =<drive>:
	    is set to path.
*/

int
ic_test_main (int seq, int flags)
{
  int ok;
  int (*fct)(const wchar_t *) =
	ic_test_getsymbol ("_wchdir");
  int (*fmkdir)(const wchar_t *) =
	ic_test_getsymbol ("_wmkdir");
  int (*frmdir)(const wchar_t *) =
	ic_test_getsymbol ("_wrmdir");
  unsigned long * (*fdoserrno)(void) =
        ic_test_getsymbol ("__doserrno");

  if (!fct || !fmkdir || !frmdir || !fdoserrno)
    return IC_TEST_RSLT_UNSUPPORTED;
  switch (seq)
  {
    case 0:
      ic_test_reset_internal_vars ();
      /* Test for max-path */
      IC_TEST_CHECK (test_dirlen (fct, fmkdir, frmdir) <= 260);
      IC_TEST_CHECK (fct (NULL) == -1 && errno == EINVAL && *(fdoserrno()) == 0);
      IC_TEST_CHECK (fct (L"Invalid Directory") == -1 && errno == ENOENT);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}
