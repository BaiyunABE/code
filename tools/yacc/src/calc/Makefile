all:
	bison calc.y
	cc -o calc calc.tab.c -lm

clean:
	rm calc calc.tab.c