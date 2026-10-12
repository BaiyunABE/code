all: main

main: main.o vsfs.o bio.o
	gcc -o main main.o vsfs.o bio.o

main.o: main.c
	gcc -c main.c

vsfs.o: vsfs.c
	gcc -c vsfs.c

bio.o: bio.c
	gcc -c bio.c

dbg:
	gcc -g -o main main.c vsfs.c bio.c

clean:
	rm *.o main
