#ifndef _ERRNO_H
#define _ERRNO_H
extern int errno;

#define ERROR		99
#define EPERM		 1	//operation not permitted
#define ENOENT		 2	//no such file or directory
#define ESRCH		 3	//no such process
#define EINTR		 4	//interrupted system call
#define EIO		 5	//input/output error
#define ENXIO		 6	//no such device or address
#define E2BIG		 7	//argument list too long
#define ENOEXEC		 8	//exec format error
#define EBADF		 9	//bad file descriptor
#define ECHILD		10	//no child processes
#define EAGAIN		11	//resouce temporarily unavailable
#define ENOMEM		12	//cannot allocate memory
#define EACCES		13	//permission denied
#define EFAULT		14	//bad address
#define ENOTBLK		15	//block device requied
#define EBUSY		16	//device or resource busy
#define EEXIST		17	//file exists
#define EXDEV		18	//invalid cross-device link
#define ENODEV		19	//no such device
#define ENOTDIR		20	//not a directory
#define EISDIR		21	//ls a directory
#define EINVAL		22	//invalid argument
#define ENFILE		23	//too many open files in system
#define EMFILE		24	//too many open files
#define ENOTTY		25	//inappropriate ioctl for device
#define ETXTBSY		26	//text file busy
#define EFBIG		27	//file too large
#define ENOSPC		28	//no space left on device
#define ESPIPE		29	//illegal seek
#define EROFS		30`	//read-only file system
#define EMLINK		31	//too many links
#define EPIPE		32	//broken pipe
#define EDOM		33	//numerical argument out of domain
#define ERANGE		34	//numerical result out of range
#define EDEADLK		35	//resource deadlock avoided
#define ENAMETOOLONG	36	//file name too long 
#define ENOLCK		37	//no locks avaialbe
#define ENOSYS		38	//function not implemented
#define ENOTEMPTY	39	//directory not empty

#endif
