all: hex2dd dd2hex hostinfo echoclient echoserver

hex2dd: hex2dd.c
	gcc -I../include hex2dd.c -o hex2dd

dd2hex: dd2hex.c
	gcc -I../include dd2hex.c -o dd2hex

hostinfo: hostinfo.c ../src/csapp.c
	gcc -I ../include hostinfo.c ../src/csapp.c -o hostinfo

echoclient: echoclient.c ../src/csapp.c
	gcc -I../include ../src/csapp.c echoclient.c -o echoclient

echoserver: echoserver.c ../src/csapp.c echo.c
	gcc -I ../include echoserver.c ../src/csapp.c echo.c -o echoserver

clean:
	rm -f hex2dd dd2hex hostinfo echoclient echoserver