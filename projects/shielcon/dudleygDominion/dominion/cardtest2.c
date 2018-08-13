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
	G.discardCount[0] = 10;

	G.deckCount[1] = 10;
	G.handCount[1] = 5;
	G.discardCount[1] = 10;
	int i;
	for (i = 0; i < 10; i++){
		G.deck[0][i] = adventurer;
		G.deck[1][i] = smithy;
		G.discard[0][i] = smithy;
		G.discard[1][i] = smithy;
	}
	for (i = 0; i < 4; i++){
		G.hand[0][i] = adventurer;
		G.deck[1][i] = smithy;
	}

	smithyCard(&G, 0, 0);

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

	for (i = 0; i < G.handCount[0]; i++){//ensures the card is drawn from the player's own hand
		if (G.hand[0][i] == smithy){
			printf("Test failed. Player acquired a card that wasn't in their deck\n");
			failures++;
		}
	}
	if (G.handCount[1] != 5 || G.deckCount[1] != 10 || G.discardCount[1] != 10){//ensures the  other player's gamestate is not changed
		printf("Test failed. The other player's gamestate was affected somehow\n");
		failures++;
	}
	if (G.discardCount[0] != 10){
		printf("Test failed. The player's discard pile was affected somehow\n");
		failures++;
	}

	if (failures > 0)
		printf("Not all tests passed. The Smithy implementation needs to be debugged\n");
	else
		printf("All test cases passed\n");
	


	return 0;

}
