ASM:=nasm
CC:=gcc
LD:=ld
CFLAGS:=-fno-builtin
INCLUDE:=-I ../include/
OBJS:=klibc.o string.o kliba.o misc.o errno.o
lib.o:$(OBJS)
	$(LD) -r -o $@ $(OBJS)
	sync
%.o:%.asm
	$(ASM) -f elf $< -o $@ $(INCLUDE)
%.o:%.c
	$(CC) -c $(CFLAGS) $< $(INCLUDE)

clean:
	rm -f *.o
