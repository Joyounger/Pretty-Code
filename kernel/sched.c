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

PUBLIC void unblock(struct task_struct *p)
{
	p->state = TASK_RUNNING;
}

PUBLIC void block(struct task_struct *p)
{
        p->state = TASK_INTERRUPTIBLE;
        schedule();
}
//只唤醒等待队列头进程(应该遍历，唤醒所有的进程)
PUBLIC void wake_up(struct  task_struct **p)
{
	if(p && *p)
	{
		(**p).state = TASK_RUNNING;
		*p = NULL;
	}
}
PUBLIC void sleep_on(struct task_struct **p)
{
        struct task_struct *tmp;
        if(!p)
                return;
        tmp = *p;
        *p = current;
        current->state = TASK_UNINTERRUPTIBLE;
        schedule();
        if(tmp)
                tmp->state = TASK_RUNNING;
}
PUBLIC int goodness(PROCESS **p)
{
	int greatest_ticks = 0;	
	PROCESS *item;
	for(item = proc_table;item < proc_table + NR_PROCESS + NR_PROCS;item++)	
	{
		if(item->flags == FREE_SLOT)
			continue;
		if(item->state == TASK_RUNNING)
		{
		//	disp_str(item->name);
			if(item->ticks > greatest_ticks)
			{
				greatest_ticks = item->ticks;
				*p = item;	
			}	
		}
	}
	return greatest_ticks;
}

PUBLIC void switch_to(PROCESS *prev,PROCESS *next)
{
}
PUBLIC void schedule()
{
	disable_int();
	PROCESS*        p;
//	PROCESS 	*prev,*next;
	int             greatest_ticks = 0;
	//based on PRI
	while (!greatest_ticks) 
	{
		//choose the best process
		greatest_ticks = goodness(&p);
		if(p == current)
		{
		//	disp_str("no best process\n");
		}
		else
		{
			current = p;
		}
		// if all processes execuse over ,asign time to each one,then choose a process
		if (!greatest_ticks) 
		{
			for (p=proc_table; p < proc_table + NR_PROCESS + NR_PROCS; p++) 
			{
				if(p->flags != FREE_SLOT)
					p->ticks = p->priority;
			}
		}
		/*		else
				{
				switch_to(prev,next);
				}
				*/

	}
	enable_int();
}
