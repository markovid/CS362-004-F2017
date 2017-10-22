/*
 *Dylan Markovic
 *CS362 Assignment 3
 *unittest4.c
 *testing 'scoreFor' function
*/

/*
	***testing scoreFor function
	* function calculates score based on treasure cards found in hand, deck, and discard pile
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "safe_assert.h"
#include <limits.h>
#include "dominion_helpers.h"

#define TESTFUNC "scoreFor"
#define SEED 1000
#define PLAYER_COUNT 4

int testScoreFor(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	printf("     ***TESTING: %s***\n", TESTFUNC);
	
	//by having a single card present in hand,deck,discard, it is easier to see where errors can occur
	G.handCount[0] = 1;
	G.deckCount[0] = 0;
	G.discardCount[0] = 0;
	printf("\nTESTING HAND SCORE...\n");
	
	printf("\nTESTING CURSE: ");
	G.hand[0][0] = curse;
	safe_assert(scoreFor(0,&G) == -1);
	
	printf("\nTESTING ESTATE: ");
	G.hand[0][0] = estate;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING DUCHY: ");
	G.hand[0][0] = duchy;
	safe_assert(scoreFor(0,&G) == 3);
	
	printf("\nTESTING PROVINCE: ");
	G.hand[0][0] = province;
	safe_assert(scoreFor(0,&G) == 6);
	
	printf("\nTESTING GREAT HALL: ");
	G.hand[0][0] = great_hall;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING Gardens: ");
	G.hand[0][0] = gardens;
	safe_assert(scoreFor(0,&G) == 0);
	
	G.handCount[0] = 0;
	G.deckCount[0] = 1;
	G.discardCount[0] = 0;
	printf("\nTESTING DECK SCORE...\n");
	
	printf("\nTESTING CURSE: ");
	G.deck[0][0] = curse;
	safe_assert(scoreFor(0,&G) == -1);
	
	printf("\nTESTING ESTATE: ");
	G.deck[0][0] = estate;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING DUCHY: ");
	G.deck[0][0] = duchy;
	safe_assert(scoreFor(0,&G) == 3);
	
	printf("\nTESTING PROVINCE: ");
	G.deck[0][0] = province;
	safe_assert(scoreFor(0,&G) == 6);
	
	printf("\nTESTING GREAT HALL: ");
	G.deck[0][0] = great_hall;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING Gardens: ");
	G.deck[0][0] = gardens;
	safe_assert(scoreFor(0,&G) == 0);
	
	G.handCount[0] = 0;
	G.deckCount[0] = 0;
	G.discardCount[0] = 1;
	printf("\nTESTING DISCARD SCORE...\n");
	
	printf("\nTESTING CURSE: ");
	G.discard[0][0] = curse;
	safe_assert(scoreFor(0,&G) == -1);
	
	printf("\nTESTING ESTATE: ");
	G.discard[0][0] = estate;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING DUCHY: ");
	G.discard[0][0] = duchy;
	safe_assert(scoreFor(0,&G) == 3);
	
	printf("\nTESTING PROVINCE: ");
	G.discard[0][0] = province;
	safe_assert(scoreFor(0,&G) == 6);
	
	printf("\nTESTING GREAT HALL: ");
	G.discard[0][0] = great_hall;
	safe_assert(scoreFor(0,&G) == 1);
	
	printf("\nTESTING Gardens: ");
	G.discard[0][0] = gardens;
	safe_assert(scoreFor(0,&G) == 0);
	
	
	//with 10 estates, gardens should add 1 to the score (10+1=11)
	G.handCount[0] = 0;
	G.deckCount[0] = 10;
	G.discardCount[0] = 1;
	printf("\nTESTING GARDENS IN DISCARD WITH 10 ESTATE IN DECK: ");
	int i;
	for(i = 0; i < 10; i++)
		G.hand[0][i] = estate;
	G.discard[0][0] = gardens;
	safe_assert(scoreFor(0,&G) == 11);
	

	

		
	printf("\n     ___TESTING COMPLETE___\n");
	
	return 0;
	
}

int main(){
	testScoreFor();
	return 0;
}