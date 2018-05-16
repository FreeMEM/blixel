#Blixel makefile

CFLAGS = -noixemul -g -Wall
CC = m68k-amigaos-gcc

# OBJS = blixel.o screen.o mainmenu.o
OBJS = blixel.o screen.o
BINARY = blixel

all: blixel

blixel: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $?

%.o: %.c libs.h


clean:
	rm -f $(BINARY) $(OBJS)
