DEBUG=true 
ASM:=nasm
CC:=gcc
LD:=ld
CFLAGS:=-fno-builtin -Wall
INCLUDE:=-I include/ -I include/linux
ASMINCLUDE:= -I boot/include/

ifdef DEBUG
BOOT:=boot/boot.com
else
BOOT:=boot/boot.bin
endif
LOADER:=boot/loader.bin
KERNEL:=kernel/kernel.bin

FSOBJS:=fs/bitmap.o fs/super.o fs/inode.o fs/stat.o fs/fcntl.o fs/fs.o fs/namei.o fs/open.o fs/file_dev.o fs/read_write.o \
	fs/buffer.o fs/link.o
MMOBJS:=mm/main.o
LIBOBJS:=lib/misc.o lib/kliba.o lib/string.o lib/klibc.o lib/errno.o
KERNELOBJS:=kernel/core.o kernel/start.o kernel/i8259.o kernel/global.o kernel/protect.o kernel/main.o kernel/clock.o \
	kernel/syscall.o kernel/console.o kernel/keyboard.o kernel/sched.o kernel/sys.o kernel/tty.o \
	kernel/printf.o kernel/vsprintf.o kernel/proc.o kernel/panic.o kernel/signal.o kernel/hd.o kernel/fork.o

OBJS:=$(KERNELOBJS) $(MMOBJS) $(FSOBJS) $(LIBOBJS)


.PHONY:clean
all:everything 

everything:$(BOOT) $(LOADER) $(KERNEL) 
$(BOOT):boot/boot.asm 
	$(ASM) $(ASMINCLUDE) $< -o $@ 
	@sz -e $(BOOT) 
$(LOADER):boot/loader.asm
	$(ASM) $(ASMINCLUDE) $< -o $@
	@sz -e $(LOADER)
$(KERNEL):$(OBJS) 
	$(LD) -s -Ttext 0x10400 -o $@ $(OBJS) $(INCLUDE)
	@sz -e $(KERNEL)

kernel/%.o:kernel/%.asm
	$(ASM) -f elf $< -o $@ $(INCLUDE)
kernel/%.o:kernel/%.c
	$(CC) -c $(CFLAGS) $<  -o $@ $(INCLUDE)
lib/%.o:lib/%.asm
	$(ASM) -f elf $< -o $@ $(INCLUDE)
lib/%.o:lib/%.c
	$(CC) -c $(CFLAGS) $< -o $@  $(INCLUDE)
fs/%.o:fs/%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE)
mm/%.o:mm/%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE)

clean:
	cd lib;rm -f *.o
	cd fs;rm -f *.o
	cd kernel;rm -f *.o
	cd mm; rm -f *.o
	@rm -f $(BOOT) $(LOADER) $(KERNEL)
