/*
 *Dylan Markovic
 *CS362 Assignment 3
 *cardtest2.c
 *testing 'village card'
*/

/*
	***testing village card
	*when the village card is played, the player should gain 2 action and draw a card
	*every other player should have the same state
	*the card should be in the discard pile after it is played
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

#define TESTCARD "village"
#define SEED 1000
#define PLAYER_COUNT 4
#define MAX_HAND 500
#define MAX_DECK 500

int testVillage(){
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i, j;
	//used for bool value
	// initialize a game state and player cards
	initializeGame(PLAYER_COUNT, k, SEED, &G);
	
	//testG will be an unused copy of the gamestate to compare the other players decks,hands,discards
	printf("     ***TESTING: %s***\n", TESTCARD);
	
	
	//make player 0 have only a village in hand, and no discards, 1 deck card.
	G.handCount[0] = 1;
	G.deckCount[0] = 1;
	G.discardCount[0] = 0;
	G.hand[0][0] = village;
	memcpy(&testG, &G, sizeof(struct gameState));

	

	
	//restore G to before card was played
	printf("TESTING Action Count after Playing Village via playCard: ");
	G.numActions = 1;
	playCard(0, 0, 0, 0, &G);
	safe_assert(G.numActions == 2);
	
	printf("TESTING Village was Discarded after playCard: ");
	safe_assert(G.discardCount[0] == 1 && G.discard[0][0] == village);
	
	printf("TESTING 1 Card is in hand after playCard: ");
	safe_assert(G.handCount[0] == 1);
	
	printf("TESTING 0 Cards are in deck after playCard: ");
	safe_assert(G.deckCount[0] == 0);
	
	printf("TESTING Other Players(1-3) State After playCard: ");
	int playerNotEffected = 0;	//flag for player difference
	for(j = 1; j < PLAYER_COUNT; j++){	//testing other players hands
		for(i = 0; i < MAX_HAND; i++){
			if(G.hand[j][i] != testG.hand[j][i])
				playerNotEffected++;
		}
		for(i = 0; i < MAX_DECK; i++){	//testing other players decks
			if(G.deck[j][i] != testG.deck[j][i])
				playerNotEffected++;
		}
		for(i = 0; i < MAX_DECK; i++){	//testing other players discards
			if(G.discard[j][i] != testG.discard[j][i])
				playerNotEffected++;
		}
	}
	safe_assert(playerNotEffected == 0);
	
	int badState = 0;
	printf("TESTING STATE OF THE TREASURE AND VICTORY DECKS: ");
	  for (i = adventurer; i <= treasure_map; i++){
		  if(G.supplyCount[i] != testG.supplyCount[i])
			  badState++;
	  }
	safe_assert(badState==0);
		
	printf("\n     ___TESTING COMPLETE___\n");
	
	return 0;
	
}

int main(){
	testVillage();
	return 0;
}
