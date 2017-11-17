/*
 *Dylan Markovic
 *CS362 Assignment 3
 *unittest2.c
 *testing 'numHandCards' function
*/

/*
	***testing numHandCards function
	* function takes a pointer to a gamestate struct and returns how many cards 
	* the current player has in his hand
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

#define TESTFUNC "numHandCards"
#define SEED 1000
#define PLAYER_COUNT 4

int testNumHandCards(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i;
	int check=0;	//used for bool value
	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	printf("     ***TESTING: %s***\n", TESTFUNC);
	printf("\nTESTING NORMAL VALUES for current player (0-500): ");
	for(i = 0; i < 500; i++){
		G.handCount[0] = i;
		if(G.handCount[0] != numHandCards(&G))
			check++;
	}
	safe_assert(check == 0);
	
	printf("\nTESTING MAX VALUE for card quantity: ");
		G.handCount[0] = INT_MAX;
		safe_assert(G.handCount[0] == numHandCards(&G));
	
	printf("\nTESTING MIN VALUE: ");
		G.handCount[0] = INT_MIN;
		safe_assert(G.handCount[0] == numHandCards(&G));
		
	printf("\n     ___TESTING COMPLETE___\n");
	
	return 0;
	
}

int main(){
	testNumHandCards();
	return 0;
}