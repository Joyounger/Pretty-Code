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
#include "fork.h"
#include "proc.h"
#include "mm.h"

PUBLIC int alloc_mem(int pid,int memsize)
{
	assert(pid < NR_PROCESS + NR_PROCS);
	int base = 0;
	if(memsize > PROC_IMAGE_SIZE_DEFAULT)
		panic("unsupported memory request %d,shoud be less than %d\n",\
				memsize,PROC_IMAGE_SIZE_DEFAULT);
	base = PROCS_BASE + pid * PROC_IMAGE_SIZE_DEFAULT;

	printk("base = %d\n",base);
	printk("memsize = %d\n",memsize);
	printk("memory_size = %d\n",memory_size);
	if(base + memsize >= memory_size)
		panic("memory allocation failed pid %d\n",pid);
	return base;
}


PUBLIC void init_mm()
{
	struct boot_params bp;
	get_boot_params(&bp);
	memory_size = bp.mem_size;
	return ;
}
