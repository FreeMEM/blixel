#Blixel makefile

# CFLAGS = -noixemul -g -Wall
CFLAGS = -noixemul
CC = m68k-amigaos-gcc
INCLUDES= includes/
RZFLAGS = -fstrength-reduce -msmall-code -Wimplicit \
          -Wstrict-prototypes -s -Os -fomit-frame-pointer

OBJS = blixel.o screen.o mainmenu.o mainworkarea.o
# OBJS = blixel.o screen.o mainmenu.o mainworkarea.o
BINARY = blixel

all: blixel

blixel: $(OBJS)
	$(CC) $(CFLAGS) $(RZFLAGS) -o $@ $?

%.o: %.c libs.h ${INCLUDES}


clean:
	rm -f $(BINARY) $(OBJS)
