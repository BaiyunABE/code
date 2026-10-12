all: lru

lru: lru.o
	gcc -o lru lru.o

lru.o: lru.c
	gcc -c lru.c

clean:
	rm -f *.o lru
