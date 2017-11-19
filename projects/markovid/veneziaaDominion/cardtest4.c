/*
 *Dylan Markovic
 *CS362 Assignment 3
 *cardtest4.c
 *testing 'adventurer' card
*/

/*
 *1. Current player should draw 2 treasure cards, and  discard all other drawn

 *2. All cards should come from his own pile.

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
#include <limits.h>

#define TESTCARD "adventurer"
#define SEED 1000
#define PLAYER_COUNT 4
#define MAX_HAND 500
#define MAX_DECK 500

int testAdventurer(){
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
	G.discardCount[0] = 0;
	//first four cards in deck are 2 treasure and 2 action cards
	G.deck[0][0] = smithy;
	G.deck[0][1] = gold;
	G.deck[0][2] = silver;
	G.deck[0][3] = adventurer;
	G.hand[0][0] = adventurer;
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("TESTING Number of Cards in Hand after Playing Adventurer Via playAdventurer: ");
	G.numActions = 1;
	int tempHand[500];
	playAdventurer(0,0,&G, 0, tempHand, 0);
	safe_assert(G.handCount[0]== 2);
	
	printf("TESTING QUANTITY of DISCARD to DECK CARDS ");
	//adventurer should be discarded, the two treasure cards in hand would mean 1 less card
	// in the deck and discard total
	safe_assert(testG.deckCount[0] -G.deckCount[0] - G.discardCount[0] == 1);
	
	printf("TESTING ALL CARDS IN HAND ARE TREASURE CARDS via playAdventurer: ");
	int badHand = 0;
	for(i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] != copper || G.hand[0][i] != silver || G.hand[0][i] != gold)
			badHand++;
	}
	safe_assert(badHand==2);
	
	
	
	printf("TESTING Other Players(1-3) State After playAdventurer: ");
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
	
	//restore G to before card was played
	memcpy(&G, &testG, sizeof(struct gameState));
	printf("TESTING Number of Cards in Hand after Playing Adventurer Via playCard: ");
	G.numActions = 1;
	playCard(0,0,0, 0, &G);
	safe_assert(G.handCount[0]== 2);
	
	printf("TESTING QUANTITY of DISCARD to DECK CARDS ");
	//adventurer should be discarded, the two treasure cards in hand would mean 1 less card
	// in the deck and discard total
	safe_assert(testG.deckCount[0] -G.deckCount[0] - G.discardCount[0] == 1);
	
	printf("TESTING ALL CARDS IN HAND ARE TREASURE CARDS via playCard: ");
	badHand = 0;
	for(i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] != copper || G.hand[0][i] != silver || G.hand[0][i] != gold)
			badHand++;
	}
	safe_assert(badHand==0);
	
	
	printf("TESTING Other Players(1-3) State After playSmithy: ");
	playerNotEffected = 0;	//flag for player difference
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
	
		 badState = 0;
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
	testAdventurer();
	return 0;
}
