all: main

main: main.o mm_malloc.o
	gcc -o main main.o mm_malloc.o

main.o: main.c
	gcc -c main.c

mm_malloc.o:
	gcc -c mm_malloc.c

clean:
	rm -f *.o main
