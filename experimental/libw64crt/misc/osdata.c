#include <w64crt.h>
#include <windows.h>

/* Global variables.  */
unsigned long __w64crt__osplatform_0_0;
unsigned long __w64crt__osver_0_0;
unsigned long __w64crt__winver_0_0;
unsigned long __w64crt__winmajor_0_0;
unsigned long __w64crt__winminor_0_0;

/* Helper macros.  */
#define CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO(COND, ERRCODE) \
  do {				\
    if (!(COND))			\
      {				\
	/* TODO: set errno.  */ \
	return (ERRCODE);	\
      }
  } while (0)

/* Functions implementation.  */

int __w64crt__get_winmajor_0_0 (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__w64crt__winmajor_0_0 != 0, EINVAL);
  *p = __w64crt__winmajor_0_0;
  return 0;
}

int __w64crt__get_winminor_0_0 (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__w64crt__winminor_0_0 != 0, EINVAL);
  *p = __w64crt__winminor_0_0;
  return 0;
}

int
__w64crt__get_winver_0_0 (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__w64crt__winver_0_0 != 0, EINVAL);
  *p = __w64crt__winver_0_0;
  return 0;
}

int
__w64crt__get_osver_0_0 (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__w64crt__osver_0_0 != 0, EINVAL);
  *p = __w64crt__osver_0_0;
  return 0;
}

int
__w64crt__get_osplatform_0_0 (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__w64crt__osplatform_0_0 != 0, EINVAL);
  *p = __w64crt__osplatform_0_0;
  return 0;
}

unsigned int
__w64crt_get_osver_0_0 (void)
{
  return __w64crt__osver_0_0;
}

unsigned int
__w64crt_get_osplatform_0_0 (void)
{
  return __w64crt__osplatform_0_0;
}

unsigned int
__w64crt_get_winver_0_0 (void)
{
  return __w64crt__winver_0_0;
}

unsigned int __w64crt_get_winmajor_0_0 (void)
{
  return __w64crt__winmajor_0_0;
}

unsigned int __w64crt_get_winminor_0_0 (void)
{
  return __w64crt__winminor_0_0;
}
