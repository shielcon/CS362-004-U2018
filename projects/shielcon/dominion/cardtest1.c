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

	playAdventurer(&G, 0);

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

	playAdventurer(&G, 1);

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

	return 0;
}








	














