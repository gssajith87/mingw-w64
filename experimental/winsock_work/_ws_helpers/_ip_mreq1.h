#ifndef _MINGW_IP_MREQ1_H
#define _MINGW_IP_MREQ1_H

#include <inaddr.h>

struct ip_mreq {
	struct in_addr	imr_multiaddr;
	struct in_addr	imr_interface;
};

#endif	/* _MINGW_IP_MREQ1_H */

