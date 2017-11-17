CFLAGS = -Wall -fpic -coverage -lm -std=c99
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

unittest1.out:
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c unittest1.c rngs.c safe_assert.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
unittest2.out:
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c unittest2.c rngs.c safe_assert.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

unittest3.out:
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c unittest3.c rngs.c safe_assert.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

unittest4.out:
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c unittest4.c rngs.c safe_assert.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

cardtest1.out:
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c cardtest1.c rngs.c safe_assert.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

cardtest2.out:
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c cardtest2.c rngs.c safe_assert.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

cardtest3.out:
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c cardtest3.c rngs.c safe_assert.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

cardtest4.out:
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c cardtest4.c rngs.c safe_assert.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unittestresults.out: unittest1.c safe_assert.h safe_assert.c
	echo "Result for running dominion tests:" > tests.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c unittest1.c rngs.c safe_assert.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c unittest2.c rngs.c safe_assert.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c unittest3.c rngs.c safe_assert.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c unittest4.c rngs.c safe_assert.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c cardtest2.c rngs.c safe_assert.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c cardtest3.c rngs.c safe_assert.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c cardtest1.c rngs.c safe_assert.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c cardtest4.c rngs.c safe_assert.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
randomtestcard1.out: randomtestcard1.c safe_assert.h safe_assert.c
	echo "Result for running randomtestcard1.c tests:" >>  randomtestcard1.out	
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 dominion.c randomtestcard1.c rngs.c safe_assert.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2.c safe_assert.h safe_assert.c
	echo "Result for running randomtestcard2.c tests:" >> randomtestcard2.out	
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 dominion.c randomtestcard2.c rngs.c safe_assert.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	
randomtestadventurer.out: randomtestadventurer.c safe_assert.h safe_assert.c
	echo "Result for running randomtestadventurer.c tests:" >> randomtestadventurer.out	
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer dominion.c randomtestadventurer.c rngs.c safe_assert.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults.out cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer

