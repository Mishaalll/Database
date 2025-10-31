cc = gcc

clear:
	rm *.o

main:
	$(CC) main.c mylib.c -o main.o
