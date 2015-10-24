CC = gcc
OBJECTS = src/scriptlang_core.c src/scriptlang_mem.c scriptlang.c
LIBS = -lm
CFLAGS = -Wall -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = scriptlang

scriptlang: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

