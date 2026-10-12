all:
	bison -d -Wcounterexamples yy.y
	flex yy.l
	cc -o yy yy.tab.c lex.yy.c -lm

clean:
	rm yy yy.tab.h yy.tab.c lex.yy.c