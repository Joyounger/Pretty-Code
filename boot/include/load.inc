
;loader.bin 加载的地址
BaseOfLoader		equ	 09000h	 
OffsetOfLoader		equ	  0100h	

BaseOfLoaderPhyAddr	equ	BaseOfLoader * 10h	

;kernel.bin加载的地址
BaseOfKernelFile	equ	 08000h	
OffsetOfKernelFile	equ	     0h	
BaseOfKernelFilePhyAddr	equ	BaseOfKernelFile * 10h

KernelEntryPointPhyAddr	equ	030400h	
					
;二级页式存储
;页目录
PageDirBase		equ	200000h	
;页表	
PageTblBase		equ	201000h 


BOOT_PARAM_ADDR   	equ 0x900
BOOT_PARAM_MAGIC 	equ  0xCCCC
