#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"
#include "syscall.h"
#include "lib.h"



PUBLIC void clock_handler(int irq)
{
	ticks++;
	current->ticks--;
	//不允许中断重入
	if (k_reenter != 0) 
	{
		return;
	}
//	disp_str("----------------------------------------------\n");
	if (current->ticks > 0) 
	{
		return;
	}
	else 
		schedule();
}
//every clock interrupt is 10ms HZ=100
PUBLIC void milli_delay(int milli_sec)
{
	int t = get_ticks();
	while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}
}

PUBLIC void init_clock()
{
	out_byte(TIMER_MODE, RATE_GENERATOR);
	//set HZ = 100
	out_byte(TIMER0, (t_8) (TIMER_FREQ/HZ) );
	out_byte(TIMER0, (t_8) ((TIMER_FREQ/HZ) >> 8));
	//设置时钟中断

	put_irq_handler(CLOCK_IRQ, clock_handler);	
	enable_irq(CLOCK_IRQ);			
}


