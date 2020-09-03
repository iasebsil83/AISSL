aissl: AISSL[0.1.0].o
	gcc -o aissl AISSL[0.1.0].o
	rm -f AISSL[0.1.0].o

AISSL[0.1.0].o: AISSL[0.1.0].c
	gcc -c -Wall AISSL[0.1.0].c

