#include <w64crt.h>
#include <windows.h>

int __w64crt__get_winmajor_0_0 (unsigned int *p)
{
  if (!p || __w64crt__winmajor_0_0 == 0)
    {
      /* TODO: set errno to EINVAL. */
      return EINVAL;
    }
  *p = __w64crt__winmajor_0_0;
  return 0;
}

int __w64crt__get_winminor_0_0 (unsigned int *p)
{
  if (!p || __w64crt__winminor_0_0 == 0)
    {
      /* TODO: set errno to EINVAL. */
      return EINVAL;
    }
  *p = __w64crt__winminor_0_0;
  return 0;
}

int
__w64crt__get_winver_0_0 (unsigned int *p)
{
  if (!p || __w64crt__winver_0_0 == 0)
    {
      /* TODO: set errno to EINVAL. */
      return EINVAL;
    }
  *p = __w64crt__winver_0_0;
  return 0;
}

int
__w64crt__get_osver_0_0 (unsigned int *p)
{
  if (!p || __w64crt__osver_0_0 == 0)
    {
      /* TODO: set errno to EINVAL. */
      return EINVAL;
    }
  *p = __w64crt__osver_0_0;
  return 0;
}

int
__w64crt__get_osplatform_0_0 (unsigned int *p)
{
  if (!p || __w64crt__osplatform_0_0 == 0)
    {
      /* TODO: set errno to EINVAL. */
      return EINVAL;
    }
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
