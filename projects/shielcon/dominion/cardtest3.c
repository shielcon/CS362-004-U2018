#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){

        int seed = 1000;
        int numPlayer = 2;
        struct gameState G;
        int failures=0;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        memset(&G, 23, sizeof(struct gameState));
        int r = initializeGame(numPlayer, k, seed, &G);

	G.handCount[0] = 5;
	G.hand[0][0] = village;
	G.deckCount[0] = 30;
	G.numActions = 0;
	int i;
	for (i = 1; i < 5; i++)
		G.hand[0][i] = feast;
	for (i = 0; i < 30; i++)
		G.deck[0][i] = adventurer;

	playVillage(0, &G, 0);
	

	if (G.handCount[0] == 6 && G.hand[0][5] == adventurer)
		printf("Success. The player has the correct number of cards\n");
	else{
		printf("Failure. The player doesn't have the correct number of cards\n");
		failures++;
	}
	if (G.numActions == 2)
		printf("Success\n");
	else if (G.numActions > 2){
		printf("Failure. Too many actions added\n");
		failures++;
	}
	else{
		printf("Failure. Not enough actions added\n");
		failures++;
	}

	printf("Total failures: %d\n", failures);

	return 0;

}
