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

	G.deckCount[0] = 10;
	G.handCount[0] = 5;
	int i;
	for (i = 0; i < 10; i++)
		G.deck[0][i] = adventurer;
	for (i = 0; i < 4; i++)
		G.hand[0][i] = adventurer;

	playSmithy(0, &G);

	if (G.handCount[0] == 7)
		printf("success\n");
	else if (G.handCount[0] > 7){
		printf("failure. The player has too many cards in their hand\n");
		failures++;
	}
	else{
		printf("failure. The player has too few cards in their hand\n");
		failures++;
	}

	printf("total failures: %d\n", failures);

	return 0;

}
