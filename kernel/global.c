

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"


//PUBLIC	PROCESS	proc_table[NR_TASKS + NR_NATIVE_PROCS];
PUBLIC	PROCESS	proc_table[NR_PROCESS + NR_PROCS];

PUBLIC	char	task_stack[STACK_SIZE_TOTAL];

//把tty任务作为第一个进程启动
PUBLIC	TASK	task_table[NR_TASKS] = {
					{task_tty, STACK_SIZE_TTY, "tty"}
					};
PUBLIC TASK 	user_proc_table[NR_NATIVE_PROCS] = {
					{init, 	STACK_SIZE_INIT,   "init"},
					{TestC, STACK_SIZE_TESTC, "TestC"},
					{TestA, STACK_SIZE_TESTA, "TestA"},
					{TestB, STACK_SIZE_TESTB, "TestB"},
					{TestD, STACK_SIZE_TESTD, "TestD"}
					};

PUBLIC	TTY			tty_table[NR_CONSOLES];
PUBLIC	CONSOLE			console_table[NR_CONSOLES];

PUBLIC	t_pf_irq_handler	irq_table[NR_IRQ];

PUBLIC	t_sys_call		sys_call_table[NR_SYS_CALL] = {sys_get_ticks,
					//			sys_write,
								sys_printx};
