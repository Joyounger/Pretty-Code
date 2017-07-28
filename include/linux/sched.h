#include "signal.h"
#include "fs.h"

typedef struct s_stackframe {	
	t_32	gs;		
	t_32	fs;		
	t_32	es;		
	t_32	ds;		
	t_32	edi;		
	t_32	esi;		
	t_32	ebp;		
	t_32	kernel_esp;	
	t_32	ebx;		
	t_32	edx;		
	t_32	ecx;		
	t_32	eax;		
	t_32	retaddr;	
	t_32	eip;		
	t_32	cs;		
	t_32	eflags;		
	t_32	esp;		
	t_32	ss;		
}STACK_FRAME;


typedef struct task_struct 
{
	STACK_FRAME	regs;			
	t_16		ldt_sel;		
	DESCRIPTOR	ldts[LDT_SIZE];		
	struct 	sigaction sig_action[32];//32个信号 
	int 		state;
	int		signal; //信号位图
	int 		sig_blocked; //信号屏蔽字段
	t_bool		sigpending;	//是否有信号 有true 没有false
	int 		flags;
	int		ticks;			
	int		priority;
	int 		nr_tty;
	t_32		pid;			
	char		name[16];		
	struct 	file 	*filp[NR_OPEN];
	struct task_struct *parent;
}PROCESS;


typedef struct s_task 
{
	t_pf_task	initial_eip;
	int		stacksize;
	char		name[32];
}TASK;



#define NR_TASKS		1 //tty 
#define NR_NATIVE_PROCS 	5 //testA testB testC testD init
//total procs in this system
#define NR_PROCS		32
#define NR_PROCESS		NR_TASKS + NR_NATIVE_PROCS


#define STACK_SIZE_DEFAULT	0x4000
#define STACK_SIZE_TTY		STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTA	STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTB	STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTC	STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTD	STACK_SIZE_DEFAULT
#define STACK_SIZE_INIT		STACK_SIZE_DEFAULT

#define STACK_SIZE_TOTAL	(STACK_SIZE_TTY + \
				STACK_SIZE_INIT + \
				STACK_SIZE_TESTA + \
				STACK_SIZE_TESTB + \
				STACK_SIZE_TESTC + \
				STACK_SIZE_TESTD)

#define proc2pid(p) (p - proc_table)
#define pid2proc(pid) (proc_table + pid)

/* 	null		0 */
#define FREE_SLOT	0
#define NO_PARENT 	NULL

#define TASK_RUNNING		0	//running
#define TASK_INTERRUPTIBLE	1	//sleep 
#define TASK_UNINTERRUPTIBLE 	2	//wati
#define TASK_ZOMB		3	//being terminated
#define TASK_STOPPED		4	//being traced
