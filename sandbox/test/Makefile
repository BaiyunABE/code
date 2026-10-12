all: test2 test3

test2: test2.o
	gcc -o test2 test2.o

test2.o: test2.s
	gcc -c test2.s

test2.s: test2.c
	gcc -S test2.c

test3: test3.o
	gcc -o test3 test3.o

test3.o: test3.s
	gcc -c test3.s

test3.s: test3.c
	gcc -S test3.c

clean:
	rm -f *.s *.o test2 test3
