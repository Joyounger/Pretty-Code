
/* protect.c */
PUBLIC void	init_prot();
PUBLIC t_32	seg2phys(t_16 seg);
PUBLIC void	disable_irq(int irq);
PUBLIC void	enable_irq(int irq);
PUBLIC void 	init_descriptor(DESCRIPTOR * p_desc, t_32 base, t_32 limit, t_16 attribute);

/* core.asm */
PUBLIC void	restart();
PUBLIC void	move_to_user_mode();

/* main.c */
PUBLIC void	TestA();
PUBLIC void	TestB();
PUBLIC void	TestC();
PUBLIC void	TestD();
PUBLIC void 	init();

/* i8259.c */
PUBLIC void	put_irq_handler(int iIRQ, t_pf_irq_handler handler);
PUBLIC void	spurious_irq(int irq);
PUBLIC void 	init_8259A();

/* clock.c */
PUBLIC void	clock_handler(int irq);
PUBLIC void	milli_delay(int milli_sec);
PUBLIC void 	init_clock();

/* sched.c */
PUBLIC void 	wake_up(struct  task_struct **p);
PUBLIC void 	sleep_on(struct task_struct **p);
PUBLIC void	schedule();
PUBLIC int 	goodness(PROCESS **p);
PUBLIC void 	switch_to(PROCESS *prev,PROCESS *next);

/* keyboard.c */
PUBLIC void	keyboard_handler(int irq);
PUBLIC void	keyboard_read(TTY* p_tty);
PUBLIC void 	init_keyboard();

/* tty.c */
PUBLIC void	task_tty();
PUBLIC void	in_process(TTY* p_tty, t_32 key);
PUBLIC int 	sys_printx(char *buf,int len,struct task_struct *p_proc);

/* console.c */
PUBLIC void	init_screen(TTY* p_tty);
PUBLIC void	out_char(CONSOLE* p_con, char ch);
PUBLIC void	scroll_screen(CONSOLE* p_con, int direction);
PUBLIC t_bool	is_current_console(CONSOLE* p_con);
PUBLIC void select_console(int nr_console);
/* syscall.asm 
PUBLIC	void	sys_call();		
PUBLIC	int	get_ticks();
PUBLIC 	void 	write(char *buf,int len);
PUBLIC 	void 	printx(char *buf,int len);
*/
/* vsprintf.c */
int vsprintf(char *buf,const char *fmt,va_list args);
int sprintf(char *buf,const char *fmt,...);
/* printf.c */
int printf(const char *fmt,...);
int printk(const char *fmt,...);

/* sys.c */
PUBLIC	int	sys_get_ticks();
//PUBLIC 	int 	sys_write(char *buf,int len,PROCESS *p_proc);

/* panic.c */
PUBLIC void 	panic(const char *fmt,...);
/*	proc.c 	*/
PUBLIC void* 	va2la(int pid,void *va);

/* signal.c */
PUBLIC void 	do_signal(int signr);
PUBLIC int 	get_signal_bitmap();
PUBLIC int 	send_signal(int signr,int pid);

/* hd.c */
PUBLIC void 	ha_handler(int irq);
PUBLIC void 	init_hd();
PUBLIC void 	hd_identify(int drive);
PUBLIC void 	hd_rw(int device,int start_sect,int nr_sects,int flag,struct buffer_head *bh);
PUBLIC void 	hd_open(int device);
//PUBLIC void do_signal();
