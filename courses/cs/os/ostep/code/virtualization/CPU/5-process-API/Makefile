all: p1 p2 p3 p4

p1: p1.o
	gcc -o p1 p1.o

p2: p2.o
	gcc -o p2 p2.o

p3: p3.o
	gcc -o p3 p3.o

p4: p4.o
	gcc -o p4 p4.o

p1.o: p1.c
	gcc -c p1.c

p2.o: p2.c
	gcc -c p2.c

p3.o: p3.c
	gcc -c p3.c

p4.o: p4.c
	gcc -c p4.c

clean:
	rm -f *.o *.output p1 p2 p3 p4
