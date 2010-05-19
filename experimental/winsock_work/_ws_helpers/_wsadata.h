#ifndef __MINGW_WSADATA_H
#define __MINGW_WSADATA_H

#define WSADESCRIPTION_LEN	256
#define WSASYS_STATUS_LEN	128

typedef struct WSAData {
	WORD		wVersion;
	WORD		wHighVersion;
#ifdef _WIN64
	unsigned short	iMaxSockets;
	unsigned short	iMaxUdpDg;
	char		*lpVendorInfo;
	char	szDescription[WSADESCRIPTION_LEN+1];
	char	szSystemStatus[WSASYS_STATUS_LEN+1];
#else
	char	szDescription[WSADESCRIPTION_LEN+1];
	char	szSystemStatus[WSASYS_STATUS_LEN+1];
	unsigned short	iMaxSockets;
	unsigned short	iMaxUdpDg;
	char		*lpVendorInfo;
#endif
} WSADATA;

typedef WSADATA *LPWSADATA;

#endif	/* __MINGW_WSADATA_H */

