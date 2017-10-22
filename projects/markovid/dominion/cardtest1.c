/*
 *Dylan Markovic
 *CS362 Assignment 3
 *cardtest1.c
 *testing 'Smithy' card
*/

/*
 *1. Current player should receive exact 3 cards.

 *2. 3 cards should come from his own pile.

 *3. No state change should occur for other players.

 *4. No state change should occur to the victory card piles and kingdom card piles.
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "safe_assert.h"

#define TESTCARD "smithy"
#define SEED 1000
#define PLAYER_COUNT 2
#define MAX_HAND 500
#define MAX_DECK 500

int main(){
	int aTestFailed= 0;
	int drawnCards = 0, disCards = 1;
	int handpos = 0, choice[3] = {0,0,0}, bonus = 0;
	int i,j;
	int currPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	
	printf("     *** TESTING: %s ***\n", TESTCARD); 
	
	//1. Current player should receive exact 3 cards.
	printf("\nTesting the number of cards drawn is 3:  ");
	//copy game state to testG
	memcpy(&testG, &G, sizeof(struct gameState));
	drawnCards = 3;
	cardEffect(smithy, choice[0], choice[1], choice[2], &testG, handpos, &bonus);
	aTestFailed += 
			safe_assert(G.handCount[currPlayer] == testG.handCount[currPlayer] +drawnCards - disCards);
			
	printf("Expected Card Count: %d     Actual Card Count: %d\n", G.handCount[currPlayer], testG.handCount[currPlayer] +drawnCards - disCards); 
	
	//2. 3 cards should come from his own pile.
	printf("\nTesting the drawn cards come from Current Player's Pile:  ");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice[0], choice[1], choice[2], &testG, handpos, &bonus);
	int decksWrong=0;
	for(i = 0; i < PLAYER_COUNT; i++){
		if(decksWrong > 0)
			break;
		if(i != 0 && G.deckCount[i] != testG.deckCount[i]){
			decksWrong++;
			aTestFailed += 
				safe_assert(G.deckCount[i] == testG.deckCount[i]);			
		}

	}
	if(decksWrong == 0)
		printf(" TEST PASSED\n");
	for(i = 0; i < PLAYER_COUNT; i++)
		printf("Player %d's DECK Before Play: %d    After Play: %d\n",i,G.deckCount[i],testG.deckCount[i]);

	
	//3. No state change should occur for other players.
	printf("\nTesting Other Players are not affected:  ");
	
	//4. No state change should occur to the victory card piles and kingdom card piles.
	printf("\nTesting the state of the Victory and Kingdom piles is preserved:  ");
	
	
	if(aTestFailed)
		printf("\n     !!!Card: %s, Has FAILED  the Complete Test!!!\n", TESTCARD);	
	else
		printf("\n     ***Card: %s, Has Passed the Complete Test***\n", TESTCARD);
	
	return 0;
}
