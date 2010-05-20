#ifndef ___WSA_FD_TYPES_H
#define ___WSA_FD_TYPES_H

#include <_ws_helpers/_socket_types.h>

#ifndef FD_SETSIZE
#define FD_SETSIZE	64
#endif
typedef struct fd_set
{
	u_int	fd_count;
	SOCKET	fd_array[FD_SETSIZE];
} fd_set;

typedef struct fd_set	FD_SET;
typedef struct fd_set	*PFD_SET;
typedef struct fd_set	*LPFD_SET;

#undef  FD_CLR
#define FD_CLR(fd,set)							\
  do {									\
	u_int __i;							\
	for(__i = 0; __i < ((fd_set *)(set))->fd_count; __i++) {	\
		if (((fd_set *)(set))->fd_array[__i] == fd) {		\
			while (__i < ((fd_set *)(set))->fd_count - 1) {	\
				((fd_set *)(set))->fd_array[__i] =	\
				 ((fd_set *)(set))->fd_array[__i + 1];	\
				__i++;					\
			}						\
			((fd_set *)(set))->fd_count--;			\
			break;						\
		}							\
	}								\
} while(0)

#define FD_ZERO(set)		(((fd_set *)(set))->fd_count = 0)

#define FD_ISSET(fd,set)	__WSAFDIsSet((SOCKET)(fd),(fd_set *)(set))

#endif /* ___WSA_FD_TYPES_H */

/* not include-guard'ing FD_SET() because of winsock1/2 difference */
#undef  FD_SET
#ifdef _WINSOCK2API_	/* WinSock2 version: */
#define FD_SET(fd,set)							\
  do {									\
	u_int __i;							\
	for(__i = 0; __i < ((fd_set *)(set))->fd_count; __i++) {	\
		if (((fd_set *)(set))->fd_array[__i] == (fd)) {		\
			break;						\
		}							\
	}								\
	if (__i == ((fd_set *)(set))->fd_count) {			\
		if (((fd_set *)(set))->fd_count < FD_SETSIZE) {		\
			((fd_set *)(set))->fd_array[__i] = (fd);	\
			((fd_set *)(set))->fd_count++;			\
		}							\
	}								\
} while(0)
#else			/* WinSock 1.1 version: */
#define FD_SET(fd,set)							\
  do {									\
	if (((fd_set *)(set))->fd_count < FD_SETSIZE)			\
	    ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++] =\
								   (fd);\
} while(0)
#endif


#undef FD_READ
#undef FD_WRITE
#undef FD_OOB
#undef FD_ACCEPT
#undef FD_CONNECT
#undef FD_CLOSE

#ifndef _WINSOCK2API
#define FD_READ		0x01
#define FD_WRITE	0x02
#define FD_OOB		0x04
#define FD_ACCEPT	0x08
#define FD_CONNECT	0x10
#define FD_CLOSE	0x20

#else /* _WINSOCK2API */

#define FD_READ_BIT	0
#define FD_READ		(1 << FD_READ_BIT)

#define FD_WRITE_BIT	1
#define FD_WRITE	(1 << FD_WRITE_BIT)

#define FD_OOB_BIT	2
#define FD_OOB		(1 << FD_OOB_BIT)

#define FD_ACCEPT_BIT	3
#define FD_ACCEPT	(1 << FD_ACCEPT_BIT)

#define FD_CONNECT_BIT	4
#define FD_CONNECT	(1 << FD_CONNECT_BIT)

#define FD_CLOSE_BIT	5
#define FD_CLOSE	(1 << FD_CLOSE_BIT)

#define FD_QOS_BIT	6
#define FD_QOS		(1 << FD_QOS_BIT)

#define FD_GROUP_QOS_BIT 7
#define FD_GROUP_QOS	(1 << FD_GROUP_QOS_BIT)

#define FD_ROUTING_INTERFACE_CHANGE_BIT	8
#define FD_ROUTING_INTERFACE_CHANGE	(1 << FD_ROUTING_INTERFACE_CHANGE_BIT)

#define FD_ADDRESS_LIST_CHANGE_BIT	9
#define FD_ADDRESS_LIST_CHANGE		(1 << FD_ADDRESS_LIST_CHANGE_BIT)

#define FD_MAX_EVENTS			10
#define FD_ALL_EVENTS			((1 << FD_MAX_EVENTS) - 1)

#endif	/* _WINSOCK2API */

