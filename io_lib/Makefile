CC=nasm
LD=ld

all: test

test: test.asm lib.inc
	$(CC) -f elf64 test.asm -o test.o
	$(LD) -o test test.o

clean:
	rm -rf *.o test
