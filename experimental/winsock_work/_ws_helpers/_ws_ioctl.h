#ifndef __MINGW_WSA_IOCTL_H
#define __MINGW_WSA_IOCTL_H

#define IOCPARM_MASK	0x7f
#define IOC_VOID	0x20000000
#define IOC_OUT		0x40000000
#define IOC_IN		0x80000000
#define IOC_INOUT	(IOC_IN | IOC_OUT)

#define _IO(x,y)	(IOC_VOID | ((x)<<8) | (y))
#define _IOR(x,y,t)	(IOC_OUT  | (((long)sizeof(t) & IOCPARM_MASK)<<16) | ((x)<<8) | (y))
#define _IOW(x,y,t)	(IOC_IN   | (((long)sizeof(t) & IOCPARM_MASK)<<16) | ((x)<<8) | (y))

#define FIONREAD	_IOR('f',127,u_long)
#define FIONBIO		_IOW('f',126,u_long)
#define FIOASYNC	_IOW('f',125,u_long)

#define SIOCSHIWAT	_IOW('s',0,u_long)
#define SIOCGHIWAT	_IOR('s',1,u_long)
#define SIOCSLOWAT	_IOW('s',2,u_long)
#define SIOCGLOWAT	_IOR('s',3,u_long)
#define SIOCATMARK	_IOR('s',7,u_long)

#endif	/* __MINGW_WSA_IOCTL_H */

