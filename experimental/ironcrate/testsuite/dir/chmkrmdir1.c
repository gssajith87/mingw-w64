#include "../testlib/main_test.c"
#include <errno.h>
#include <stdlib.h>

typedef int (*ffct)(const char *);
#define TSTNAME "abcdef"
#define TSTNAMELEN 7

static int
get_env_var (char *d, size_t dn)
{
  char s[4];
  s[0] = '=';
  s[1] = 'A' + _getdrive () - 1;
  s[2] = ':';
  s[3] = 0;
  if (!GetEnvironmentVariableA (s, d, dn))
    return 0;
  return 1;
}

static int
test_dirlen (ffct fchdir, ffct fmkdir, ffct frmdir)
{
  int m;
  if (fmkdir (TSTNAME))
   return 0;
  if (fchdir (TSTNAME))
    return 0;
  m = test_dirlen (fchdir, fmkdir, frmdir);
  fchdir ("..");
  frmdir (TSTNAME);
  return m + TSTNAMELEN;
}

static int
test_env_var (ffct fchdir, ffct fmkdir, ffct frmdir)
{
  char s1[MAX_PATH], s2[MAX_PATH], *p1, *p2;
  if (!get_env_var (s1, MAX_PATH))
    return 0;
  fmkdir ("a");
  if (fchdir ("a"))
    return 0;
  if (!get_env_var (s2, MAX_PATH))
    return 0;
  fchdir ("..");
  frmdir ("a");
  p1 = s1; p2 = s2;
  while (*p1 != 0 && *p2 != 0)
    {
      if (*p1 == *p2
          || ((*p1 == '\\' || *p1 == '/') && (*p2 == '\\' || *p2 == '/')))
        {
	  p1++, p2++;
	  continue;
	}
      break;
    }
  if (*p1 != 0)
    return 0;
  if (*p2 == '\\' || *p2 == '/')
    p2++;
  if (*p2 != 'a')
    return 0;
  p2++;
  if (*p2 == '\\' || *p2 == '/')
    p2++;
  if (*p2 != 0)
    return 0;
  return 1;
}

/* int __cdecl _chdir (const char *path).

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
  int (*fct)(const char *) =
	ic_test_getsymbol ("_chdir");
  int (*fmkdir)(const char *) =
	ic_test_getsymbol ("_mkdir");
  int (*frmdir)(const char *) =
	ic_test_getsymbol ("_rmdir");
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
      IC_TEST_CHECK (fct ("Invalid Directory") == -1 && errno == ENOENT);
      IC_TEST_CHECK (test_env_var (fct, fmkdir, frmdir) != 0);
      return IC_TEST_RSLT_SUCCESS;
    default:
      break;
  }
  return IC_TEST_RSLT_FAILED;
}
