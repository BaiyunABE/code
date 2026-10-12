all:
	bison rpcalc.y
	cc -o rpcalc rpcalc.tab.c -lm

clean:
	rm rpcalc rpcalc.tab.c