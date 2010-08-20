
#include <fcntl.h>

#ifndef O_BINARY
# define O_BINARY 0
#endif

#ifndef HAVE_MKSTEMP
extern int mkstemps(char *template, int suffix_len);
#endif

