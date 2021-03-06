/*
 *Dylan Markovic
 *CS362 Assignment 3
 *randomtestcard1.c
 *testing 'Smithy Card'
*/

/*    testing smithy card
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
#include <limits.h>
#include <time.h>

#define TESTCARD "smithy"
#define PLAYER_COUNT 4
#define MAX_HAND 500
#define MAX_DECK 500
#define TEST_NUMBER 500
#define SEED_UPPER_LIMIT 1000
#define SEED_LOWER_LIMIT 0
#define PLAYER_UPPER_LIMIT 4
#define PLAYER_LOWER_LIMIT 2

//createRandom simply creates a random int in the rangeof the limits, including the limit value
int createRandom(int lowerLimit, int upperLimit){
	return (rand()%(upperLimit-lowerLimit) + lowerLimit);
}
int randomGreatHall(){
	struct gameState G, originalG;
	int kard[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i,j,k;
	//test card TEST_NUMBER many times
	for(i = 0; i < TEST_NUMBER; i++){
			printf("     ***TESTING %d of %d: %s***\n", i+1, TEST_NUMBER, TESTCARD);
		int seed = createRandom(SEED_LOWER_LIMIT, SEED_UPPER_LIMIT); 		//random value to seed gamestate
		int numberOfPlayers = createRandom(PLAYER_LOWER_LIMIT, PLAYER_UPPER_LIMIT); //random number of players
		int currentPlayer = createRandom(0, numberOfPlayers-1);	//randomly choose whose will play the card
		int cardPosition = createRandom(0, MAX_HAND -1);  //create random position for the card to be played from
		
		//initialize game state
		initializeGame(numberOfPlayers, kard, seed, &G);
		G.whoseTurn = currentPlayer;
		G.hand[currentPlayer][cardPosition] = smithy;
		//copy G into the state we will not be altering, originalG
		memcpy(&originalG, &G, sizeof(struct gameState));
		

		//**** testing via playCard ********
		G.numActions = 1;
		playCard(cardPosition, 0, 0, 0, &G);
		
		printf("TESTING smithy was Discarded after Smithy via playCard: ");
		safe_assert(G.discardCount[currentPlayer] == originalG.discardCount[currentPlayer] + 1 //1 more card after used
			&& G.discard[currentPlayer][G.discardCount[currentPlayer]-1] == great_hall);  //top of discard pile is greathall
			
		printf("TESTING Number of Cards in hand after Smithy: ");
		safe_assert(G.handCount[currentPlayer] == originalG.handCount[currentPlayer] + 2);//should have discarded 1 and drawn 3
		
		printf("TESTING Smithy was Discarded after Smithy: ");
		safe_assert(G.discardCount[currentPlayer] == originalG.discardCount[currentPlayer] + 1 && G.discard[currentPlayer][G.discardCount[currentPlayer]-1] == smithy);	
		
		printf("TESTING 3 less Cards are in deck after Smithy: ");
		safe_assert(G.deckCount[currentPlayer] == originalG.deckCount[currentPlayer] -3);
		
		printf("TESTING Other Players' State After Smithy: ");
		int playerNotEffected = 0;	//flag for player difference
		for(j = 0; j < numberOfPlayers; j++){	//testing other players hands
			if(j != currentPlayer){
				for(k = 0; k < MAX_HAND; k++){
					if(G.hand[j][k] != originalG.hand[j][k])
						playerNotEffected++;
				}
				for(k = 0; k < MAX_DECK; k++){	//testing other players decks
					if(G.deck[j][k] != originalG.deck[j][k])
						playerNotEffected++;
				}
				for(k = 0; k < MAX_DECK; k++){	//testing other players discards
					if(G.discard[j][k] != originalG.discard[j][k])
						playerNotEffected++;
				}
			}
		}
		safe_assert(playerNotEffected == 0);
		
		int badState = 0;
		printf("TESTING STATE OF THE TREASURE AND VICTORY DECKS: ");
		for (k = adventurer; k <= treasure_map; k++){
			if(G.supplyCount[k] != originalG.supplyCount[k])
				badState++;
		}
		safe_assert(badState==0);
	}
	return 0;
	
}

int main(){
	srand(time(NULL));
	randomGreatHall();
	return 0;
}
