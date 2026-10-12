all: null forget joy

null: null.o
	gcc -o null null.o

forget: forget.o
	gcc -o forget forget.o

joy: joy.o
	gcc -o joy joy.o

null.o: null.c
	gcc -c null.c

forget.o: forget.c
	gcc -c forget.c

joy.o: joy.c
	gcc -c joy.c

clean:
	rm -f *.o null forget joy
