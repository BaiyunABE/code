all: dpp parking_lot

dpp: dpp.o
	gcc -o dpp dpp.o

parking_lot: parking_lot.o
	gcc -o parking_lot parking_lot.o

dpp.o: dpp.c
	gcc -c dpp.c

parking_lot.o: parking_lot.c
	gcc -c parking_lot.c

clean:
	rm -f *.o dpp parking_lot
