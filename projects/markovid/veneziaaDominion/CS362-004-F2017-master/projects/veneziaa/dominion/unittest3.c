/*
 *Dylan Markovic
 *CS362 Assignment 3
 *unittest3.c
 *testing 'updateCoins' function
*/

/*
	***testing updateCoins function
	* function updates the current players coins via counting the treasure cards he is holding
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

#define TESTFUNC "updateCoins"
#define SEED 1000
#define PLAYER_COUNT 4

int testUpdateCoins(){
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	printf("     ***TESTING: %s***\n", TESTFUNC);
	printf("\nTESTING Copper Coin: ");
		G.handCount[0] = 1;
		G.hand[0][0] = copper;
		updateCoins(0,&G,0);
		safe_assert(G.coins == 1); 
		
	printf("\nTESTING Silver Coin: ");
		G.handCount[0] = 1;
		G.hand[0][0] = silver;
		updateCoins(0,&G,0);
		safe_assert(G.coins == 2);
		
	printf("\nTESTING Gold Coin: ");
		G.handCount[0] = 1;
		G.hand[0][0] = gold;
		updateCoins(0,&G,0);
		safe_assert(G.coins == 3); 
		
	printf("\nTESTING Bonus: ");
		G.handCount[0] = 1;
		G.hand[0][0] = smithy;
		updateCoins(0,&G,5);
		safe_assert(G.coins == 5); 
	

		
	printf("\n     ___TESTING COMPLETE___\n");
	
	return 0;
	
}

int main(){
	testUpdateCoins();
	return 0;
}