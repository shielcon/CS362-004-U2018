#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){

	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	struct gameState *state = &G;
	int numPlayer = 2;
	memset(&G, 23, sizeof(struct gameState));
	int r = initializeGame(numPlayer, k, seed, &G);

	int player = 0;
	int supplyPos = adventurer;
	int failures=0;

	G.deckCount[player]=0;
	G.handCount[player]=0;
	G.discardCount[player]=0;
	G.supplyCount[adventurer] = 10;
	G.supplyCount[feast] = 1;
	G.supplyCount[smithy] = 0;

	gainCard(adventurer, &G, 0, player); //to flag = 0 - to discard


	printf("player should have 1 adventurer in the discard. The supply should have one less adventurer. No other cards should have changed\n");

        if (
           state->discard[player][state->discardCount[player]-1] == supplyPos
           && state->deckCount[player] == 0
           && state->handCount[player] == 0
           && state->discardCount[player] == 1
           && state->supplyCount[adventurer] == 9
           && state->supplyCount[feast] == 1
           && state->supplyCount[smithy] == 0)
		printf("success\n");
	else{
		printf("test 1 failed\n");
		failures++;
	}


        gainCard(adventurer, &G, 1, player); //to flag = 1 - to deck

        printf("player should have 1 adventurer in the deck. The supply should have one less adventurer. No other cards should have changed\n");


        if (state->deck[player][state->deckCount[player]-1] == supplyPos
           && state->deckCount[player] == 1
           && state->handCount[player] == 0
           && state->deckCount[player] == 1
           && state->supplyCount[adventurer] == 8
           && state->supplyCount[feast] == 1
           && state->supplyCount[smithy] == 0)
                printf("success\n");
        else{
                printf("test 2 failed\n");
                failures++;
        }


        gainCard(adventurer, &G, 2, player); //to flag = 2 - to hand

        printf("player should have 1 adventurer in the hand. The supply should have one less adventurer. No other cards should have changed\n");


        if (
	   state->hand[player][state->handCount[player]-1] == supplyPos
           && state->deckCount[player] == 1
           && state->handCount[player] == 1
           && state->handCount[player] == 1
           && state->supplyCount[adventurer] == 7
           && state->supplyCount[feast] == 1
           && state->supplyCount[smithy] == 0)
                printf("success\n");
        else{
                printf("test 3 failed\n");
                failures++;
        }


	gainCard(feast, &G, 0, player); // should only return one feast
	if (gainCard(feast, &G, 0, player) > -1){
		printf("Test failed. No feast cards remaining\n");
		failures++;
	}
	if (gainCard(smithy, &G, 0, player) > -1){
		printf("Test failed. No smithy cards remaining\n");
		failures++;
	}


	printf("Total falures: %d\n", failures);

	return 0;

}
