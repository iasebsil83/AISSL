run: AISSL.o
	gcc -o run AISSL.o
	rm -f AISSL.o

AISSL.o: AISSL.c
	gcc -c -Wall AISSL.c

