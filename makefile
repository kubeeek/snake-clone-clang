CC=gcc
CFLAGS=-g -ansi -O
LDFLAGS=-lcurses

clean:
		@echo Usuwam gotowe pliki
		@rm -f *.o test

all:main.o utils.o 
		$(CC) $(CFLAGS) -o snake main.o utils.o $(LDFLAGS)

main.o:main.c utils.h
		$(CC) $(CFLAGS) -c main.c

utils.o:utils.c utils.h
		$(CC) $(CFLAGS) -c utils.c
