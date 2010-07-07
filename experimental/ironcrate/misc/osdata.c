#include <icrt.h>
#include <windows.h>

/* Global variables.  */
unsigned long __iCrt__osplatform;
unsigned long __iCrt__osver;
unsigned long __iCrt__winver;
unsigned long __iCrt__winmajor;
unsigned long __iCrt__winminor;

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

int
__iCrt__get_winmajor (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__iCrt__winmajor != 0, EINVAL);
  *p = __iCrt__winmajor;
  return 0;
}

int
__iCrt__get_winminor (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__iCrt__winminor != 0, EINVAL);
  *p = __iCrt__winminor;
  return 0;
}

int
__iCrt__get_winver (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__iCrt__winver != 0, EINVAL);
  *p = __iCrt__winver;
  return 0;
}

int
__iCrt__get_osver (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__iCrt__osver != 0, EINVAL);
  *p = __iCrt__osver;
  return 0;
}

int
__iCrt__get_osplatform (unsigned int *p)
{
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (p, EINVAL);
  CHECK_AND_RETURN_ON_ERROR_WITH_ERRNO (__iCrt__osplatform != 0, EINVAL);
  *p = __iCrt__osplatform;
  return 0;
}

unsigned int
__iCrt_get_osver (void)
{
  return __iCrt__osver;
}

unsigned int
__iCrt_get_osplatform (void)
{
  return __iCrt__osplatform;
}

unsigned int
__iCrt_get_winver (void)
{
  return __iCrt__winver;
}

unsigned int
__iCrt_get_winmajor (void)
{
  return __iCrt__winmajor;
}

unsigned int
__iCrt_get_winminor (void)
{
  return __iCrt__winminor;
}
