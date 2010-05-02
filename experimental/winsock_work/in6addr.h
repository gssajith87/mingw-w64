#ifndef s6_addr

#include <_bsd_types.h>

struct in6_addr {
  __MINGW_EXTENSION union {
    u_char Byte[16];
    u_short Word[8];
  } u;
};

#define in_addr6	in6_addr

#define _S6_un		u
#define _S6_u8		Byte
#define s6_addr		_S6_un._S6_u8

#define s6_bytes	u.Byte
#define s6_words	u.Word

#endif /* s6_addr */

