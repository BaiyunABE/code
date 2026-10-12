all:
	bison -d mycc.y
	flex mycc.l
	cc -o mycc mycc.tab.c lex.yy.c -lm

clean:
	rm mycc mycc.tab.h mycc.tab.c lex.yy.c