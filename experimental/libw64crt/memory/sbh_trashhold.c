#include <w64crt.h>

static size_t sbh_threshold = 0;

size_t
__w64crt_get_sbh_threshold (void)
{
  return sbh_threshold;
}

int
__w64crt_set_sbh_threshold (size_t threshold)
{
  if (threshold > 1016)
     return 0;
  sbh_threshold = threshold;
  return 1;
}
