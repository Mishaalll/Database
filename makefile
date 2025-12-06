CC = gcc

all: test

test: main.c mylib.c
	$(CC) main.c mylib.c -o main.o

clear:
	rm *.o
