ASM:=nasm
CC:=gcc
LD:=ld
CFLAGS:=-fno-builtin -Wall
INCLUDE:=-I ../include/ -I ../include/linux
OBJS:=core.o start.o i8259.o global.o protect.o main.o hd.o \
	clock.o syscall.o console.o keyboard.o sched.o sys.o tty.o printf.o\
	vsprintf.o proc.o panic.o signal.o  fork.o
kernel.o:$(OBJS)
	$(LD) -r -o $@ $(OBJS)
%.o:%.asm
	$(ASM) -f elf $< -o $@ $(INCLUDE)
%.o:%.c
	$(CC) -c $(CFLAGS) $< $(INCLUDE)

clean:
	rm -f *.o

