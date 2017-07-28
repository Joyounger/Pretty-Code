#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"

//系统级错误 系统stop
PUBLIC void panic(const char *fmt,...)
{
	int i;
	char buf[128];
	va_list args = (va_list)((char *)&fmt+4);
	i = vsprintf(buf,fmt,args);
	printf("%c panic %s",MAG_CH_PANIC,buf);
//	__asm__ __volatile__ ("ud2");
}
