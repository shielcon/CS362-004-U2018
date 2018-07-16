#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
	int i, c, t, r;
	int deckCount;
	int handCount;
	int discardCount;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
	int cardTypes[6][MAX_HAND];
	int cardScore[6];
	int numPlayer = 2;
	struct gameState G;
	int score;
	int expected;
	int failures = 0;
	
for (i = 0; i < 6; i++){
	for (c = 0; c < MAX_HAND; c++){
		cardTypes[i][c] = curse;
		cardTypes[i][c] = estate;
		cardTypes[i][c] = duchy;
		cardTypes[i][c] = province;
		cardTypes[i][c] = great_hall;
		cardTypes[i][c] = gardens;
	}
}


cardScore[0] = -1;
cardScore[1] = 1;
cardScore[2] = 3;
cardScore[3] = 6;
cardScore[4] = 1;
cardScore[5] = 0;

int j; //for testing
	
//#if (NOISY_TEST == 1)
//    printf("Test player %d with %d treasure card(s) and %d bonus.\n", i, handCount, bonus);
//#endif

for (i = 0; i < numPlayer; i++){
	for (deckCount = 1; deckCount <= 5; deckCount++){
		for (discardCount = 1; discardCount <= 5; discardCount++){
			for (handCount = 1; handCount <= 5; handCount++){
				memset(&G, 23, sizeof(struct gameState));
				r = initializeGame(numPlayer, k, seed, &G);
				G.handCount[i] = handCount;
				G.deckCount[i] = deckCount;
				G.discardCount[i] = discardCount;
				
				for (t = 0; t < 6; t++){
					memcpy(G.deck[i], cardTypes[t], sizeof(int) * deckCount);
					memcpy(G.discard[i], cardTypes[t], sizeof(int) * discardCount);
					memcpy(G.hand[i], cardTypes[t], sizeof(int) * handCount);
					for (j = 0; j < handCount; j++)
						printf("current value in hand: %d\n", G.hand[i][j]);
					score = scoreFor(i, &G);
					cardScore[5] = (handCount + deckCount + discardCount) * (fullDeckCount(i, 0, &G) / 10);
					expected = (handCount * cardScore[t]) + (discardCount * cardScore[t]) + (handCount * cardScore[t]);
#if (NOISY_TEST == 1)
					printf("score for player %d = %d, expected score is %d\n", i, score, expected);
#endif
					if (score != expected){
						printf("Test failed\n");
						failures++;
					}
				}
			}
		}	
	}		
}	

return 0;
}
				
				
				
				
				
				
				
