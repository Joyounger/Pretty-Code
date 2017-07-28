
%include "sconst.inc"

_NR_get_ticks		equ	0	
_NR_write		equ 	1
_NR_printx		equ 	2

INT_VECTOR_SYS_CALL	equ	0x80  ;syscall number

global	get_ticks
global 	write
global 	printx

bits 32
[section .text]

get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret

write:
	mov 	eax,_NR_write
	mov 	ebx,[esp + 4]
	mov 	ecx,[esp + 8]
	int 	INT_VECTOR_SYS_CALL
	ret
printx:
	mov 	eax,_NR_printx
	mov 	ebx,[esp + 4]
	mov 	ecx,[esp + 8]
	int 	INT_VECTOR_SYS_CALL
	ret
