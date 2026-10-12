all: thread lock

thread: thread.o
	gcc -o thread thread.o -Wall -pthread

lock: lock.o
	gcc -o lock lock.o -Wall -pthread

thread.o: thread.c
	gcc -c thread.c

lock.o: lock.c
	gcc -c lock.c

clean:
	rm -f *.o thread lock
