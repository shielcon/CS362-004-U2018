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
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	int r = initializeGame(numPlayer, k, seed, &G);

	G.whoseTurn=0;

	G.handCount[0] = 5;
	G.hand[0][0] = smithy;
	
	int result = handCard(0, &G);

	if (result == smithy)
		printf("Success\n");
	else
		printf("test failed\n");
	

	return 0;
}
