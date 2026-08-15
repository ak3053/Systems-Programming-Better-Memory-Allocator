CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: memgrind

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.o mymalloc.o

memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm -f *.o memgrind