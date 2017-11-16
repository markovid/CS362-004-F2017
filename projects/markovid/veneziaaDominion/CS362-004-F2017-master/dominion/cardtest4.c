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

	printf("Testing Gardens\n");	

	int status = cardEffect(gardens, 0, 0, 0, &state, 0, 0);

	testState.phase = state.phase; // Correct behavior unclear


	int failed = 0;
	if (status != -1)
	{
		printf("Fail - Did not return error code for attempt to play Gardens.\n");
		failed = 1;
	}
	if (memcmp(&state, &testState, sizeof(struct gameState)))
	{
		printf("Fail - Miscellaneous memory corruption\n");
		failed = 1;
	}
	if (failed == 0)	
		printf("Passed!\n");

	return 0;
}
