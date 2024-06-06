CC=gcc
CFLAGS=-I.
LIBS=-lncurses

main: main.c
	$(CC) -o main main.c $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f main