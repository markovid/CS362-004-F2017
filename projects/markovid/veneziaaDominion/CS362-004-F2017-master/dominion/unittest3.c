#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main()
{
	int i;
	const int seed = 300;
	struct gameState state;
	int kingdomCards[10] = 
		{adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };
	int numberOfPlayers = 2;
	initializeGame(numberOfPlayers, kingdomCards, seed, &state);

	printf("Testing getWinners()\n");	
	int winner[2];

	getWinners(winner, &state);
	
	int failed = 0;
	
	for (i = 0; i < 2; i++)
	{
		if (winner[i] != 1)
		{
			printf("Fail - Players not drawn at beginning of game.\n");
			failed = 1;
		}
	}

	state.hand[0][0] = curse;

	getWinners(winner, &state);

	if (winner[0] != 0)
	{
		printf("Fail - Player with curse did not lose to player without curse.\n");
		failed = 1;
	}
	if (winner[1] != 1)
	{
		printf("Fail - Player without curse did not beat player with curse.\n");
		failed = 1;
	}
	
	if (failed == 0)
		printf("Success!\n");

	return 0;
}
