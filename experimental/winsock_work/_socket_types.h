#ifndef ___WSA_SOCKET_TYPES_H
#define ___WSA_SOCKET_TYPES_H

typedef INT_PTR		SOCKET;

#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR	(-1)

#ifndef FD_SETSIZE
#define FD_SETSIZE	64
#endif
typedef struct fd_set
{
	u_int	fd_count;
	SOCKET	fd_array[FD_SETSIZE];
} fd_set;

#undef  FD_CLR
#define FD_CLR(fd,set)							\
  do {									\
	u_int __i;							\
	for(__i = 0;__i < ((fd_set *)(set))->fd_count;__i++) {		\
		if (((fd_set *)(set))->fd_array[__i]==fd) {		\
			while (__i < ((fd_set *)(set))->fd_count-1) {	\
				((fd_set *)(set))->fd_array[__i] =	\
				 ((fd_set *)(set))->fd_array[__i+1];	\
				__i++;					\
			}						\
			((fd_set *)(set))->fd_count--;			\
			break;						\
		}							\
	}								\
} while(0)

#define FD_ZERO(set)		(((fd_set *)(set))->fd_count = 0)

#define FD_ISSET(fd,set)	__WSAFDIsSet((SOCKET)(fd),(fd_set *)(set))

#endif /* ___WSA_SOCKET_TYPES_H */

/* not include-guard'ing FD_SET() because of winsock1/2 difference */
#undef  FD_SET
#ifdef _WINSOCK2API_	/* WinSock2 version: */
#define FD_SET(fd,set)							\
  do {									\
	u_int __i;							\
	for(__i = 0;__i < ((fd_set *)(set))->fd_count;__i++) {		\
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

