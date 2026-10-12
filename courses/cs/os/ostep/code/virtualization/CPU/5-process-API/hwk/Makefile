all: 1 2 3

1: 1.o
	gcc -o 1 1.o

2: 2.o
	gcc -o 2 2.o

3: 3.o
	gcc -o 3 3.o

1.o: 1.c
	gcc -c 1.c

2.o: 2.c
	gcc -c 2.c

3.o: 3.c
	gcc -c 3.c

clean:
	rm -f *.o *.output 1 2 3
