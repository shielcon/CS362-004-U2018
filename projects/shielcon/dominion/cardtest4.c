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
	G.whoseTurn = 0;

	G.numActions = 1;
	G.handCount[0] = 5;
	G.discardCount[0] = 0;
	int i;
	for (i = 0; i < 4; i++)
		G.hand[0][i] = adventurer;
	G.hand[0][4] = great_hall;
	G.deckCount[0] = 30;
	for (i = 0; i < 30; i++)
		G.deck[0][i] = smithy;

        G.handCount[1] = 10;
        G.deckCount[1] = 10;
        G.discardCount[1] = 10;
        for (i = 0; i < 10; i++){
                G.hand[1][i] = remodel;
                G.deck[1][i] = remodel;
                G.discard[1][i] = remodel;
        }

	
	playGreat_hall(0, &G, 4);

	if (G.hand[0][4] == smithy)
		printf("Success. Smithy added to hand\n");//also ensures that the player drew from their own deck, since Smithy is only in their deck
	else{
		printf("Failure. Smithy has not been added\n");
		failures++;
	}
	for (i = 0; i < G.handCount[0]; i++){
		if (G.hand[0][i] == great_hall){
			printf("Failure. great hall was not removed\n");
			failures++;
		}
	}

	if (G.numActions == 2)
		printf("success\n");
	else{
		printf("Failure. Action not added\n");
		failures++;
	}

	if (G.whoseTurn != 0){
		printf("Failure. The game state's turn was changed\n");
		failures++;
	}

	if (failures > 0)
		printf("Some tests failed. The Great_hall implementation needs to be debugged\n");
	else
		printf("All test cases passed\n");


	return 0;

}
