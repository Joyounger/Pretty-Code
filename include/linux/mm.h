extern long memory_end; 
extern long main_memory_start;
extern long memory_size;
extern long buffer_memory_start;
extern long buffer_memory_end;


PUBLIC int alloc_mem(int pid,int memsize);
PUBLIC void init_mm();


