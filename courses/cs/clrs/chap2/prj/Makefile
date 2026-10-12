all:
	gcc -O2 -o bin/mergesort src/mergesort.c
	gcc -O2 -o bin/quicksort src/quicksort.c
	gcc -O2 -o bin/select src/select.c
	gcc -O2 -o bin/point src/point.c -lm

dbg:
	gcc -g -o bin/mergesort src/mergesort.c
	gcc -g -o bin/quicksort src/quicksort.c
	gcc -g -o bin/select src/select.c
	gcc -g -o bin/point src/point.c -lm

clean:
	rm bin/*.out
	rm bin/mergesort
	rm bin/quicksort
	rm bin/select
	rm bin/point
