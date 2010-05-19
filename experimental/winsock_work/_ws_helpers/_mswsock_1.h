#ifndef _MINGW_MSWSOCK_1_H
#define _MINGW_MSWSOCK_1_H

#define SO_CONNDATA		0x7000
#define SO_CONNOPT		0x7001
#define SO_DISCDATA		0x7002
#define SO_DISCOPT		0x7003
#define SO_CONNDATALEN		0x7004
#define SO_CONNOPTLEN		0x7005
#define SO_DISCDATALEN		0x7006
#define SO_DISCOPTLEN		0x7007

#define SO_OPENTYPE		0x7008

#define SO_SYNCHRONOUS_ALERT	0x10
#define SO_SYNCHRONOUS_NONALERT	0x20

#define SO_MAXDG		0x7009
#define SO_MAXPATHDG		0x700A
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B
#define SO_CONNECT_TIME		0x700C

#define TCP_BSDURGENT		0x7000

typedef struct _TRANSMIT_FILE_BUFFERS {
	LPVOID	Head;
	DWORD	HeadLength;
	LPVOID	Tail;
	DWORD	TailLength;
} TRANSMIT_FILE_BUFFERS, *PTRANSMIT_FILE_BUFFERS, *LPTRANSMIT_FILE_BUFFERS;

#define TF_DISCONNECT		0x01
#define TF_REUSE_SOCKET		0x02
#define TF_WRITE_BEHIND		0x04

#ifdef __cplusplus
extern "C" {
#endif

int WINAPI	WSARecvEx   (SOCKET s, char *buf, int len, int *flags);

WINBOOL WINAPI	TransmitFile(SOCKET hSocket, HANDLE hFile, DWORD nNumberOfBytesToWrite,
			     DWORD nNumberOfBytesPerSend, LPOVERLAPPED lpOverlapped,
			     LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers, DWORD dwReserved);

WINBOOL WINAPI	AcceptEx    (SOCKET sListenSocket, SOCKET sAcceptSocket, PVOID lpOutputBuffer,
			     DWORD dwReceiveDataLength, DWORD dwLocalAddressLength,
			     DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived,
			     LPOVERLAPPED lpOverlapped);

VOID WINAPI	GetAcceptExSockaddrs(PVOID lpOutputBuffer , DWORD dwReceiveDataLength,
			     DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength,
			     struct sockaddr **LocalSockaddr , LPINT LocalSockaddrLength,
			     struct sockaddr **RemoteSockaddr, LPINT RemoteSockaddrLength);

#ifdef __cplusplus
}
#endif

#endif	/* _MINGW_MSWSOCK_1_H */

