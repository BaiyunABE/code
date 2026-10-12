all: pcp

pcp: pcp.o buffer.o
	gcc -o pcp pcp.o buffer.o

pcp.o: pcp.c
	gcc -c pcp.c

buffer.o: buffer.c
	gcc -c buffer.c

clean:
	rm -f *.o pcp
