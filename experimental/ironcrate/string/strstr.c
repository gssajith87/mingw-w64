#include <icrt.h>

char *
strstr (const char *d, const char *str)
{
  char *dp = (char *) d;
  size_t strl = strlen (str);

  while ((dp = strchr (dp, *str)) != NULL)
    {
      if (!strncmp (dp, str, strl))
	return dp;
      dp++;
    }
  return NULL;
}

