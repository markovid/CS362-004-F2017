CFLAGS = -Wall -fpic -coverage -lm

all: testme run

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

run: testme
	./testme
	
clean:
	rm -f *.o testme
