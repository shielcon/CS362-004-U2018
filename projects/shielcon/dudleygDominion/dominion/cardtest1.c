#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){

	int seed = 1000;
	int numPlayer = 3;
	struct gameState G;
	int failures=0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	memset(&G, 23, sizeof(struct gameState));
	int r = initializeGame(numPlayer, k, seed, &G);

	//test for first player: currently has 2 golds in deck

	G.handCount[0] = 1;
	G.hand[0][0] = adventurer;

	G.deckCount[0] = 5;
	G.discardCount[0] = 0;
	G.deck[0][0] = smithy;
        G.deck[0][1] = gold;
        G.deck[0][2] = smithy;
        G.deck[0][3] = gold;
        G.deck[0][4] = smithy;

	int tempHand[MAX_HAND], cardDrawn;
	int drawntreasure = 0;
	int z = 0;

	adventurerCard(&G, 0, cardDrawn, tempHand, drawntreasure, z);

	if (G.hand[0][G.handCount[0]-2] == gold)
		printf("Success\n");
	else{
		printf("Player's hand didn't acquire the 2 gold coins from the deck. Test failed\n");
		failures++;
	}
	if (G.discard[0][G.discardCount[0]-2] == smithy && G.discard[0][G.discardCount[0]-1] == smithy){
		printf("Success\n");
	}
	else{
		printf("Failure. Something is wrong with the discard pile\n");
		failures++;
	}


	//test for second player: deck is empty. Discard has all copper coins

	G.handCount[1] = 1;
	G.hand[1][0] = adventurer;

	G.deckCount[1] = 0;
	G.discardCount[1] = 10;
	int i;
	for (i = 0; i < 10; i++)
		G.discard[1][i] = copper;

	drawntreasure = 0;
	z = 0;

	adventurerCard(&G, 1, cardDrawn, tempHand, drawntreasure, z);

	if (G.hand[1][G.handCount[1]-2] == copper && G.hand[1][G.handCount[1]-1] == copper){
		printf("Success\n");
	}
	else{
		printf("Player's hand didn't acquire the 2 copper coins from the discard pile\n");
		failures++;
	}

	if (G.discardCount[1] == 0)
		printf("success\n");
	else{
		printf("Failure. Something is wrong with the discard pile\n");
		failures++;
	}

	//test for third player. Has nothing but adventurers in his hand
	
	G.handCount[2] = 5;
	G.deckCount[2] = 10;
	G.discardCount[2] = 10;

	G.handCount[0] = 10;
	G.handCount[1] = 10;
	G.deckCount[0] = 10;
	G.deckCount[1] = 10;
	G.discardCount[0] = 10;
	G.discardCount[1] = 10;

	for (i = 0; i < 10; i++){

		G.deck[2][i] = adventurer;
		G.discard[2][i] = adventurer;
		G.hand[0][i] = copper;
		G.hand[1][i] = copper;
		G.deck[0][i] = copper;
		G.deck[1][i] = copper;
		G.discard[0][i] = copper;
		G.discard[1][i] = copper;
	}

	for (i = 0; i < 10; i++){
		G.hand[2][i] = adventurer;
	}

	z = 0;
	drawntreasure = 0;

	adventurerCard(&G, 2, cardDrawn, tempHand, drawntreasure, z);

	for (i = 0; i < G.handCount[2]; i++){
		if (G.hand[2][i] == copper){
			printf("Failure. The player should not have earned a copper\n");
			failures++;
		}
	}

	if (G.handCount[0] != 10 || G.handCount[1] != 10
	   || G.deckCount[0] != 10 || G.deckCount[1] != 10
	   || G.discardCount[0] != 10 || G.discardCount[1] != 10)
	{
		printf("Failed. The other player's game states were changed somehow\n");
		failures++;
	}

	if (failures > 0)
		printf("Not all test cases passed. The adventurer function needs to be debugged\n");
	else
		printf("All tests passed\n");
	

	return 0;
}








	














