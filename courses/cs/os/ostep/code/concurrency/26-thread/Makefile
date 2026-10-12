all: t0 t1

t0: t0.o
	gcc -o t0 t0.o -Wall -pthread

t1: t1.o
	gcc -o t1 t1.o -Wall -pthread

t0.o: t0.c
	gcc -c t0.c

t1.o: t1.c
	gcc -c t1.c

clean:
	rm -f *.o t0 t1
