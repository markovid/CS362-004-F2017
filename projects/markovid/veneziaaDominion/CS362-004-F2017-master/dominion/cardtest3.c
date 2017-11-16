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

	printf("Testing Smithy\n");	
	int player = state.whoseTurn;

	int status = cardEffect(smithy, 0, 0, 0, &state, 0, 0);

	testState.phase = state.phase; // Correct behavior unclear

	testState.handCount[player] += 3;
	testState.deckCount[player] -= 3;

	int failed = 0;
	if (status != 0)
	{
		printf("Fail - Returned incorrect status.\n");
		failed = 1;
	}
	if (state.handCount[player] != testState.handCount[player])
	{
		printf("Fail - Hand size was not increased by 3.\n");
		failed = 1;
	}
	if (state.deckCount[player] != testState.deckCount[player])
	{
		printf("Fail - Three cards not missing from deck.\n");
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
