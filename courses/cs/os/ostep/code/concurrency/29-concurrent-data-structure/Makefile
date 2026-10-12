all: queue

queue: queue.o
	gcc -o queue queue.o

queue.o: queue.c
	gcc -c queue.c

clean:
	rm -f *.o queue
