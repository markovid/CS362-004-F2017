/*
 *Dylan Markovic
 *CS362 Assignment 3
 *randomtestcardadventurer.c
 *testing 'adventurer Card'
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
#include <time.h>

#define TESTCARD "adventurer"
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
int randomAdventurer(){
	struct gameState G, originalG;
	int kard[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i;
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
		G.hand[currentPlayer][cardPosition] = adventurer;
		//copy G into the state we will not be altering, originalG
		memcpy(&originalG, &G, sizeof(struct gameState));
		
		G.numActions = 1;
		int tempHand[500];
		playAdventurer(0,0,&G, 0, tempHand, 0);

		
		printf("TESTING QUANTITY of DISCARD to DECK CARDS ");
		//the number of cards in the deck + discard pile should have 1 less card(+adventurer in hand - 2 treasure from deck
		safe_assert(originalG.deckCount[currentPlayer] + originalG.discardCount[currentPlayer]-G.deckCount[currentPlayer] - G.discardCount[currentPlayer] == 1);
			
		printf("TESTING Number of Cards in hand after playAdventurer: ");
		safe_assert(G.handCount[currentPlayer] == originalG.handCount[currentPlayer] + 1);//should have discarded 1 and drawn 2
		
		printf("TESTING if last two cards in hand are treasure cards: ");
		//after playing adventurer, the last two cards in current player's hand should be treasure cards
		int validCards = 0;
		int x;
		for(x = G.handCount[currentPlayer] -2; x < G.handCount[currentPlayer]; x++){
			if(G.hand[currentPlayer][x] != copper || G.hand[currentPlayer][x] != silver || G.hand[currentPlayer][x] != gold)
				validCards++;
		}
		safe_assert(validCards == 0); //both new cards are not treasure
		
		printf("TESTING Other Players' State After playAdventurer: ");
		int playerNotEffected = 0;	//flag for player difference
		int j, k;
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
		
		//restore G to before card was played
		
		//**** testing via playCard ********
		memcpy(&G, &originalG, sizeof(struct gameState));
		printf("TESTING Action Count after Playing Adventurer via playCard: ");
		G.numActions = 1;
		playCard(cardPosition, 0, 0, 0, &G);
		safe_assert(G.numActions == 1);
		
		printf("TESTING Adventurer was Discarded after Adventurer: ");
		safe_assert(G.discardCount[currentPlayer] == originalG.discardCount[currentPlayer] + 1 //1 more card after used
			&& G.discard[currentPlayer][G.discardCount[currentPlayer]-1] == great_hall);  //top of discard pile is greathall
			
		printf("TESTING Number of Cards in hand after Adventurer: ");
		safe_assert(G.handCount[currentPlayer] == originalG.handCount[currentPlayer]);//should have discarded 1 and drawn 1
		
		printf("TESTING 1 less Card is in deck after Adventurer: ");
		safe_assert(G.deckCount[currentPlayer] == originalG.deckCount[currentPlayer] -1);  //should have 1 less card in deck
		
		printf("TESTING Other Players' State After Adventurer: ");
		playerNotEffected = 0;	//flag for player difference
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
		
		badState = 0;
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
	randomAdventurer();
	return 0;
}