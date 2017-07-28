#include "type.h"
#include "const.h"
#include "protect.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"
#include "string.h"
#include "mm.h"

PRIVATE int get_limit(struct descriptor *dp)
{
	if(dp)
	{
		return ((dp->limit_high_attr2 & 0xF) >> DP_LIMIT_SHIFT) + dp->limit_low;
	}
	return 0;
}

PRIVATE int get_base(struct descriptor *dp)
{
	if(dp)
	{
		return ((dp->base_high << DP_BASE_HIGH_SHIFT) + (dp->base_mid << DP_BASE_MID_SHIFT) + dp->base_low);
	}
	return 0;
}

PRIVATE int find_empty_process(void)
{
	int i;
	//排除任务0
	for(i = 0;i < NR_PROCESS + NR_PROCS;i++)
	{
		if(proc_table[i].flags == FREE_SLOT)
			break;
	//	else
	//		printk("i = %d\t",i);
	}
	if((i >= NR_PROCESS + NR_PROCS))
		return -1;
	else 
		return i;

}

////复制父进程的地址空间
PRIVATE int copy_mem(int pid,struct task_struct *p)
{
	struct descriptor *dp = &proc_table[pid].ldts[INDEX_LDT_C];
	int text_base = get_base(dp);
	int text_limit = get_limit(dp);
	int text_size = (text_limit + 1) * ((dp->limit_high_attr2 * 0x80)?4096:1);

	dp = &proc_table[pid].ldts[INDEX_LDT_D]; 
	int data_base =  get_base(dp);
	int data_limit= get_limit(dp);
	int data_size = (text_limit + 1) * ((dp->limit_high_attr2 * 0x80)?4096:1);

	assert((text_base == data_base)  && 
		(text_limit == data_limit) &&
		(text_size == data_size)
		)

	int child_base = alloc_mem(p->pid,text_size);
	printk("child_base = %d\t text_base = %d\t text_size = %d\n",child_base,text_base,text_size);
	memcpy((void *)child_base,(void *)(text_base),text_size);

	return 0;
}
PUBLIC int do_fork()
{
	int child_pid = -1; 	//child process pid
	int pid = current->pid; //parent process pid;
	int ret = -1;
	struct task_struct *p; 
	ret = find_empty_process();
	if(ret == -1) 
		panic("cannot find empty process\n");
	else 
		child_pid = ret;
	printk("child_pid = %d\n",child_pid);
	p = proc_table + child_pid;

	*p = proc_table[3]; //*p = *current;

	p->pid = child_pid;
	p->parent = current;
	sprintf(p->name,"%s-%d",p->name,p->pid);
	//	printk("p->name= %s\n",p->name);

	copy_mem(pid,p);

	return 0;
}

PUBLIC int fork()
{
	//	int flag;
	return do_fork();
}

PUBLIC int getpid()
{
	return 0;
}

