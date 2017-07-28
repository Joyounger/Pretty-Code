#include "boot.h" 

//       klib.asm 
PUBLIC void     out_byte(t_port port, t_8 value);
PUBLIC t_8      in_byte(t_port port);
PUBLIC void     disable_int();
PUBLIC void     enable_int();
PUBLIC void     disp_str(char * info);
PUBLIC void     disp_color_str(char * info, int color);
PUBLIC void     clear_screen();
//       tlib.c 
PUBLIC t_bool   is_alphanumeric(char ch);
PUBLIC void     delay(int time);
PUBLIC void     itoa(char* str, int num);
PUBLIC void     disp_int(int input);

//       misc.c 
PUBLIC void     spin(char *str);
PUBLIC void     assertion_failure(char *exp,char *file,char *base_file,int line);
PUBLIC int 	strncmp(char *str1,char *str2,int len);
PUBLIC int 	strncpy(char *dest,char *src,int pos,int size);


PUBLIC void 	get_boot_params(struct boot_params *bp);
PUBLIC int 	get_kernel_map(unsigned int * base, unsigned int * limit);
