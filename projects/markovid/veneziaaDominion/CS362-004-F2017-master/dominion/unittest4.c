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
	int kingdomCards[10] = 
		{adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };
	int numberOfPlayers = 2;
	initializeGame(numberOfPlayers, kingdomCards, seed, &state);

	printf("Testing drawCard()\n");	
	
	int status;
	int i;
	int failed = 0;

	for (i = 0; i < 6; i++)
	{
		status = drawCard(0, &state);
		if (i < 5)
		{
			if (status != 0)
			{
				printf("Fail - Error status reported by function.\n");
				failed = 1;
			}
			if (state.handCount[0] != 6 + i)
			{
				printf("Fail - Number of cards in hand incorrect.\n");
				failed = 1;
			}
		}
		else
		{
			if (status != -1)
			{
				printf("Fail - Impossible draw does not report error.\n");
				failed = 1;
			}
			if (state.handCount[0] != 10)
			{
				printf("Fail - Hand size incorrect after failed draw.\n");
				failed = 1;
			}
		}
	}
	if (failed == 0)
		printf("Success!\n");

	return 0;
}
