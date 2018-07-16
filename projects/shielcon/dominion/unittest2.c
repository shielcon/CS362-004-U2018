#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
        int r;
        int i;
        int seed = 1000;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int trashFlag = 0;
	int trashFlag2 = 1;

        int numPlayer = 2;
        struct gameState G;
        int failures = 0;

        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);

	G.playedCardCount = 0;

        G.handCount[0]=5;
        G.handCount[1]=1;

	int adventurers[5];

	memcpy(G.hand[0], adventurers, sizeof(int) * 5);
	G.hand[1][0] = adventurer;

	//standard discard procedure. Both players discard with the trashflag set to 0


	discardCard(4, 0, &G, trashFlag);
	discardCard(0, 1, &G, trashFlag);

	printf("playedCards should contain 2 cards. It contains %d cards\n", G.playedCardCount);

	if (G.playedCardCount != 2 || G.playedCards[G.playedCardCount-1] != adventurer){
		printf("test failed\n");
		printf("%d\n", G.playedCards[G.playedCardCount - 1]);
		failures++;
	}

	//discard without the trashflag set. Played cards should stay the same,
	//but the player should still lose the card
	discardCard(3, 0, &G, trashFlag2);
	
	printf("PlayedCards should still contain 2 cards, player 1 shoule have 3 remaining cards. PlayedCards = %d. Player 1's hand has %d cards\n", G.playedCardCount, G.handCount[0]);

	if (G.handCount[0] != 3 || G.playedCardCount != 2){
		printf("test failed\n");
		failures++;
	}

	G.hand[0][2] = smithy;
	G.hand[0][1] = curse;
	G.hand[0][0] = adventurer;

	//discarding curse from hand
	discardCard(1, 0, &G, trashFlag2);

	printf("player 1 shoule have an adventurer and a smithy. The curse should not be in the player's hand\n");

	for (i = 0; i < G.handCount[0]; i++){
		printf("card: %d\n", G.hand[0][i]);
		if (G.hand[0][i] == curse){
			printf("test failed\n");
			failures++;
		}
	}

	printf("total failures: %d\n", failures);

	return 0;	

}
	

	

	
	
	
