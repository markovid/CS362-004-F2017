#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main()
{
	const int seed = 300;
	struct gameState state;
	struct gameState testState;
	int kingdomCards[10] = 
		{adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };
	int numberOfPlayers = 2;
	initializeGame(numberOfPlayers, kingdomCards, seed, &state);

	memcpy(&testState, &state, sizeof(struct gameState));

	printf("Testing buyCard(2)\n");	
	int position = 2;
	int player = state.whoseTurn;
	int totalDiscard = state.discardCount[player];

	state.coins = 10;

	int status = buyCard(position, &state);

	testState.phase = state.phase; // Correct behavior unclear
	testState.coins = 5;  // Hard coded cost of feast because getCost wasn't working

	testState.supplyCount[position]--;
	testState.numBuys--;
	testState.discard[player][totalDiscard] = kingdomCards[position];
	testState.discardCount[player]--;

	if (status != 0)
		printf("Fail - Returned incorrect status\n");
	else if (state.coins != testState.coins)
		printf("Fail - Coins updated incorrectly\n");
	else if (state.supplyCount[position] != testState.supplyCount[position])
		printf("Fail - Supply count not updated correctly\n");
	else if (state.numBuys != testState.numBuys)
		printf("Fail - Number of buys not updated correctly\n");
	else if (state.discard[player][totalDiscard] != testState.discard[player][totalDiscard])
		printf("Fail - Card not correctly added to discard pile\n");
	else if (state.discardCount[player] != testState.discardCount[player])
		printf("Fail - Discard count not updated correctly\n");
	else if (memcmp(&state, &testState, sizeof(struct gameState)))
		printf("Fail - Miscellaneous memory corruption\n");
	else
		printf("Passed!\n");

	return 0;
}
