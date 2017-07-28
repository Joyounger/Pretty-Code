CC:=gcc
LD:=ld
CFLAGS:=-fno-builtin -Wall
INCLUDE:=-I ../include/ -I ../include/linux/
FSOBJS:=main.o
mm.o:$(FSOBJS) 
	$(LD) -r -o $@ $(FSOBJS)
	sync
%.o:%.c
	$(CC) -c $(CFLAGS) $< $(INCLUDE)
clean:
	rm -f *.o



