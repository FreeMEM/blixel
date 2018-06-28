#Blixel makefile

CFLAGS = -noixemul -g -Wall
CC = m68k-amigaos-gcc
INCLUDES= includes/

# OBJS = blixel.o screen.o mainmenu.o
OBJS = blixel.o screen.o mainmenu.o
BINARY = blixel

all: blixel

blixel: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $?

%.o: %.c libs.h ${INCLUDES}


clean:
	rm -f $(BINARY) $(OBJS)
