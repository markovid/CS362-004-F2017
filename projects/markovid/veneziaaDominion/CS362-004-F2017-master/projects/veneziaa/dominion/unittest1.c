/*
 *Dylan Markovic
 *CS362 Assignment 3
 *unittest1.c
 *testing 'whoseTurn' function
*/

/*
	***test for whoseTurn function
	*whoseTurn is a function that takes one parameter, a pointer to a gamestate struct.
	*it returns the integer which corresponds to array indices for the chosen player's deck,
	*hand, discard pile, etc
	
	*we can test the function by changing the value of the gamestate's whoseTurn value directly 
	*and comparing it the the function results.
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

#define TESTFUNC "whoseTurn"
#define SEED 1000
#define PLAYER_COUNT 2

int testWhoseTurn(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i;
	int check=0;	//used for bool value
	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	printf("     ***TESTING: %s***\n", TESTFUNC);
	printf("\nTESTING NORMAL VALUES(0-3): ");
	for(i = 0; i < 4; i++){
		G.whoseTurn = i;
		if(G.whoseTurn != whoseTurn(&G))
			check++;
	}
	safe_assert(check == 0);
	
	printf("\nTESTING MAX VALUE: ");
		G.whoseTurn = INT_MAX;
		safe_assert(G.whoseTurn == whoseTurn(&G));
	
	printf("\nTESTING MIN VALUE: ");
		G.whoseTurn = INT_MIN;
		safe_assert(G.whoseTurn == whoseTurn(&G));
		
	printf("\n     ___TESTING COMPLETE___\n");
	
	return 0;
	
}

int main(){
	testWhoseTurn();
	return 0;
}