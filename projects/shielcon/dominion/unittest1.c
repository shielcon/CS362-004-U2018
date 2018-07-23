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
	int maxHandCount = 5;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int players[2];

	int numPlayer = 2;
	struct gameState G;
	int failures = 0;
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	G.handCount[0]=5;
	G.handCount[1]=5;
	
	int curses[5];
	int estates[5];
	for (i = 0; i < maxHandCount; i++){
		estates[i] = estate;
		curses[i] = curse;
	}

	//simple case: one player has a score of five, the other has a score of -5

	memcpy(G.hand[0], estates, sizeof(int) * maxHandCount);
	memcpy(G.hand[1], curses, sizeof(int) * maxHandCount);

	getWinners(players, &G);

	printf("expected result for p1: 1, actual result: %d\n", players[0]);
	printf("expected result for p2: 0, actual result: %d\n", players[1]);

	if (players[0] != 1 || players[1] != 0){
		printf("test failed\n");
		failures++;
	}


	//another simple case: this time, player two wins
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);
        G.handCount[0]=5;
        G.handCount[1]=5;

        memcpy(G.hand[0], curses, sizeof(int) * maxHandCount);
        memcpy(G.hand[1], estates, sizeof(int) * maxHandCount);

        getWinners(players, &G);

        printf("expected result for p1: 0, actual result: %d\n", players[0]);
        printf("expected result for p2: 1, actual result: %d\n", players[1]);

        if (players[0] != 0 || players[1] != 1){
                printf("test failed\n");
                failures++;
        }



	//both have negative scores, but p1 has one estate card
	
	memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);
        G.handCount[0]=5;
        G.handCount[1]=5;

        memcpy(G.hand[0], curses, sizeof(int) * maxHandCount - 1);
	G.hand[0][4] = estate;
        memcpy(G.hand[1], curses, sizeof(int) * maxHandCount);

	getWinners(players, &G);

        printf("expected result for p1: 1, actual result: %d\n", players[0]);
        printf("expected result for p2: 0, actual result: %d\n", players[1]);

        if (players[0] != 1 || players[1] != 0){
                printf("test failed\n");
                failures++;
        }

	//both have the same scores
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);
        G.handCount[0]=5;
        G.handCount[1]=5;
	G.whoseTurn = 2;

        memcpy(G.hand[0], estates, sizeof(int) * maxHandCount);
        memcpy(G.hand[1], estates, sizeof(int) * maxHandCount);

        getWinners(players, &G);

        printf("expected result for p1: 1, actual result: %d\n", players[0]);
        printf("expected result for p2: 1, actual result: %d\n", players[1]);

        if (players[0] != 1 || players[1] != 1){
                printf("test failed\n");
                failures++;
        }


	//both have the same scores, but p2 wins because it's still p1's turns
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);
        G.handCount[0]=5;
        G.handCount[1]=5;
        //G.whoseTurn = 2; the turn is left at p1

        memcpy(G.hand[0], estates, sizeof(int) * maxHandCount);
        memcpy(G.hand[1], estates, sizeof(int) * maxHandCount);

        getWinners(players, &G);

        printf("expected result for p1: 0, actual result: %d\n", players[0]);
        printf("expected result for p2: 1, actual result: %d\n", players[1]);

        if (players[0] != 0 || players[1] != 1){
                printf("test failed\n");
                failures++;
        }

	if (faiilures > 0)
		printf("At least one test case failed. getWinners() needs to be debugged\n");
	else
		printf("All test cases for getWinners() passed\n");


return 0;
}





























