#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"
#include "lib.h"
#include "hd.h"
#include "blk_drv.h"
#include "fcntl.h"

PRIVATE int dupfd(unsigned int oldfd,unsigned int newfd)
{
	if(oldfd >= NR_OPEN || !current->filp[oldfd])
		return -1;
	if(newfd >= NR_OPEN)
		return -1;
	while(newfd < NR_OPEN)
	{
		if(current->filp[newfd])
			newfd++;
		else
			break;	
	}
	if(newfd >= NR_OPEN)
		return -1;
	(current->filp[newfd] = current->filp[oldfd])->f_count++;
	return newfd;
}

PUBLIC int sys_dup2(unsigned int oldfd,unsigned int newfd)
{
	sys_close(newfd);
	return dupfd(oldfd,newfd);
}

PUBLIC int sys_fcntl(unsigned int fd,int cmd,unsigned int arg)
{
	struct file *filp;
	if(fd >= NR_OPEN || !(filp = current->filp[fd]))
		return -1;
	switch(cmd)
	{
		case F_DUPFD:
			return dupfd(fd,arg);
		case F_GETFD:

		case F_SETFD:

		case F_GETFL:
			return filp->f_flag;
		case F_SETFL:
			return filp->f_flag |= arg;
		default:
			return -1;
	}
}
