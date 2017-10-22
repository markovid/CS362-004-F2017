CFLAGS = -Wall -fpic -coverage -lm
safe_assert.o: safe_assert.h safe_assert.c
	gcc -c safe_assert.c -g $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o safe_assert.o $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out



	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
tests.out: unittest1.c safe_assert.h safe_assert.c
	echo "Result for running dominion tests:" > tests.out
	
	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 dominion.c unittest1.c rngs.c safe_assert.c $(CFLAGS)
	unittest1 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "unittest2.c:" >> tests.out
	gcc -o unittest2 dominion.c unittest2.c rngs.c safe_assert.c $(CFLAGS)
	unittest2 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "unittest3.c:" >> tests.out
	gcc -o unittest3 dominion.c unittest3.c rngs.c safe_assert.c $(CFLAGS)
	unittest3 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "unittest4.c:" >> tests.out
	gcc -o unittest4 dominion.c unittest4.c rngs.c safe_assert.c $(CFLAGS)
	unittest4 >> tests.out
	gcov dominion.c >> tests.out


all: playdom player testDrawCard testBuyCard badTestDrawCard tests.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe tests.out
