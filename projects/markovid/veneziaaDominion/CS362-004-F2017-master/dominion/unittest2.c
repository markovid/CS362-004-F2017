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

	printf("Testing isGameOver()\n");

	int failed = 0;

	if (isGameOver(&state))
	{
		printf("Fail - Game reports being over immediately\n");
		failed = 1;
	}	
	
	state.supplyCount[province] = 0;
	if (!isGameOver(&state))
	{
		printf("Fail - Game not over after all provinces gone.\n");
		failed = 1;
	}
	state.supplyCount[province] = 10;

	state.supplyCount[adventurer] = 0;
	state.supplyCount[village] = 0;
	state.supplyCount[baron] = 0;
	if (!isGameOver(&state))
	{
		printf("Fail - Game not over after 3 piles gone.\n");
		failed = 1;
	}
	
	if (failed == 0)
		printf("Success!\n");

	return 0;
}
