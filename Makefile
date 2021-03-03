ifeq ($(OS),Windows_NT)
	AFMT = win32
	LFLG = -mi386pe -subsystem console
	LIBS = -LC:\MinGW\lib -lkernel32 -luser32
else
	AFMT = elf32
	LFLG = -melf_i386 -e _main
	LIBS =
endif

LIBNAME = libsortasm
LIBSRCS = $(wildcard $(LIBNAME)/*.asm)
LIBOBJS = $(LIBSRCS:$(LIBNAME)/%.asm=obj/%.o)


CSRCS  = $(wildcard *.c)
COBJS  = $(CSRCS:%.c=obj/%.o)
CFLAGS = -m32 -Wall -O3 -fno-stack-protector -std=c99

OUT   = main.exe

all: build run

build: makelib $(COBJS)
	gcc -m32 -o $(OUT) $(COBJS) $(LIBNAME).lib

obj:
	mkdir obj
    
makelib: obj $(LIBOBJS)
	ar rcs $(LIBNAME).lib $(LIBOBJS)

obj/%.o: $(LIBNAME)/%.asm 
	nasm -O3 -f $(AFMT) $(LIBNAME)/$*.asm -o obj/$*.o    

obj/%.o: %.c
	gcc $(CFLAGS) -c $*.c -o obj/$*.o
    
clean:
	rm -rf obj $(OUT) $(LIBNAME).lib

run:
	./$(OUT)
    
